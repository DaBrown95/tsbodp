/* Observed Thumb BIOS handoff. Explicit low-level glue; excluded from C. */
.syntax unified
.thumb
.text
.global resource_bios_swi_15
.type resource_bios_swi_15, %function
.thumb_func
resource_bios_swi_15:
    svc #0x15
    bx lr
.size resource_bios_swi_15, .-resource_bios_swi_15
