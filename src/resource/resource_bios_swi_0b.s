/* Observed Thumb BIOS handoff. Explicit low-level glue; excluded from C. */
.syntax unified
.thumb
.text
.global resource_bios_swi_0b
.type resource_bios_swi_0b, %function
.thumb_func
resource_bios_swi_0b:
    svc #0x0b
    bx lr
.size resource_bios_swi_0b, .-resource_bios_swi_0b
