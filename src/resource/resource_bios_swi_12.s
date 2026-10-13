/* Observed Thumb BIOS handoff. Explicit low-level glue; excluded from C. */
.syntax unified
.thumb
.text
.global resource_bios_swi_12
.type resource_bios_swi_12, %function
.thumb_func
resource_bios_swi_12:
    svc #0x12
    bx lr
.size resource_bios_swi_12, .-resource_bios_swi_12
