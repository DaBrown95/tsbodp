/* Observed Thumb BIOS handoff. Explicit low-level glue; excluded from C. */
.syntax unified
.thumb
.text
.global resource_bios_swi_0c
.type resource_bios_swi_0c, %function
.thumb_func
resource_bios_swi_0c:
    svc #0x0c
    bx lr
.size resource_bios_swi_0c, .-resource_bios_swi_0c
