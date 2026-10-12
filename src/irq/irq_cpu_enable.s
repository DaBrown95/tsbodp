/* ARM CPSR glue: change the IRQ mask while preserving r0. Excluded from C. */
.arm
.text
.global irq_cpu_enable
.type irq_cpu_enable, %function
irq_cpu_enable:
    stmdb sp!, {r0}
    mrs r0, cpsr
    bic r0, r0, #0x80
    msr cpsr_fc, r0
    ldmia sp!, {r0}
    bx lr
.size irq_cpu_enable, .-irq_cpu_enable
