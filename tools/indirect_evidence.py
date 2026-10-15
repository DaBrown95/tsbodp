"""Validate static table/producer evidence without granting source credit."""
import hashlib
import struct


def record_tables(data, tables, physical):
    """Return observed callback fields; an observed prefix never closes an index."""
    result = []
    names = set()
    for table in tables:
        name = table['name']
        start, rows, stride = (table[k] for k in
                               ('rom_offset', 'observed_rows', 'record_stride'))
        fields = table['callback_fields']
        if (name in names or any(type(v) is not int for v in (start, rows, stride))
                or start < 0 or rows <= 0 or stride <= 0 or stride % 4
                or start % 4 or not fields or len(set(fields)) != len(fields)
                or any(type(f) is not int or f < 0 or f % 4 or f + 4 > stride
                       for f in fields)
                or start + rows * stride > len(data)
                or table.get('targets_complete') is not False
                or not table.get('evidence')):
            raise ValueError('Invalid observed record-table evidence')
        names.add(name)
        raw = data[start:start + rows * stride]
        if hashlib.sha256(raw).hexdigest() != table['region_sha256']:
            raise ValueError('Observed record-table prefix differs from ROM')
        values = {field: [struct.unpack_from('<I', raw, row * stride + field)[0]
                          for row in range(rows)] for field in fields}
        for value in (v for column in values.values() for v in column if v):
            address = value & ~1
            if physical(address) is None or address % (2 if value & 1 else 4):
                raise ValueError('Observed callback target is unmapped or misaligned')
        result.append({**table, 'columns': values,
                       'targets': sorted({v for column in values.values()
                                          for v in column if v})})
    return result


def phase_targets(table, site):
    """Select the observed phase column, preserving an open runtime domain."""
    fields = table.get('consumer_fields')
    if fields is None:
        return sorted({value & ~1 for value in table['entries'] if value})
    field = fields.get(str(site))
    stride, rows = table['record_stride'], table['record_count']
    if (type(field) is not int or field not in table['phase_fields']
            or stride % 4 or len(table['entries']) != rows * stride // 4):
        raise ValueError('Invalid phase-column consumer evidence')
    return sorted({table['entries'][row * stride // 4 + field // 4] & ~1
                   for row in range(rows)
                   if table['entries'][row * stride // 4 + field // 4]})


def validate_fixed_target(row, data, functions, source_hash, physical):
    """A pinned matching source and its ROM literal establish a fixed producer."""
    owner = next((f for f in functions if f['name'] == row['owner']), None)
    site, literal, target = (row[k] for k in
                              ('rom_offset', 'literal_rom_offset', 'target'))
    if (owner is None or any(type(v) is not int for v in (site, literal, target))
            or not owner['rom_offset'] <= site < owner['rom_offset'] + owner['size']
            or literal % 4 or not owner['rom_offset'] <= literal
            or literal + 4 > owner['rom_offset'] + owner['size']
            or source_hash(owner) != row['source_sha256']
            or struct.unpack_from('<I', data, literal)[0] != target
            or physical(target & ~1) is None
            or (target & ~1) % (2 if target & 1 else 4)):
        raise ValueError('Fixed producer source, site, literal or target differs')
    return target & ~1


def annotate_records(results, physical, evidence, fixed):
    """Attach producer facts only to transfers actually found by the decoder."""
    producers = {row['rom_offset']: row for row in evidence}
    constants = {row['rom_offset']: row for row in fixed}
    if len(producers) != len(evidence) or len(constants) != len(fixed):
        raise ValueError('Duplicate indirect producer site')
    found = set()
    for result in results.values():
        for record in result['transfer_records']:
            site = physical(record['site'])
            if site in producers:
                record['producer_evidence'] = producers[site]
                found.add(site)
            if site in constants:
                record.update(kind='fixed_literal_call', targets_complete=True,
                              targets=[constants[site]['target'] & ~1],
                              target_origin='pinned_matching_source_and_ROM_literal',
                              limitation='Static producer only; copied-memory state and arguments remain separate.')
    if not set(constants) <= found:
        raise ValueError('Fixed producer annotation lacks a decoded transfer')


def literal_veneers(scanner, family):
    """Check adjacent PC-load/BX thunks, including a preserving wrapper."""
    from capstone.arm import ARM_INS_LDR, ARM_INS_BX, ARM_INS_BL, ARM_OP_MEM, ARM_REG_PC, ARM_REG_LR
    start, size = family['rom_offset'], family['size']
    if hashlib.sha256(scanner.data[start:start+size]).hexdigest() != family['region_sha256']:
        raise ValueError('Literal veneer family differs from ROM')
    seeds = []
    for row in family['entries']:
        entry, load, branch = (row[k] for k in ('entry_rom_offset', 'load_rom_offset', 'BX_rom_offset'))
        if not start <= entry <= load < branch < start+size:
            raise ValueError('Invalid literal veneer instruction bounds')
        decode = lambda off: scanner.decode(0x08000000+off, 'Thumb')
        ins, bx = decode(load), decode(branch)
        if (ins is None or bx is None or ins.id != ARM_INS_LDR or bx.id != ARM_INS_BX
                or len(ins.operands) != 2 or ins.operands[1].type != ARM_OP_MEM
                or ins.operands[1].mem.base != ARM_REG_PC or ins.operands[1].mem.index
                or ins.operands[0].reg != bx.operands[0].reg):
            raise ValueError('Literal load/BX register provenance differs')
        literal = ((load+4) & ~3)+ins.operands[1].mem.disp
        if (literal != row['literal_rom_offset'] or not start <= literal <= start+size-4
                or struct.unpack_from('<I', scanner.data, literal)[0] != row['target']
                or scanner.physical(row['target'] & ~1) is None):
            raise ValueError('Literal veneer target differs')
        if entry == load:
            if branch != load+2:
                raise ValueError('Simple veneer has intervening instructions')
        else:
            push, call, pop = decode(entry), decode(load+2), decode(load+6)
            if (load != entry+2 or branch != load+8 or push.mnemonic != 'push'
                    or [o.reg for o in push.operands] != [ins.operands[0].reg, ARM_REG_LR]
                    or call.id != ARM_INS_BL or call.operands[0].imm != 0x08000000+branch
                    or pop.mnemonic != 'pop'
                    or [o.reg for o in pop.operands] != [ins.operands[0].reg, ARM_REG_PC]):
                raise ValueError('Preserving veneer control flow differs')
        seeds.append(0x08000000+entry)
    return seeds
