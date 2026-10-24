"""Validate bounded indirect calls without closing other table consumers.

The first proof grammar is deliberately narrow: a Thumb byte is guarded above
96, subtracts 96, and supplies the high nibble to a ten-row ROM table. It proves
ordinary paths from one pinned source owner, not arbitrary interior entries or
the state read by a later consumer of the same table.
"""
import hashlib
import struct
from collections import defaultdict

from capstone.arm import (ARM_CC_AL, ARM_CC_INVALID, ARM_INS_B, ARM_INS_BL,
                          ARM_INS_BX, ARM_OP_IMM, ARM_OP_MEM, ARM_OP_REG,
                          ARM_REG_PC, ARM_REG_R0, ARM_REG_R1, ARM_REG_R2,
                          ARM_REG_R3, ARM_REG_R4, ARM_REG_R5)


BASE = 0x08000000
PROOF_KIND = 'thumb_volume_byte_table_v1'


def _require(condition, message):
    if not condition:
        raise ValueError('Bounded table proof: ' + message)


def _signature(ins):
    """Use decoded operands, including shifts, rather than formatted text."""
    operands = []
    for op in ins.operands:
        if op.shift.type or op.subtracted:
            return None
        if op.type == ARM_OP_REG:
            operands.append(('reg', op.reg))
        elif op.type == ARM_OP_IMM:
            operands.append(('imm', op.imm))
        elif op.type == ARM_OP_MEM:
            operands.append(('mem', op.mem.base, op.mem.index, op.mem.disp))
        else:
            return None
    return ins.mnemonic, tuple(operands)


def _cfg(scanner, start, end):
    """Decode every local path; unknown transfers and overlapping code reject."""
    nodes, successors, covered, returns = {}, {}, {}, []
    pending = [start]
    while pending:
        pc = pending.pop()
        if pc in nodes:
            continue
        _require(start <= pc < end and pc % 2 == 0,
                 'local control flow leaves the complete owner')
        ins = scanner.decode(pc, 'Thumb')
        _require(ins is not None and scanner.arm7_instruction(ins, 'Thumb')
                 and pc + ins.size <= end and ins.address == pc
                 and scanner.physical(pc) == pc - BASE,
                 'invalid owned ARM7 Thumb instruction')
        _require(not any(byte in covered for byte in range(pc, pc + ins.size)),
                 'overlapping instruction entries')
        covered.update((byte, pc) for byte in range(pc, pc + ins.size))
        nodes[pc] = ins
        if ins.id == ARM_INS_B:
            _require(len(ins.operands) == 1 and ins.operands[0].type == ARM_OP_IMM,
                     'non-immediate branch')
            edges = [ins.operands[0].imm]
            if ins.cc not in (ARM_CC_AL, ARM_CC_INVALID):
                edges.append(pc + ins.size)
        elif ins.id == ARM_INS_BL:
            _require(len(ins.operands) == 1 and ins.operands[0].type == ARM_OP_IMM
                     and not start <= ins.operands[0].imm < end,
                     'unsupported local call')
            # Normal external-call return is a conservative local edge. Calls
            # are separately forbidden on the byte-definition/selector path.
            edges = [pc + ins.size]
        elif ins.id == ARM_INS_BX:
            _require(_signature(ins) == ('bx', (('reg', ARM_REG_R0),)),
                     'unmodelled register transfer in owner')
            returns.append(pc)
            edges = []
        else:
            _require(ARM_REG_PC not in ins.regs_access()[1]
                     and ins.cc in (ARM_CC_AL, ARM_CC_INVALID)
                     and ins.mnemonic not in ('svc', 'bkpt'),
                     'unmodelled PC write or service in owner')
            edges = [pc + ins.size]
        successors[pc] = edges
        pending.extend(edges)
    predecessors = defaultdict(set)
    for pc, edges in successors.items():
        for dest in edges:
            predecessors[dest].add(pc)
    for pc in returns:
        previous = nodes.get(pc - 2)
        _require(previous is not None
                 and _signature(previous) == ('pop', (('reg', ARM_REG_R0),))
                 and predecessors[pc] == {pc - 2},
                 'return lacks its unique saved-return predecessor')
    _require(returns, 'owner has no recognized return')
    return nodes, predecessors


