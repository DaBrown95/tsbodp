/* Cartridge entry runs in ARM state before a C execution environment exists.
 * The header separates this branch from the reset routine. Hardware startup
 * assembly, excluded from matching C coverage. */
.syntax unified
.arm
.text
.balign 4
.global rom_entry
.type rom_entry, %function
rom_entry:
    b startup_reset
.size rom_entry, .-rom_entry
