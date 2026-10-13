/* Observed Thumb BIOS handoff. Explicit low-level glue; excluded from C. */
.syntax unified
.thumb
.text
.global resource_bios_swi_14
.type resource_bios_swi_14, %function
.thumb_func
resource_bios_swi_14:
    svc #0x14
    bx lr
.size resource_bios_swi_14, .-resource_bios_swi_14