def _byte_definitions(nodes, predecessors, entry, guard):
    """Every backwards path must meet a byte definition before entry/call."""
    definitions, visited = set(), set()
    pending = list(predecessors[guard])
    _require(guard != entry and pending, 'byte value has no local definition')
    while pending:
        pc = pending.pop()
        if pc in visited:
            continue
        visited.add(pc)
        ins = nodes[pc]
        _require(ins.id != ARM_INS_BL, 'call intervenes after byte definition')
        if ARM_REG_R4 in ins.regs_access()[1]:
            sig = _signature(ins)
            immediate_byte = (sig is not None and sig[0] == 'movs'
                              and len(sig[1]) == 2
                              and sig[1][0] == ('reg', ARM_REG_R4)
                              and sig[1][1][0] == 'imm'
                              and 0 <= sig[1][1][1] <= 255)
            loaded_byte = (sig is not None and sig[0] == 'ldrb'
                           and len(sig[1]) == 2
                           and sig[1][0] == ('reg', ARM_REG_R4)
                           and sig[1][1][0] == 'mem'
                           and not ins.writeback)
            _require(immediate_byte or loaded_byte,
                     'selector reaches guard from a non-byte definition')
            definitions.add(pc)
            continue
        _require(pc != entry and predecessors[pc],
                 'definition-free path from owner entry')
        pending.extend(predecessors[pc])
    _require(definitions, 'no reaching byte definitions')
    return sorted(definitions)


