/* Hardware reset establishes the IRQ and system stacks and installs the BIOS
 * IRQ-vector callback before entering Thumb code. The Thumb installation ABI
 * passes its end pointer in r4 to startup_copy_words, and enters the ordinary
 * game entry through an explicit ARM/Thumb handoff. This is startup assembly,
 * not a replacement for the still-unconverted C game entry. */
.syntax unified
.arm
.text
.balign 4
.global startup_reset
.type startup_reset, %function
startup_reset:
/* ADR has no external relocation on ARM7. The dispatcher is a separate source
 * extent at this fixed displacement, as required by its ROM/RAM copy layout. */
.set .Lirq_entry, startup_reset + 0xa0
    mov r0, #0x12               /* IRQ mode */
    msr cpsr_fc, r0
    ldr sp, .Lirq_stack
    mov r0, #0x1f               /* System mode */
    msr cpsr_fc, r0
    ldr sp, .Lsystem_stack
    ldr r1, .Lbios_irq_vector
    adr r0, .Lirq_entry
    str r0, [r1]
    add r0, pc, #1
    bx r0

.thumb
.thumb_func
.Linstall_images:
    ldr r1, .Laudio_load
    ldr r2, .Laudio_start
    ldr r4, .Laudio_end
    bl startup_copy_words
    ldr r1, .Lewram_load
    ldr r2, .Lewram_start
    ldr r4, .Lewram_end
    bl startup_copy_words
    ldr r1, .Lgame_entry
    mov lr, pc
    bx r1
    b startup_reset

/* Original placement is part of the PC-relative startup interface. The stack,
 * vector and image addresses are data; no instruction bodies are embedded. */
.balign 4
.Lsystem_stack:    .word startup_system_stack
.Lirq_stack:       .word startup_irq_stack
.Lbios_irq_vector: .word startup_bios_irq_vector
.Laudio_load:      .word startup_audio_load
.Laudio_start:     .word startup_audio_start
.Laudio_end:       .word startup_audio_end
.Lewram_load:      .word startup_ewram_load
.Lewram_start:     .word startup_ewram_start
.Lewram_end:       .word startup_ewram_end
.Lgame_entry:      .word startup_game_entry
.size startup_reset, .-startup_reset
