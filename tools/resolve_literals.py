#!/usr/bin/env python3
"""Resolve word literals at explicitly supplied ARM7 ROM instruction addresses.

Example: python tools/resolve_literals.py 0x08000100 0x08000102 --mode Thumb
Optional --function names select provisional symbol bindings from the fixed
build manifest. Reports are exclusive new JSON files beneath reports/.

Only Thumb-1 LDR Rt,[PC,#imm] and aligned ARM immediate, preindexed, non-writeback
word LDR are supported. Thumb uses (address+4)&~3; ARM uses address+8. No scan,
RAM-copy mapping, Thumb-2, unaligned ARM word rotation, pointed-to-memory read,
execution/condition evaluation, function boundary or source/type proof occurs.
Caller-supplied addresses may be data. Symbol names never affect decoded values.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys
import time

from project import ROOT, inspect_rom

BASE = 0x08000000
MAX_ADDRESS = 0xffffffff
MAX_SITES = 256
WARNINGS = [
    'Instruction addresses are caller-supplied; code versus data is unproven.',
    'This resolves encoded addresses only; it does not prove execution or an ARM condition.',
    'The value is the literal word, not a read of pointed-to memory or a type claim.',
    'Selected manifest names are provisional annotations; conflicting bindings remain explicit.',
]


def _address(value):
    if isinstance(value, bool) or not isinstance(value, int) or not 0 <= value <= MAX_ADDRESS:
        raise ValueError('Address must be an unsigned 32-bit integer')
    return value


def _offset(data, address, size, base):
    offset = address - base
    if offset < 0 or offset > len(data) - size:
        raise ValueError('Instruction or literal word lies outside the supplied ROM span')
    return offset


def resolve_word_literal(data, address, mode='Thumb', base=BASE):
    """Decode one explicit site in a contiguous byte span; no identity/CFG claim.

    Use analyze_literals for an identity-audited report. Even function-pointer
    state bits in supplied addresses are rejected, never silently cleared.
    """
    _address(address)
    _address(base)
    if len(data) > MAX_ADDRESS + 1 - base:
        raise ValueError('ROM mapping exceeds the 32-bit address space')
    if mode not in ('Thumb', 'ARM'):
        raise ValueError('Mode must be Thumb or ARM')
    size = 2 if mode == 'Thumb' else 4
    if address % size:
        raise ValueError('Instruction address is not aligned for the selected mode')
    offset = _offset(data, address, size, base)
    raw = bytes(data[offset:offset+size])
    opcode = int.from_bytes(raw, 'little')
    if mode == 'Thumb':
        if opcode & 0xf800 != 0x4800:
            raise ValueError('Not an ARM7 Thumb immediate word PC-relative LDR')
        register, displacement, condition = (opcode >> 8) & 7, (opcode & 255) * 4, None
        bias = 4
    else:
        # Check I=0, P=1, B=0, W=0, L=1 and Rn=PC; U selects +/- imm12.
        if opcode >> 28 == 15 or opcode & 0x0f7f0000 != 0x051f0000:
            raise ValueError('Not an ARM7 immediate non-writeback word PC-relative LDR')
        register, condition = (opcode >> 12) & 15, opcode >> 28
        displacement = (opcode & 4095) * (1 if opcode & 0x00800000 else -1)
        bias = 8
    if address > MAX_ADDRESS - bias:
        raise ValueError('PC bias overflows the 32-bit address space')
    pc = (address + bias) & ~3 if mode == 'Thumb' else address + bias
    literal = pc + displacement
    if not 0 <= literal <= MAX_ADDRESS:
        raise ValueError('Literal address arithmetic overflows the 32-bit address space')
    if literal % 4:
        raise ValueError('Unaligned ARM word loads/rotation are outside this literal resolver')
    literal_offset = _offset(data, literal, 4, base)
    word = bytes(data[literal_offset:literal_offset+4])
    return {'instruction_address': address, 'instruction_rom_offset': offset,
            'mode': mode, 'instruction_bytes': raw.hex(),
            'destination_register': f'r{register}', 'ARM_condition_bits': condition,
            'effective_pc': pc, 'displacement': displacement,
            'literal_address': literal, 'literal_rom_offset': literal_offset,
            'literal_bytes': word.hex(), 'value': struct.unpack('<I', word)[0]}


def selected_bindings(manifest, names):
    """Collect exact selected symbol values, without canonicalizing pointer bits."""
    if len(names) != len(set(names)):
        raise ValueError('Repeated manifest function selection')
    bindings, by_name = [], {}
    rows = manifest.get('functions', []) + manifest.get('assembly', [])
    for name in names:
        selected = [row for row in rows if row['name'] == name]
        if len(selected) != 1:
            raise ValueError('Absent or ambiguous selected manifest function: ' + name)
        for symbol, encoded in selected[0].get('symbols', {}).items():
            value = int(encoded, 0) if isinstance(encoded, str) else encoded
            _address(value)
            bindings.append({'function': name, 'symbol': symbol, 'binding_address': value})
            by_name.setdefault(symbol, set()).add(value)
    conflicts = [{'symbol': name, 'addresses': sorted(values)}
                 for name, values in sorted(by_name.items()) if len(values) > 1]
    for binding in bindings:
        binding['name_has_conflicting_addresses'] = len(by_name[binding['symbol']]) > 1
    return bindings, conflicts


def analyze_literals(data, target, addresses, mode='Thumb', manifest=None, functions=()):
    """Audit reference identity before any instruction/pool resolution; no writes."""
    identity = inspect_rom(data, target)
    if not identity['accepted']:
        raise ValueError('Reference ROM failed its fixed target identity audit')
    addresses = list(addresses)
    if not 1 <= len(addresses) <= MAX_SITES or len(set(addresses)) != len(addresses):
        raise ValueError('Supply 1..256 distinct explicit instruction addresses')
    if functions and (manifest is None or manifest.get('target') != target['id']):
        raise ValueError('Selected manifest target differs from the audited ROM')
    bindings, conflicts = selected_bindings(manifest or {}, functions)
    loads = [resolve_word_literal(data, address, mode) for address in addresses]
    for load in loads:
        load['provisional_symbol_bindings'] = [dict(b) for b in bindings
                                               if b['binding_address'] == load['value']]
    return {'status': 'RESOLVED_EXPLICIT_SITES', 'reference_audit': identity,
            'loads': loads, 'selected_functions': list(functions),
            'symbol_binding_conflicts': conflicts, 'warnings': list(WARNINGS),
            'control_flow_verified': False, 'source_reconstruction_verified': False}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('addresses', nargs='+', type=lambda value: int(value, 0))
    parser.add_argument('--mode', choices=('Thumb', 'ARM'), default='Thumb')
    parser.add_argument('--function', action='append', default=[])
    parser.add_argument('--output', help='Exclusive new JSON path beneath reports/')
    args = parser.parse_args(argv)
    try:
        target_path = ROOT / 'config/targets/us-eu.json'
        target_bytes = target_path.read_bytes()
        target = json.loads(target_bytes)
        data = (ROOT / target['rom_path']).read_bytes()
        manifest_bytes = None
        # Never call project.audit: its latest audit report must remain untouched.
        if not inspect_rom(data, target)['accepted']:
            raise ValueError('Reference ROM failed its fixed target identity audit')
        if args.function:
            manifest_bytes = (ROOT / 'config/build-us-eu.json').read_bytes()
        report = analyze_literals(data, target, args.addresses, args.mode,
                                  json.loads(manifest_bytes) if manifest_bytes else None,
                                  args.function)
        report['target_config_sha256'] = hashlib.sha256(target_bytes).hexdigest()
        report['manifest_sha256'] = (hashlib.sha256(manifest_bytes).hexdigest()
                                     if manifest_bytes is not None else None)
        report['helper_sha256'] = {
            name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
            for name in ('tools/resolve_literals.py', 'tools/project.py')}
        output = Path(args.output) if args.output else Path(f'reports/us-eu/literal-loads/{time.time_ns()}.json')
        output = output.absolute() if output.is_absolute() else (ROOT / output).absolute()
        if (output.resolve() != output or not output.is_relative_to(ROOT / 'reports')
                or output.suffix != '.json'):
            raise ValueError('Output must be a nonsymlink JSON path beneath reports/')
        output.parent.mkdir(parents=True, exist_ok=True)
        with output.open('x', encoding='utf-8') as stream:
            stream.write(json.dumps(report, indent=2) + '\n')
        print('Report: ' + str(output.relative_to(ROOT)))
        return 0
    except (OSError, ValueError, KeyError, TypeError) as error:
        print('Literal resolution failed: ' + str(error), file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
