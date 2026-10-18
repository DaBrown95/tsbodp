#!/usr/bin/env python3
"""ROM-wide static entry/extent inventory; metadata only, never source credit.

Recursive control flow seeds direct calls and literal function pointers. A
whole-ROM prologue/pointer sweep adds candidates, not proven functions. Gaps
remain explicit; instruction decoding is not proof that bytes are executable.
"""
import hashlib
import json
import struct
from collections import defaultdict, deque
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, __version__ as capstone_version
from capstone.arm import ARM_OP_MEM, ARM_REG_PC, ARM_REG_LR, ARM_CC_AL, ARM_CC_INVALID, ARM_INS_BL, ARM_INS_B, ARM_INS_BX, ARM_INS_MOV, ARM_INS_LDR
from project import ROOT, audit
from inventory_partition import partition, overlay
from control_flow import thumb_switch, constant_result, stack_return
from ram_copies import validate_copy
from indirect_evidence import record_tables, phase_targets, validate_fixed_target, annotate_records, literal_veneers
from fixed_target_proof import prove_fixed_target
from inventory_census import census, verify_census

BASE = 0x08000000


def observed_extent_counts(observed, start, size):
    """Count observed byte roles inside an estimate or replacement extent."""
    return {count: sum(start <= offset < start + size for offset in observed[field])
            for field, count in (('instruction_offsets', 'decoded_instruction_bytes'),
                                 ('literal_offsets', 'referenced_literal_bytes'))
            if field in observed}


def finalize_extent_observations(rows):
    """Recount final ownership, including remnants split by an overlay."""
    for row in rows:
        row.update(observed_extent_counts(row, row['rom_offset'], row['size']))
        row.pop('instruction_offsets', None)
        row.pop('literal_offsets', None)


def unresolved_callback_sites(rows):
    """Observed table entries do not prove the runtime index is bounded."""
    calls = ('register_veneer_call', 'dynamic_call', 'observed_table_call')
    return sorted({record['rom_offset'] for row in rows
                   for record in row.get('transfer_records', [])
                   if record['kind'] in calls
                   and not record.get('targets_complete', False)})


def source_owned_data_regions(data, regions, owners, source_hash):
    """Validate supplied source-emitted roles; never remove execution evidence."""
    if not isinstance(regions, list):
        raise ValueError('Source data regions must be a list')
    owners = {owner['name']: owner for owner in owners}
    result, names, spans = [], set(), []
    for row in regions:
        if not isinstance(row, dict):
            raise ValueError('Source data region must be an object')
        name, start, size = row.get('name'), row.get('rom_offset'), row.get('size')
        owner_name = row.get('owner')
        owner = owners.get(owner_name) if isinstance(owner_name, str) else None
        if (not isinstance(name, str) or not name or name in names
                or type(start) is not int or type(size) is not int
                or size <= 0 or start < 0 or start + size > len(data)
                or owner is None or not owner['rom_offset'] <= start
                or start + size > owner['rom_offset'] + owner['size']
                or row.get('role') not in ('alignment', 'debug_packet')
                or not isinstance(row.get('evidence'), list) or not row['evidence']
                or any(not isinstance(item, str) or not item.strip() for item in row['evidence'])):
            raise ValueError('Invalid source-owned data region')
        if (source_hash(owner) != row.get('source_sha256')
                or hashlib.sha256(data[start:start + size]).hexdigest() != row.get('region_sha256')):
            raise ValueError('Source-owned data evidence differs')
        if any(start < end and begin < start + size for begin, end in spans):
            raise ValueError('Source-owned data regions overlap')
        names.add(name)
        spans.append((start, start + size))
        result.append({**row, 'status': 'mapped_data'})
    return result


