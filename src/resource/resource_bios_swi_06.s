/* Observed Thumb BIOS quotient handoff. Explicit glue, excluded from C. */
.syntax unified
.text
.cpu arm7tdmi
.thumb
.balign 4
.global display_bios_div
.type display_bios_div, %function
.thumb_func
display_bios_div:
    svc 0x06
    bx lr
.size display_bios_div, .-display_bios_div
