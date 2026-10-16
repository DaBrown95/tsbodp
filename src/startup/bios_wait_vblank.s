/* Thumb BIOS handoff used by the startup loop. No C arguments are consumed.
 * The wrapper clears scratch r2 before VBlankIntrWait; BIOS register effects
 * belong to that service. It then returns through the caller's LR. Explicit
 * hardware glue, with no recovered-C credit. */
.syntax unified
.cpu arm7tdmi
.thumb
.text
.balign 4
.equ BIOS_VBLANK_INTR_WAIT, 0x05
.global startup_bios_wait_vblank
.type startup_bios_wait_vblank, %function
.thumb_func
startup_bios_wait_vblank:
    movs r2, #0
    svc BIOS_VBLANK_INTR_WAIT
    bx lr
.size startup_bios_wait_vblank, .-startup_bios_wait_vblank
.balign 4, 0
