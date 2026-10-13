/* Observed Thumb BIOS handoff. Explicit low-level glue; excluded from C. */
.syntax unified
.thumb
.text
.global resource_bios_swi_11
.type resource_bios_swi_11, %function
.thumb_func
resource_bios_swi_11:
    svc #0x11
    bx lr
.size resource_bios_swi_11, .-resource_bios_swi_11
