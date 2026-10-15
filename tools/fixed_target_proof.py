"""Prove a Thumb call register after caller validates ROM/source ownership.

Ordinary calls clobber r0-r3/ip/lr and preserve r4-r11 by the ARM ABI.
No copied-memory immutability or arbitrary callee ABI correctness is proved.
"""
import struct
from collections import deque

from capstone.arm import (ARM_INS_B, ARM_INS_BL, ARM_INS_BX, ARM_OP_MEM, ARM_OP_REG,
                          ARM_REG_PC, ARM_REG_LR, ARM_REG_R0, ARM_REG_R1,
                          ARM_REG_R2, ARM_REG_R3, ARM_REG_R12,
                          ARM_CC_AL, ARM_CC_INVALID)
from control_flow import constant_result, stack_return, thumb_switch


def prove_fixed_target(scanner, owner, site, target):
    """Prove every rooted path at physical ``site``; target retains mode bit."""
    if (type(site) is not int or type(target) is not int
            or owner.get('mode', 'Thumb') != 'Thumb'):
        raise ValueError('Fixed target proof requires a Thumb owner and integers')
    start, size = owner['rom_offset'], owner['size']
    entry = owner.get('ram_address', 0x08000000 + start)
    result = scanner.results.get((entry, 'Thumb'))
    pc_site = entry + site - start
    if (not start <= site < start + size or result is None
            or scanner.physical(entry) != start
            or scanner.physical(target & ~1) is None
            or (target & ~1) % (2 if target & 1 else 4)
            or pc_site not in result['instructions']):
        raise ValueError('Fixed target lacks an owned decoded call site')
    code = {pc for pc in result['instructions'] if entry <= pc < entry + size}
    call = scanner.decode(pc_site, 'Thumb')
    if call.id != ARM_INS_BL:
        raise ValueError('Fixed target site is not a Thumb BL')
    stub = scanner.decode(call.operands[0].imm, 'Thumb')
    if (stub is None or stub.id != ARM_INS_BX
            or stub.operands[0].reg in (ARM_REG_PC, ARM_REG_LR)):
        raise ValueError('Fixed target call lacks a register veneer')
    target_reg = stub.operands[0].reg
    incoming, todo = {entry: {}}, deque([entry])
    clobbers = (ARM_REG_R0, ARM_REG_R1, ARM_REG_R2, ARM_REG_R3,
                ARM_REG_R12, ARM_REG_LR)
    iterations = 0
    while todo:
        pc = todo.popleft()
        iterations += 1
        if iterations > max(128, len(code) * 32):
            raise ValueError('Fixed target constant proof did not converge')
        ins = scanner.decode(pc, 'Thumb')
        state = incoming[pc].copy()
        conditional = ins.cc not in (ARM_CC_AL, ARM_CC_INVALID)
        successor = [pc + ins.size]
        if ins.id == ARM_INS_BL:
            for reg in clobbers:
                state.pop(reg, None)
        elif ins.id == ARM_INS_B:
            successor = [ins.operands[0].imm] + (successor if conditional else [])
        elif ins.id == ARM_INS_BX:
            if ins.op_str != 'lr' and not stack_return(scanner, pc, 'Thumb'):
                raise ValueError('Unmodelled register control flow in owner')
            successor = []
        elif ARM_REG_PC in ins.regs_access()[1]:
            if ins.mnemonic.startswith(('pop', 'ldm')):
                successor = []
            else:
                switch = thumb_switch(scanner, pc)
                if switch is None:
                    raise ValueError('Unmodelled PC write in owner')
                successor = switch['targets']
        else:
            if conditional or ins.mnemonic == 'svc':
                raise ValueError('Unsupported conditional instruction or service')
            uses_pc = any(op.type == ARM_OP_REG and op.reg == ARM_REG_PC
                          for op in ins.operands[1:])
            computed = None if uses_pc else constant_result(ins, state, 'Thumb')
            loaded = None
            if (ins.mnemonic == 'ldr' and len(ins.operands) == 2
                    and ins.operands[1].type == ARM_OP_MEM
                    and ins.operands[1].mem.base == ARM_REG_PC
                    and not ins.operands[1].mem.index):
                literal = ((pc + 4) & ~3) + ins.operands[1].mem.disp
                off = scanner.physical(literal)
                if off is not None and start <= off and off + 4 <= start + size:
                    loaded = (ins.operands[0].reg,
                              struct.unpack_from('<I', scanner.data, off)[0])
            for reg in ins.regs_access()[1]:
                state.pop(reg, None)
            if computed:
                state[computed[0]] = computed[1]
            if loaded:
                state[loaded[0]] = loaded[1]
        for dest in successor:
            if not entry <= dest < entry + size:
                raise ValueError('Owner path falls outside its complete extent')
            if dest not in code:
                raise ValueError('Owner successor is not an existing instruction')
            old = incoming.get(dest)
            joined = state.copy() if old is None else {
                reg: value for reg, value in old.items() if state.get(reg) == value}
            if old is None or joined != old:
                incoming[dest] = joined
                todo.append(dest)
    if incoming.get(pc_site, {}).get(target_reg) != target:
        raise ValueError('Veneer register target is unknown or conflicts with evidence')
    return {'target': target & ~1, 'target_mode': 'Thumb' if target & 1 else 'ARM',
            'call_register': stub.reg_name(target_reg), 'rom_offset': site,
            'reached_instructions': len(incoming), 'iterations': iterations,
            'scope': 'All rooted owner paths; ordinary ARM call clobbers; no runtime claim'}
