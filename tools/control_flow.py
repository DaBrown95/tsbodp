"""Conservative ARM7 transfer recognition from instruction and table evidence."""
import struct
from capstone.arm import ARM_OP_IMM, ARM_OP_REG, ARM_OP_MEM, ARM_REG_PC


def thumb_switch(scanner, pc):
    """Recognize agbcc's guarded word-table MOV pc dispatch, including BLS/B.

    The guard, scaled index, address load and final transfer must agree. Every
    target must be even (MOV keeps Thumb state), local and decodable. Table words
    are data, while case destinations are blocks of the current function.
    """
    seq = [scanner.decode(pc-delta, 'Thumb') for delta in (8, 6, 4, 2, 0)]
    if any(i is None or i.size != 2 for i in seq):
        return None
    shift, base_load, add, load, jump = seq
    if (shift.mnemonic != 'lsls' or len(shift.operands) != 3
            or shift.operands[2].type != ARM_OP_IMM or shift.operands[2].imm != 2
            or base_load.mnemonic != 'ldr' or add.mnemonic != 'adds'
            or load.mnemonic != 'ldr' or jump.mnemonic != 'mov'
            or jump.op_str.split(',')[0] != 'pc'):
        return None
    index, scaled = shift.operands[1].reg, shift.operands[0].reg
    table_reg = base_load.operands[0].reg
    if (len(base_load.operands) != 2 or base_load.operands[1].type != ARM_OP_MEM
            or base_load.operands[1].mem.base != ARM_REG_PC
            or base_load.operands[1].mem.index
            or len(add.operands) != 3 or [o.reg for o in add.operands] != [scaled, scaled, table_reg]
            or len(load.operands) != 2 or load.operands[0].reg != scaled
            or load.operands[1].type != ARM_OP_MEM or load.operands[1].mem.base != scaled
            or load.operands[1].mem.index or load.operands[1].mem.disp
            or jump.operands[1].reg != scaled):
        return None
    branch = scanner.decode(pc-10, 'Thumb')
    if branch is None:
        return None
    if branch.mnemonic == 'bhi':
        compare = scanner.decode(pc-12, 'Thumb')
        guard = branch
    elif branch.mnemonic == 'b':
        guard = scanner.decode(pc-12, 'Thumb')
        compare = scanner.decode(pc-14, 'Thumb')
        if guard is None or guard.mnemonic != 'bls' or guard.operands[0].imm != pc-8:
            return None
    else:
        return None
    if (compare is None or compare.mnemonic != 'cmp' or len(compare.operands) != 2
            or compare.operands[0].reg != index or compare.operands[1].type != ARM_OP_IMM):
        return None
    count = compare.operands[1].imm+1
    if not 1 <= count <= 256:
        return None
    literal = ((base_load.address+4)&~3)+base_load.operands[1].mem.disp
    literal_off = scanner.physical(literal)
    if literal_off is None or literal_off+4 > len(scanner.data):
        return None
    table = struct.unpack_from('<I', scanner.data, literal_off)[0]
    off = scanner.physical(table)
    if off is None or table % 4 or off+4*count > len(scanner.data):
        return None
    targets = list(struct.unpack_from('<'+'I'*count, scanner.data, off))
    table_end = table+4*count
    for dest in targets:
        if (dest & 1 or abs(dest-pc) > 0x20000 or table <= dest < table_end
                or scanner.physical(dest) is None):
            return None
        instruction = scanner.decode(dest, 'Thumb')
        if instruction is None or not scanner.arm7_instruction(instruction, 'Thumb'):
            return None
    return {'site': pc, 'kind': 'bounded_switch', 'targets_complete': True,
            'guard_address': guard.address, 'default_target': branch.operands[0].imm, 'table_rom_offset': off,
            'table_bytes': count*4, 'case_count': count, 'targets': sorted(set(targets))}


def constant_result(ins, constants, mode):
    """Track immediate/literal-derived moves and arithmetic; never guess memory."""
    operands = ins.operands
    if not operands or operands[0].type != ARM_OP_REG or any(op.shift.type for op in operands):
        return None

    def value(op):
        if op.type == ARM_OP_IMM:
            return op.imm
        if op.type == ARM_OP_REG:
            if op.reg == ARM_REG_PC:
                return ins.address+(4 if mode == 'Thumb' else 8)
            return constants.get(op.reg)
        return None

    operation = ins.mnemonic.rstrip('s')
    if operation == 'mov' and len(operands) == 2:
        result = value(operands[1])
    elif operation in ('add', 'sub', 'lsl') and len(operands) in (2, 3):
        left, right = (value(operands[0]), value(operands[1])) if len(operands) == 2 else (value(operands[1]), value(operands[2]))
        if left is None or right is None:
            return None
        result = left+right if operation == 'add' else left-right if operation == 'sub' else left << right if 0 <= right < 32 else None
    else:
        return None
    return None if result is None else (operands[0].reg, result & 0xffffffff)


def stack_return(scanner, pc, mode):
    """Recognize POP {reg}; [ADD sp,#imm]; BX reg, not arbitrary BX reg."""
    if mode != 'Thumb':
        return False
    jump = scanner.decode(pc, mode)
    before = scanner.decode(pc-2, mode)
    if jump is None or jump.mnemonic != 'bx' or before is None:
        return False
    if before.mnemonic == 'add' and before.op_str.startswith('sp,'):
        before = scanner.decode(pc-4, mode)
    return (before is not None and before.mnemonic == 'pop' and len(before.operands) == 1
            and before.operands[0].reg == jump.operands[0].reg)
