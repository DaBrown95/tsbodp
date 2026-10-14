/* Observed Thumb BIOS handoff. Explicit low-level glue; excluded from C. */
.syntax unified
.thumb
.text
.global view_bios_arctan2
.type view_bios_arctan2, %function
.thumb_func
view_bios_arctan2:
    svc #0x0a
    bx lr
.size view_bios_arctan2, .-view_bios_arctan2