class Scanner:
    def __init__(self, data, copies):
        self.data, self.copies = data, copies
        self.engines = {m: Cs(CS_ARCH_ARM, flag) for m, flag in
                        [('Thumb', CS_MODE_THUMB), ('ARM', CS_MODE_ARM)]}
        for engine in self.engines.values():
            engine.detail = True
        self.entries, self.results, self.cache = {}, {}, {}
        self.pending = deque()
        self.literal_bytes = set()
        self.case_blocks = set()
        self.internal_labels = set()

    def physical(self, address):
        if BASE <= address < BASE + len(self.data):
            return address-BASE
        for copy in self.copies:
            delta = address-copy['ram_address']
            if 0 <= delta < copy['size']:
                return copy['rom_offset']+delta
        return None

    def seed(self, address, mode, evidence, name=None):
        address &= ~1
        off = self.physical(address)
        if off is None or address % (4 if mode == 'ARM' else 2):
            return
        key = (address, mode)
        if key not in self.entries:
            self.entries[key] = {'evidence': set(), 'name': name}
            self.pending.append(key)
        self.entries[key]['evidence'].add(evidence)
        if name:
            self.entries[key]['name'] = name

    def decode(self, address, mode):
        key = address, mode
        if key not in self.cache:
            off = self.physical(address)
            self.cache[key] = next(self.engines[mode].disasm(self.data[off:off+4], address, count=1), None) if off is not None else None
        return self.cache[key]

    def arm7_instruction(self, ins, mode):
        off = self.physical(ins.address)
        if off is None or off+ins.size > len(self.data):
            return False
        halfword = struct.unpack_from('<H', self.data, off)[0]
        if mode == 'Thumb':
            if ins.size == 4 and ins.mnemonic != 'bl':
                return False
            if halfword & 0xf000 == 0xb000 and halfword & 0xff00 not in (0xb000, 0xb400, 0xb500, 0xbc00, 0xbd00):
                return False
        return not ins.mnemonic.startswith(('udf', 'it', 'cbz', 'cbnz', 'blx'))

    def walk(self, entry, mode):
        todo, visited, literals, calls, issues = [entry], {}, set(), set(), set()
        terminal = False
        trusted = any(e in self.entries.get((entry, mode), {}).get('evidence', ()) for e in ('startup', 'startup main pointer', 'bounded audit', 'audited RAM entry', 'audited dispatch entry', 'direct call', 'resolved literal transfer'))
        transfers = set()
        transfer_records = {}
        returns = set()
        while todo and len(visited) < 32768:
            pc = todo.pop()
            constants = {}
            previous_call_setup = False
            previous_pop = None
            previous_end = None
            while pc not in visited:
                if abs(pc-entry) > 0x20000 or self.physical(pc) is None:
                    issues.add('branch outside bounded walk'); break
                other = self.entries.get((pc, mode))
                interior = other is not None and other['evidence'] <= {'pointer candidate'} and previous_end == pc
                if interior:
                    self.internal_labels.add(pc)
                case_label = interior or other is not None and other['evidence'] <= {'pointer candidate'} and (pc in self.case_blocks or stack_return(self, pc, mode))
                if pc != entry and other is not None and not case_label:
                    issues.add('shared tail or adjacent entry'); terminal = True; break
                ins = self.decode(pc, mode)
                if ins is None or not self.arm7_instruction(ins, mode):
                    issues.add('invalid or non-ARM7 instruction'); break
                visited[pc] = ins.size
                next_pc = pc + ins.size
                loaded = None
                computed = constant_result(ins, constants, mode) if ins.cc in (ARM_CC_AL, ARM_CC_INVALID) else None
                if ins.id == ARM_INS_LDR and len(ins.operands) > 1 and not ins.writeback:
                    mem = ins.operands[1]
                    if mem.type == ARM_OP_MEM and mem.mem.base == ARM_REG_PC and not mem.mem.index:
                        literal = ((pc+4)&~3 if mode == 'Thumb' else pc+8) + mem.mem.disp
                        off = self.physical(literal)
                        if off is not None and off+4 <= len(self.data):
                            literals.update(range(off, off+4)); self.literal_bytes.update(range(off, off+4))
                            value = struct.unpack_from('<I', self.data, off)[0]
                            if ins.cc in (ARM_CC_AL, ARM_CC_INVALID):
                                loaded = ins.operands[0].reg, value
                conditional = ins.cc not in (ARM_CC_AL, ARM_CC_INVALID)
                if ins.id == ARM_INS_BL:
                    dest = ins.operands[0].imm
                    if self.physical(dest) is not None:
                        calls.add((dest, mode)); self.seed(dest, mode, 'direct call' if trusted else 'candidate call')
                    else:
                        issues.add('unmapped direct call')
                    stub = self.decode(dest, mode) if self.physical(dest) is not None else None
                    if stub is not None and stub.mnemonic == 'bx' and stub.operands[0].reg != ARM_REG_LR:
                        register = stub.operands[0].reg
                        value = constants.get(register)
                        record = {'site': pc, 'kind': 'register_veneer_call', 'veneer_address': dest,
                                  'targets_complete': False, 'targets': []}
                        if value is not None and self.physical(value & ~1) is not None:
                            resolved, resolved_mode = value & ~1, 'Thumb' if value & 1 else 'ARM'
                            calls.add((resolved, resolved_mode))
                            self.seed(resolved, resolved_mode, 'resolved literal transfer' if trusted else 'candidate literal transfer')
                            record.update(targets_complete=True, targets=[resolved])
                        transfer_records[pc] = record
                    constants.clear()
                elif ins.id == ARM_INS_B:
                    dest = ins.operands[0].imm
                    todo.append(dest)
                    if not conditional:
                        terminal = True; break
                elif ins.id == ARM_INS_BX:
                    reg = ins.operands[0].reg
                    value = constants.get(reg)
                    if value is not None and self.physical(value & ~1) is not None:
                        dest, dest_mode = value & ~1, 'Thumb' if value & 1 else 'ARM'
                        calls.add((dest, dest_mode)); self.seed(dest, dest_mode, 'resolved literal transfer' if trusted else 'candidate literal transfer')
                        transfer_records[pc] = {'site': pc, 'kind': 'literal_transfer', 'targets_complete': True, 'targets': [dest]}
                    elif ins.op_str != 'lr' and previous_pop != reg and not (pc != entry and stack_return(self, pc, mode)):
                        issues.add('indirect transfer'); transfers.add(pc)
                        transfer_records[pc] = {'site': pc, 'kind': 'dynamic_call' if previous_call_setup else 'register_dispatch', 'targets_complete': False, 'targets': []}
                    if ins.op_str == 'lr' or previous_pop == reg or pc != entry and stack_return(self, pc, mode):
                        returns.add(pc)
                    terminal = True
                    if not previous_call_setup and not conditional:
                        break
                    constants.clear()
                elif ('pc' in ins.op_str and ins.mnemonic.startswith(('pop', 'ldm'))
                      or ins.id == ARM_INS_MOV and ins.op_str.startswith('pc,')):
                    terminal = True
                    if ins.op_str == 'pc, lr' or ins.mnemonic.startswith(('pop', 'ldm')):
                        returns.add(pc)
                    if ins.op_str not in ('pc, lr',) and not ins.mnemonic.startswith(('pop', 'ldm')):
                        switch = thumb_switch(self, pc) if mode == 'Thumb' else None
                        if switch:
                            transfer_records[pc] = switch
                            self.case_blocks.update(switch['targets'])
                            todo.extend(reversed(switch['targets']))
                            table_bytes = set(range(switch['table_rom_offset'], switch['table_rom_offset']+switch['table_bytes']))
                            literals.update(table_bytes); self.literal_bytes.update(table_bytes)
                        else:
                            issues.add('indirect transfer'); transfers.add(pc)
                            transfer_records[pc] = {'site': pc, 'kind': 'unresolved_jump', 'targets_complete': False, 'targets': []}
                    if not conditional:
                        break
                elif ARM_REG_PC in ins.regs_access()[1]:
                    # A decoder must not silently walk through an unmodelled PC
                    # write and then call the later bytes a closed function body.
                    issues.add('indirect transfer'); transfers.add(pc)
                    transfer_records[pc] = {'site': pc, 'kind': 'unresolved_pc_write',
                                            'targets_complete': False, 'targets': []}
                    if not conditional:
                        break
                # Track only literal-loaded register values; other writes invalidate them.
                for reg in ins.regs_access()[1]:
                    constants.pop(reg, None)
                if computed:
                    constants[computed[0]] = computed[1]
                if loaded:
                    constants[loaded[0]] = loaded[1]
                previous_call_setup = ins.op_str == 'lr, pc' and ins.mnemonic == 'mov' or ins.mnemonic == 'add' and ins.op_str == 'lr, pc, #0'
                previous_pop = ins.operands[0].reg if ins.mnemonic == 'pop' and len(ins.operands) == 1 else None
                previous_end = next_pc
                pc = next_pc
        if len(visited) >= 32768:
            issues.add('walk instruction limit')
        return {'instructions': visited, 'literals': literals, 'calls': calls,
                'issues': issues, 'terminal': terminal, 'unresolved_transfers': transfers, 'transfer_records': list(transfer_records.values()), 'return_sites': returns}

    def drain(self):
        while self.pending:
            key = self.pending.popleft()
            self.results[key] = self.walk(*key)


