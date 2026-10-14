/* Observed Thumb BIOS remainder handoff; explicit glue, zero matching C. */
.syntax unified
.text
.cpu arm7tdmi
.thumb
.balign 4
.global display_bios_remainder
.type display_bios_remainder, %function
.thumb_func
display_bios_remainder:
    svc 0x06
    adds r0, r1, #0
    bx lr
    .balign 4, 0
.size display_bios_remainder, .-display_bios_remainder