def validate_bounded_table(row, scanner, functions, source_hash):
    """Derive a complete target set from one supported native selector proof.

    Metadata identifies where to check; it cannot supply an unchecked target
    list or assert completeness. The caller's matching build establishes source
    ownership separately. This validator checks its source pin and native flow.
    """
    _require(isinstance(row, dict) and row.get('proof_kind') == PROOF_KIND,
             'unsupported proof grammar')
    owners = [f for f in functions if f.get('name') == row.get('owner')]
    _require(len(owners) == 1, 'missing or ambiguous source owner')
    owner = owners[0]
    fields = ('rom_offset', 'guard_rom_offset', 'dispatch_rom_offset',
              'literal_rom_offset', 'table_rom_offset', 'table_rows',
              'record_stride', 'veneer_rom_offset')
    _require(all(type(row.get(key)) is int for key in fields),
             'integer proof locations required')
    off, size = owner.get('rom_offset'), owner.get('size')
    _require(type(off) is int and type(size) is int and off >= 0
             and 0 < size <= 0x20000 and off + size <= len(scanner.data)
             and owner.get('mode', 'Thumb') == 'Thumb'
             and owner.get('ram_address', BASE + off) == BASE + off,
             'proof requires a bounded ROM Thumb owner')
    _require(isinstance(row.get('source_sha256'), str)
             and len(row['source_sha256']) == 64
             and source_hash(owner) == row['source_sha256'],
             'source owner pin differs')
    _require(row['table_rows'] == 10 and row['record_stride'] == 8,
             'unsupported table layout')
    site, guard, dispatch, literal = (row[key] for key in fields[:4])
    table, veneer = row['table_rom_offset'], row['veneer_rom_offset']
    _require(all(off <= value < off + size and value % 2 == 0
                 for value in (site, guard, dispatch))
             and off <= literal and literal + 4 <= off + size
             and literal % 4 == 0
             and table >= 0 and table % 4 == 0 and table + 80 <= len(scanner.data)
             and veneer >= 0 and veneer % 2 == 0 and veneer + 2 <= len(scanner.data),
             'invalid owner, literal, table or veneer bounds')
    _require(site == dispatch + 24, 'selector window has unexpected length')
    entry, end = BASE + off, BASE + off + size
    nodes, predecessors = _cfg(scanner, entry, end)
    absolute_guard, absolute_dispatch, absolute_site = (BASE + value for value in
                                                       (guard, dispatch, site))
    _require(all(pc in nodes for pc in
                 (absolute_guard, absolute_guard + 2, absolute_guard + 4,
                  absolute_dispatch, absolute_site)),
             'guard or call is not reachable from owner entry')
    R = lambda reg: ('reg', reg)
    I = lambda value: ('imm', value)
    M = lambda base, index=0, disp=0: ('mem', base, index, disp)
    expected_guard = [
        ('cmp', (R(ARM_REG_R4), I(96))),
        ('bls', (I(BASE + guard + 6),)),
        ('b', (I(absolute_dispatch),)),
    ]
    for index, expected in enumerate(expected_guard):
        pc = absolute_guard + 2 * index
        _require(_signature(nodes[pc]) == expected, 'unsigned guard differs')
        if index:
            _require(predecessors[pc] == {pc - 2}, 'guard edge can be bypassed')
    _require(predecessors[absolute_dispatch] == {absolute_guard + 4},
             'selector block has an unguarded incoming edge')
    expected = [
        ('adds', (R(ARM_REG_R1), R(ARM_REG_R4), I(0))),
        ('subs', (R(ARM_REG_R1), I(96))),
        ('lsls', (R(ARM_REG_R4), R(ARM_REG_R1), I(24))),
        ('adds', (R(ARM_REG_R3), R(ARM_REG_R5), I(0))),
        ('ldr', (R(ARM_REG_R0), M(ARM_REG_PC, disp=literal - ((dispatch + 12) & ~3)))),
        ('lsrs', (R(ARM_REG_R2), R(ARM_REG_R4), I(28))),
        ('adds', (R(ARM_REG_R3), I(93))),
        ('strb', (R(ARM_REG_R1), M(ARM_REG_R3))),
        ('lsls', (R(ARM_REG_R1), R(ARM_REG_R2), I(3))),
        ('ldr', (R(ARM_REG_R4), M(ARM_REG_R0, ARM_REG_R1))),
        ('adds', (R(ARM_REG_R0), R(ARM_REG_R5), I(0))),
        ('movs', (R(ARM_REG_R1), I(1))),
        ('bl', (I(BASE + veneer),)),
    ]
    for index, signature in enumerate(expected):
        pc = absolute_dispatch + 2 * index
        _require(pc in nodes and _signature(nodes[pc]) == signature
                 and nodes[pc].size == (4 if index == 12 else 2),
                 'selector arithmetic, store, capture or call differs')
        if index:
            _require(predecessors[pc] == {pc - 2},
                     'selector instruction has an extra incoming edge')
    definitions = _byte_definitions(nodes, predecessors, entry, absolute_guard)
    _require(struct.unpack_from('<I', scanner.data, literal)[0] == BASE + table,
             'literal does not select the pinned immutable ROM table')
    raw = scanner.data[table:table + 80]
    _require(hashlib.sha256(raw).hexdigest() == row.get('table_sha256'),
             'table prefix pin differs')
    stub = scanner.decode(BASE + veneer, 'Thumb')
    _require(stub is not None and scanner.arm7_instruction(stub, 'Thumb')
             and stub.size == 2
             and _signature(stub) == ('bx', (R(ARM_REG_R4),)),
             'veneer does not use the captured target register')
    # Enumerate the finite input domain independently of any claimed metadata
    # bound. The already validated instruction grammar supplies these steps.
    selectors = sorted({(((value - 96) << 24) & 0xffffffff) >> 28
                        for value in range(97, 256)})
    _require(selectors == list(range(10)), 'selector exceeds the observed rows')
    pointers = [struct.unpack_from('<I', raw, index * 8)[0] for index in selectors]
    target_owners = []
    for pointer in pointers:
        address = pointer & ~1
        physical = scanner.physical(address)
        _require(pointer & 1 and physical is not None and address % 2 == 0
                 and physical == address - BASE,
                 'callback is null, unmapped or wrong-mode')
        matches = [f for f in functions if f.get('rom_offset') == physical
                   and f.get('mode', 'Thumb') == 'Thumb'
                   and f.get('ram_address', BASE + physical) == address]
        _require(len(matches) == 1, 'callback lacks an exact source entry')
        target_owners.append(matches[0]['name'])
    targets = sorted({pointer & ~1 for pointer in pointers})
    return {
        'rom_offset': site, 'kind': 'bounded_table_call', 'targets_complete': True,
        'targets': targets,
        'target_modes': [{'address': address, 'mode': 'Thumb'} for address in targets],
        'target_origin': 'validated_guarded_byte_ROM_table',
        'table_rom_offset': table, 'table_bytes': 80, 'record_stride': 8,
        'selector_bounds': [0, 9], 'veneer_address': BASE + veneer,
        'bounded_selector_proof': {
            'kind': PROOF_KIND, 'owner': owner['name'],
            'source_sha256': row['source_sha256'],
            'guard_rom_offset': guard, 'dispatch_rom_offset': dispatch,
            'byte_definition_rom_offsets': [pc - BASE for pc in definitions],
            'reachable_instruction_count': len(nodes), 'byte_inputs': 256,
            'dispatch_inputs': 159, 'target_owners': target_owners,
        },
        'limitation': ('Ordinary local paths from the pinned source owner entry; '
                       'other table consumers, arbitrary interior entry, argument '
                       'validity and runtime behavior remain separate.'),
    }


def annotate_bounded_records(results, physical, validated):
    """Apply validated facts only to the exact decoded register-veneer calls."""
    by_site = {row['rom_offset']: row for row in validated}
    _require(len(by_site) == len(validated), 'duplicate bounded call site')
    found, pending = set(), []
    for result in results.values():
        for record in result['transfer_records']:
            site = physical(record['site'])
            if site not in by_site:
                continue
            row = by_site[site]
            _require(record['site'] == BASE + site,
                     'ROM-entry proof cannot close a copied call alias')
            _require(record['kind'] in ('register_veneer_call', 'observed_table_call',
                                        'bounded_table_call')
                     and record.get('veneer_address') == row['veneer_address'],
                     'decoded transfer does not match the validated veneer call')
            pending.append((record, row))
            found.add(site)
    _require(found == set(by_site), 'bounded annotation lacks a decoded call')
    for record, row in pending:
        record.update(row)
