/* Observed Thumb BIOS handoff. Explicit low-level glue; excluded from C. */
.syntax unified
.thumb
.text
.global resource_bios_swi_13
.type resource_bios_swi_13, %function
.thumb_func
resource_bios_swi_13:
    svc #0x13
    bx lr
.size resource_bios_swi_13, .-resource_bios_swi_13