def main():
    requirement = next(line.split('==', 1)[1] for line in
                       (ROOT/'config/analysis-requirements.txt').read_text().splitlines()
                       if line.startswith('capstone=='))
    if capstone_version != requirement:
        raise ValueError('Capstone version differs from pinned analysis requirements')
    target = json.loads((ROOT/'config/targets/us-eu.json').read_text())
    data, identity = audit(ROOT/target['rom_path'], target)
    if not identity['accepted']:
        return 1
    ram = json.loads((ROOT/'config/ram-map-us-eu.json').read_text())
    bounded = json.loads((ROOT/'config/progress-regions-us-eu.json').read_text())
    manifest = json.loads((ROOT/'config/build-us-eu.json').read_text())
    source_code = manifest['functions'] + [r for r in manifest.get('assembly', []) if r.get('mode') != 'data']
    word = lambda off: struct.unpack_from('<I', data, off)[0]
    for copy in ram['copies']:
        validate_copy(copy, word)
    for entry in ram['entries']:
        if 'pointer_rom_offset' in entry and word(entry['pointer_rom_offset']) != entry['ram_address']:
            raise ValueError('RAM entry pointer differs from ROM')
    if word(ram['irq_default_table_rom_offset']+12) != 0x03000004:
        raise ValueError('Audio IRQ entry differs from default table')
    scanner = Scanner(data, ram['copies'])
    scanner.seed(BASE, 'ARM', 'startup', 'ROM entry')
    scanner.seed(BASE+0xc0, 'ARM', 'startup', 'ARM startup')
    scanner.seed(BASE+0xec, 'Thumb', 'startup', 'Thumb startup')
    scanner.seed(BASE+0x25c0c, 'Thumb', 'startup main pointer', 'Entry routine')
    for row in bounded['unconverted_extents'] + source_code:
        scanner.seed(row.get('ram_address', BASE+row['rom_offset']),
                     row.get('mode', 'ARM' if row['name'].startswith('ARM') else 'Thumb'),
                     'bounded audit', row['name'])
    for entry in ram['entries']:
        scanner.seed(entry['ram_address'], entry['mode'], 'audited RAM entry', entry['name'])
    dispatch_config = json.loads((ROOT/'config/indirect-transfers-us-eu.json').read_text())
    evidence_config = json.loads((ROOT/'config/code-evidence-us-eu.json').read_text())
    if evidence_config['reference_sha256'] != identity['sha256']:
        raise ValueError('Static evidence targets another ROM')
    evidence_inputs = set()
    source_data = source_owned_data_regions(
        data, evidence_config.get('source_owned_data_regions', []),
        manifest['functions'] + manifest.get('assembly', []),
        lambda owner: hashlib.sha256((ROOT/owner['source']).read_bytes()).hexdigest())
    evidence_inputs.update(next(owner['source'] for owner in manifest['functions'] + manifest.get('assembly', [])
                                if owner['name'] == row['owner']) for row in source_data)
    observed_records = record_tables(data, evidence_config['observed_record_tables'], scanner.physical)
    for table in observed_records:
        for item in table['evidence']:
            if 'source' in item:
                owner = next((f for f in manifest['functions'] if f['name'] == item['function']), None)
                if (owner is None or owner['source'] != item['source']
                        or hashlib.sha256((ROOT/item['source']).read_bytes()).hexdigest() != item['source_sha256']):
                    raise ValueError('Stale matching-source table evidence')
                evidence_inputs.add(item['source'])
        for value in table['targets']:
            scanner.seed(value & ~1, 'Thumb' if value & 1 else 'ARM', 'audited dispatch entry')
    for row in evidence_config['fixed_targets']:
        validate_fixed_target(row, data, manifest['functions'],
                              lambda f: hashlib.sha256((ROOT/f['source']).read_bytes()).hexdigest(), scanner.physical)
        evidence_inputs.add(next(f['source'] for f in manifest['functions'] if f['name'] == row['owner']))
    for address in literal_veneers(scanner, evidence_config['audio_literal_veneers']):
        scanner.seed(address, 'Thumb', 'audited dispatch entry')
    veneers = evidence_config['register_veneer_sequence']
    from capstone import arm
    for index, register in enumerate(veneers['registers']):
        address = BASE + veneers['rom_offset'] + index * veneers['stride']
        ins = scanner.decode(address, 'Thumb')
        if (ins is None or ins.id != ARM_INS_BX
                or ins.operands[0].reg != getattr(arm, 'ARM_REG_R'+str(register))
                or struct.unpack_from('<H', data, address-BASE+2)[0] != 0x46c0):
            raise ValueError('Register veneer sequence differs from audited template')
        scanner.seed(address, 'Thumb', 'audited dispatch entry', 'Register veneer r'+str(register))
    for table in dispatch_config['observed_dispatch_tables']:
        values = list(struct.unpack_from('<'+'I'*table['count'], data, table['rom_offset']))
        if values != table['entries']:
            raise ValueError('Observed dispatch table differs from ROM')
        if 'pointer_literal_rom_offset' in table and word(table['pointer_literal_rom_offset']) != BASE+table['rom_offset']:
            raise ValueError('Dispatch table pointer differs from audited literal')
        for value in values:
            if value:
                scanner.seed(value & ~1, 'Thumb' if value & 1 else 'ARM', 'audited dispatch entry')
    scanner.drain()
    # Snapshot strong evidence before any pointer/prologue-only candidate seeds.
    # The separate census never promotes those candidates or awards source credit.
    for key in list(scanner.results):
        scanner.results[key] = scanner.walk(*key)
    scanner.drain()
    strong_results = dict(scanner.results)
    strong_entries = {key: {**value, 'evidence': set(value['evidence'])}
                      for key, value in scanner.entries.items()}
    for row in evidence_config['fixed_targets']:
        owner = next(f for f in manifest['functions'] if f['name'] == row['owner'])
        prove_fixed_target(scanner, owner, row['rom_offset'], row['target'])
    graph_count = len(scanner.entries)
    # Inspect ALL aligned ROM words for pointers. They remain candidate evidence:
    # integer data can resemble addresses, and callbacks are not proven reachable.
    pointers = defaultdict(int)
    arm_pointers = defaultdict(int)
    arm_signatures = defaultdict(list)
    raw_arm_bx = 0
    prologues = set()
    for off in range(0, len(data)-3, 4):
        value = struct.unpack_from('<I', data, off)[0]
        if value & 1 and scanner.physical(value & ~1) is not None:
            pointers[value & ~1] += 1
        elif not value & 3 and scanner.physical(value) is not None:
            arm_pointers[value] += 1
        if value & 0x0ffffff0 == 0x012fff10:
            raw_arm_bx += 1
        if value & 0x0fff0000 == 0x092d0000 and value & 0x4000:
            condition = value >> 28
            name = ('STMDB_SP_LR_AL' if condition == 14 else
                    'STMDB_SP_LR_conditional' if condition < 14 else
                    'STMDB_pattern_unsupported_condition_15')
            arm_signatures[name].append(BASE+off)
        if value == 0xe52de004:
            arm_signatures['STR_LR_SP_predecrement_AL'].append(BASE+off)
        if (value == 0xe1a0c00d and off+8 <= len(data)
                and struct.unpack_from('<I', data, off+4)[0] & 0x0fff4000 == 0x092d4000):
            arm_signatures['APCS_MOV_IP_SP_then_STMDB'].append(BASE+off)
    # Scan every Thumb halfword for the common push {...,lr} entry pattern.
    raw_thumb_bx = 0
    for off in range(0, len(data)-1, 2):
        value = struct.unpack_from('<H', data, off)[0]
        if value & 0xff87 == 0x4700:
            raw_thumb_bx += 1
        if off >= 0xc0 and value & 0xff00 == 0xb500:
            prologues.add(BASE+off)
    known_instr = {pc for result in scanner.results.values() for pc in result['instructions']}
    main_end = max(pc for pc in known_instr if BASE <= pc < BASE+0x100000)
    sweep_candidates = []
    for address in sorted(prologues):
        off = address-BASE
        if address in known_instr or off in scanner.literal_bytes:
            continue
        # The connected main bank is grounded by control flow. Outside it require
        # pointer corroboration; never sweep arbitrary assets into executable code.
        if address <= main_end or pointers[address]:
            sweep_candidates.append(address)
            scanner.seed(address, 'Thumb', 'prologue candidate' if address <= main_end else 'pointer and prologue candidate')
    # Include pointer-only leaf callbacks inside the connected main bank.
    for address in sorted(pointers):
        if BASE+0xc0 <= address <= main_end and address not in known_instr and address-BASE not in scanner.literal_bytes:
            scanner.seed(address, 'Thumb', 'pointer candidate')
    scanner.drain()
    # Rewalk with the full entry set to stop at separately discovered functions.
    for key in list(scanner.results):
        scanner.results[key] = scanner.walk(*key)
    scanner.drain()
    # ARM table targets can expose code previously decoded as Thumb candidates.
    # Remove weak conflicting starts only when an ARM CFG owns those bytes.
    # Independent direct-call/audit evidence in both modes is kept as a conflict.
    arm_owned = {scanner.physical(pc)+i for (address, mode), result in scanner.results.items() if mode == 'ARM'
                 for pc, length in result['instructions'].items() for i in range(length)}
    mode_conflicts, discarded_modes = [], []
    for key in list(scanner.entries):
        if key[1] == 'Thumb' and scanner.physical(key[0]) in arm_owned:
            evidence = scanner.entries[key]['evidence']
            if all('candidate' in e for e in evidence):
                discarded_modes.append({'address': key[0], 'mode': key[1], 'reason': 'owned ARM instruction bytes'})
                del scanner.entries[key]; scanner.results.pop(key, None)
            else:
                mode_conflicts.append({'address': key[0], 'mode': key[1], 'evidence': sorted(evidence)})
    if discarded_modes:
        for key in list(scanner.results):
            scanner.results[key] = scanner.walk(*key)
        scanner.drain()
    folded = []
    for key in list(scanner.entries):
        owned_elsewhere = any(key[0] in result['instructions'] for other, result in scanner.results.items() if other != key)
        if (key[0] in scanner.case_blocks or key[0] in scanner.internal_labels or stack_return(scanner, *key) and owned_elsewhere) and scanner.entries[key]['evidence'] <= {'pointer candidate'}:
            folded.append({'address': key[0], 'mode': key[1], 'reason': 'switch case block' if key[0] in scanner.case_blocks else 'fallthrough interior label' if key[0] in scanner.internal_labels else 'owned stack-return block'})
            del scanner.entries[key]; scanner.results.pop(key, None)
    if folded:
        for key in list(scanner.results):
            scanner.results[key] = scanner.walk(*key)
        scanner.drain()
    for table in dispatch_config['observed_dispatch_tables']:
        for result in scanner.results.values():
            for record in result['transfer_records']:
                if scanner.physical(record['site']) in table['consumer_sites']:
                    record.update(kind='observed_table_call', targets=phase_targets(table, scanner.physical(record['site'])), targets_complete=False,
                                  table_name=table['name'], table_rom_offset=table['rom_offset'],
                                  table_bytes=4*table['count'], limitation=table['limitation'])
    annotate_records(scanner.results, scanner.physical,
                     evidence_config['indirect_producers'], evidence_config['fixed_targets'])
    # Merge RAM/ROM aliases at physical entry. They receive a single ROM tile.
    merged = {}
    for key, result in scanner.results.items():
        address, mode = key; off = scanner.physical(address)
        if not result['instructions']:
            continue
        if off not in merged:
            merged[off] = {'name': scanner.entries[key]['name'] or f'sub_{address:08X}',
                           'rom_offset': off, 'mode': mode, 'runtime_addresses': [],
                           'evidence': set(), 'instruction_offsets': set(), 'literal_offsets': set(),
                           'issues': set(), 'call_targets': set(), 'unresolved_transfer_offsets': set(), 'transfer_records': {}, 'return_offsets': set()}
        row = merged[off]
        row['runtime_addresses'].append(address)
        row['evidence'].update(scanner.entries[key]['evidence'])
        row['instruction_offsets'].update(scanner.physical(pc)+i for pc,n in result['instructions'].items() for i in range(n))
        row['literal_offsets'].update(result['literals'])
        row['issues'].update(result['issues'])
        row['return_offsets'].update(scanner.physical(pc) for pc in result['return_sites'])
        for record in result['transfer_records']:
            site = scanner.physical(record['site'])
            row['transfer_records'][site] = {**record, 'rom_offset': site}
        row['call_targets'].update(dest for dest,_ in result['calls'])
        row['unresolved_transfer_offsets'].update(scanner.physical(pc) for pc in result['unresolved_transfers'])
    # Extents are envelopes of decoded paths and local pools, clipped at the
    # next entry. These are estimates, not a compiler-owned function-size proof.
    starts = sorted(merged)
    rows = []
    for index, off in enumerate(starts):
        row = merged[off]
        limit = starts[index+1] if index+1 < len(starts) else len(data)
        owned = [p for p in row['instruction_offsets'] | row['literal_offsets'] if off <= p < limit]
        if not owned:
            continue
        end = max(owned)+1
        row['transfer_records'] = sorted(row['transfer_records'].values(), key=lambda r: r['rom_offset'])
        row['size'] = end-off
        row['extent_basis'] = 'CFG envelope estimate'
        row['entry_rom_offset'] = off
        row['body_rom_start'] = min(row['instruction_offsets'])
        row['body_rom_end'] = max(row['instruction_offsets'])+1
        row['boundary_confidence'] = 'control_flow_bounded' if not row['issues'] and row['return_offsets'] and all(off <= p < end for p in row['instruction_offsets']) else 'provisional'
        # Preserve full observations until the final ownership overlay.
        row['status'] = 'candidate' if any('candidate' in e for e in row['evidence']) and not any(e in row['evidence'] for e in ('direct call', 'bounded audit', 'audited RAM entry', 'audited dispatch entry', 'resolved literal transfer')) else 'mapped_code'
        row['group'] = 'Copied audio / ARM' if 0xfda478 <= off < 0xfdba28 else ('Startup / ARM' if off < 0x2a0 else f'ROM {0x0800+off//0x10000:04X}xxxx')
        for field in ('evidence', 'issues', 'call_targets', 'runtime_addresses', 'unresolved_transfer_offsets', 'return_offsets'):
            row[field] = sorted(set(row[field]))
        if off >= 0x100000 and row['group'] != 'Copied audio / ARM' and not row['call_targets']:
            continue  # Uncorroborated pointer/prologue coincidences stay unresolved.
        rows.append(row)
    audited = []
    for known in overlay(bounded['unconverted_extents'], source_code):
        off = known['rom_offset']
        discovered = merged.get(off, {})
        audited.append({**discovered, **{k: known[k] for k in ('name', 'rom_offset', 'size')},
                        'status': 'mapped_code', 'extent_basis': 'bounded audit', 'boundary_confidence': 'bounded audit', 'entry_rom_offset': off,
                        'group': 'Startup / ARM' if off < 0x2a0 else f'ROM {0x0800+off//0x10000:04X}xxxx'})
    rows = overlay(rows, audited)
    # Do not emit sets retained in rejected/overlaid discovery records.
    for row in rows:
        for field in ('evidence', 'issues', 'call_targets', 'runtime_addresses', 'unresolved_transfer_offsets', 'return_offsets'):
            row[field] = sorted(set(row.get(field, ())))
    finalize_extent_observations(rows)
    audio = next(c for c in ram['copies'] if c['name'] == 'audio_iwram')
    ewram = next(c for c in ram['copies'] if c['name'] == 'initial_ewram')
    zero_start = audio['rom_offset']+0x115c
    if any(data[zero_start:audio['rom_offset']+audio['size']]):
        raise ValueError('Audio zero-initialization extent changed')
    data_regions = [
        {'name': 'Cartridge header', 'rom_offset': 4, 'size': 0xbc, 'status': 'mapped_data'},
        {'name': 'Audio zero initialization', 'rom_offset': zero_start,
         'size': audio['rom_offset']+audio['size']-zero_start, 'status': 'mapped_data'},
        {'name': 'Initial EWRAM data image', 'rom_offset': ewram['rom_offset'],
         'size': ewram['size'], 'status': 'mapped_data'}]
    for table in dispatch_config['observed_dispatch_tables']:
        data_regions.append({'name': table['name'], 'rom_offset': table['rom_offset'],
                             'size': table['count']*4, 'status': 'mapped_data'})
    for table in observed_records:
        data_regions.append({'name': table['name'], 'rom_offset': table['rom_offset'],
                             'size': table['observed_rows']*table['record_stride'], 'status': 'mapped_data'})
    result = {'target': 'us-eu', 'reference_sha256': identity['sha256'], 'rom_bytes': len(data),
              'complete_rom_partition': True, 'complete_code_inventory': False,
              'decoder': {'name': 'Capstone', 'version': capstone_version},
              'method': 'ARM/Thumb recursive control flow with ARM7 guards; whole-ROM aligned pointers, Thumb/ARM weak signatures; separate rooted census and estimated extents',
              'limitations': ['Control-flow bounded means decoded paths terminate or loop; it does not prove compiler ownership, stack balance or runtime reachability.',
                              'Static discovery is not proof of function boundaries or reachability.',
                              'Indirect jumps and jump tables can hide code; unresolved bytes may include code, pools, data and padding.',
                              'Tiles include estimated envelopes and local literals; copied RAM code is counted once at ROM load offsets.',
                              'Self-modifying audio paths are decoded from the original image only.'],
              'folded_block_entries': folded, 'discarded_mode_candidates': discarded_modes, 'mode_conflicts': mode_conflicts,
              'transfer_records': sorted({r['rom_offset']: r for row in rows for r in row.get('transfer_records', [])}.values(), key=lambda r: r['rom_offset']),
              'unresolved_indirect_call_sites': unresolved_callback_sites(rows),
              'initial_connected_entries': graph_count, 'connected_main_last_instruction': main_end,
              'unresolved_transfer_sites': sorted({p for r in rows for p in r['unresolved_transfer_offsets']}), 'whole_rom_prologue_hits': len(prologues),
              'sweep_seed_count': len(sweep_candidates),
              'weak_whole_ROM_survey': {'aligned_words_examined': len(data)//4,
                  'Thumb_halfwords_examined': len(data)//2,
                  'raw_BX_patterns': {'ARM': raw_arm_bx, 'Thumb': raw_thumb_bx},
                  'ARM_signature_counts': {name: len(values) for name, values in arm_signatures.items()},
                  'ARM_signature_pointer_coincidences': sorted({address for values in arm_signatures.values() for address in values if arm_pointers[address]}),
                  'ARM_signatures_seeded_as_code': False,
                  'limitation': 'Signatures, raw BX words and pointer coincidences do not prove code, function entries or absence of other code.'},
              'entry_count': len({r['entry_rom_offset'] for r in rows}), 'extent_count': len(rows),
              'mapped_extent_bytes': sum(r['size'] for r in rows), 'rows': rows,
              'source_owned_data_regions': source_data,
              'data_regions': data_regions, 'partition': partition(rows+data_regions, len(data)),
              'input_sha256': {p: hashlib.sha256((ROOT/p).read_bytes()).hexdigest() for p in
                              ('tools/inventory_rom.py', 'tools/control_flow.py', 'tools/inventory_partition.py', 'tools/ram_copies.py', 'tools/indirect_evidence.py', 'tools/fixed_target_proof.py', 'tools/inventory_census.py', 'config/code-evidence-us-eu.json', 'config/ram-map-us-eu.json', 'config/indirect-transfers-us-eu.json', 'config/progress-regions-us-eu.json', 'config/build-us-eu.json', 'config/analysis-requirements.txt', *sorted(evidence_inputs))}}
    result['inventory_schema_version'] = 2
    result['historical_mapped_extent_baseline'] = 319640
    result['code_census'] = census(scanner, strong_entries, strong_results,
        rows=rows, data_regions=data_regions+source_data,
        source_code=[{**f, 'source_kind': f.get('kind', 'compiled_c'),
                      'mode': f.get('mode', 'Thumb')}
                     for f in manifest['functions']+manifest.get('assembly', [])],
        quality_annotations=evidence_config['quality_annotations'])
    verify_census(result['code_census'], len(data))
    out = ROOT/'assets/rom-inventory.json'
    out.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps({k: result[k] for k in ('entry_count', 'initial_connected_entries', 'whole_rom_prologue_hits', 'sweep_seed_count', 'mapped_extent_bytes')}, indent=2))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
