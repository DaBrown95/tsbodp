/* ARM CPSR glue: change the IRQ mask while preserving r0. Excluded from C. */
.arm
.text
.global irq_cpu_disable
.type irq_cpu_disable, %function
irq_cpu_disable:
    stmdb sp!, {r0}
    mrs r0, cpsr
    orr r0, r0, #0x80
    msr cpsr_fc, r0
    ldmia sp!, {r0}
    bx lr
.size irq_cpu_disable, .-irq_cpu_disable
