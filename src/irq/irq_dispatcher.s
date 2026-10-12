/* ARM exception glue, executed from ROM at startup and after the IWRAM copy.
 * This is explicit assembly, excluded from matching C coverage. */
.syntax unified
.arm
.text
.balign 4
.global irq_dispatcher
.type irq_dispatcher, %function
irq_dispatcher:
/* Pool ownership is separate; these local aliases express its relative layout. */
.set .Lmask_pool, irq_dispatcher + 0x140
.set .Ltable_pool, irq_dispatcher + 0x144
    mov r3, #0x04000000
    add r3, r3, #0x200
    ldr r2, [r3]                 /* IE and IF snapshot */
    ldrh r1, [r3, #8]            /* IME snapshot */
    mrs r0, spsr
    stmdb sp!, {r0-r3, lr}
    mov r0, #1
    strh r0, [r3, #8]
    and r1, r2, r2, lsr #16
    mov ip, #0

/* Table order defines priority. r0 retains the selected acknowledgement. */
.macro next_irq mask
    ands r0, r1, #\mask
    bne .Ldispatch
    add ip, ip, #4
.endm
    next_irq 0xc0                /* Timer 3 / serial */
    next_irq 1                   /* VBlank */
    next_irq 4                   /* VCount */
    next_irq 0x10                /* Timer 1 */
    next_irq 2                   /* HBlank */
    next_irq 8                   /* Timer 0 / audio */
    next_irq 0x20                /* Timer 2 */
    next_irq 0x100
    next_irq 0x200
    next_irq 0x400
    next_irq 0x800
    next_irq 0x1000
    ands r0, r1, #0x2000
    strbne r0, [r3, #-0x17c]     /* Game Pak IRQ stops this path */
.Lgamepak_stop:
    bne .Lgamepak_stop
.Ldispatch:
    strh r0, [r3, #2]
    ldr r1, .Lmask_pool
    bic r2, r2, r0
    and r1, r1, r2
    strh r1, [r3]

/* Call the table handler on the system stack, permitting nested IRQs. */
    mrs r3, cpsr
    bic r3, r3, #0xdf
    orr r3, r3, #0x1f
    msr cpsr_fc, r3
    ldr r1, .Ltable_pool
    add r1, r1, ip
    ldr r0, [r1]
    stmdb sp!, {lr}
    add lr, pc, #0
    bx r0
    ldmia sp!, {lr}
    mrs r3, cpsr
    bic r3, r3, #0xdf
    orr r3, r3, #0x92
    msr cpsr_fc, r3
    ldmia sp!, {r0-r3, lr}
    strh r2, [r3]
    strh r1, [r3, #8]
    msr spsr_fc, r0
    bx lr
.size irq_dispatcher, .-irq_dispatcher
