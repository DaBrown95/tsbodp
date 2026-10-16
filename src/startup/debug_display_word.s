/* Register-transparent no$gba debugger adapter, reconstructed from its native
 * interface and the documented debug-message packet. No historical source-file
 * identity is claimed. Protocol: https://problemkaputt.de/gbahlp.htm
 *
 * The packet displays R0, so the adapter saves the caller's R0, reads the fixed
 * word, presents it, and restores R0 before returning. Other registers and flags
 * are untouched. All embedded halfwords/text/alignment below are packet data;
 * the final word is a pointer literal, not an instruction. */
.syntax unified
.arm
.text
.balign 4
.global startup_debug_display_word
.type startup_debug_display_word, %function
startup_debug_display_word:
    stmdb sp!, {r0}
    ldr r0, .Ldisplay_word_address
    ldr r0, [r0]
    mov ip, ip
    b .Lafter_message
    .hword 0x6464, 0
    .asciz "PRF %r0%"
    /* The documented GNU .align 4 spelling is a 16-byte boundary. */
    .balign 16, 0
.Lafter_message:
    ldmia sp!, {r0}
    bx lr
.Ldisplay_word_address:
    .word g_debug_display_word
.size startup_debug_display_word, .-startup_debug_display_word
