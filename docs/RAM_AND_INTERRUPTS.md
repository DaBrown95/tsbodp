> Internal AI scratch notes. Reader-facing setup and project information belong in the root README.

# Copied RAM map and interrupt milestone

Target: USA/Europe revision 0, SHA-1
`fb5662172fadebf4577f6f6f163741fc041c11e6`. This is a static analysis of the
original image. Run `make ram-map`, `make build`, `make compare`, and `make test`.

## Copies and execution addresses

| Copy | ROM source | RAM destination | Length | Evidence and classification |
| --- | --- | --- | --- | --- |
| Startup audio | `0x08FDA478` | `0x03000000` | `0x15B0` | Startup literals at ROM `0x114`; ARM entries reached from ROM veneers and IRQ table. Mixed instructions, pools, tables and initialization. |
| Startup EWRAM | `0x08FDBA28` | `0x02000000` | `0x27F8` | Startup literals at ROM `0x120`; initial data, with only three nonzero bytes. No executable entry established. |
| IRQ installation | `0x08000160` | `0x03001BA0` | `0x200` | `irq_init` DMA3 source/destination/count, then IRQ vector write. Mixed copy, not 512 bytes of ARM instructions. |

Startup first points the IRQ vector at ROM `0x08000160`. Interrupt initialization
later copies 128 words and changes the vector at `0x03007FFC` to `0x03001BA0`.
The dispatcher's established ARM extent is ROM `0x160..0x288`, mapping to RAM
`0x03001BA0..0x03001CC8`. Its table-address pool maps from ROM `0x2A4` to RAM
`0x03001CE4`. The intervening Thumb startup helper and later bytes are also
copied, but are not thereby proven to be dispatcher instructions.

The audio copy has a zero first word and a confirmed ARM IRQ entry at
`0x03000004`; default IRQ table index 3 points there. ROM veneers establish
entries at RAM `0x03000094`, `0x030002EC`, `0x03000320`, `0x030003E8`,
`0x03000434`, `0x030004B4`, `0x03000578`, and `0x03001080`.
Loaded pointers also support entries at `0x03000AB4` and `0x03000BF0`.
The final `0x454` bytes are zero initialization. This is not a complete
instruction/data partition or proof of all function boundaries.

The IRQ at `0x03000074` writes the existing `bx lr` instruction to
`0x0300004C`, changing its subsequent path. The routine at `0x03000BF0` changes
shift fields at eight ARM instruction addresses, recorded in the map. These
are executable RAM and mutable instruction state; a static ROM disassembly
alone cannot describe every runtime state. The `player.c` revision string is
consistent with the previously investigated Krawall engine, without proving
an exact upstream version.

`config/ram-map-us-eu.json` records addresses, phases, entries, pointer evidence
and mutable instruction sites. `tools/map_ram.py` checks reference identity,
startup and DMA literals and entry pointers, then emits copied images and a
local report under `analysis/us-eu/ram/`. This directory stays ignored.

## Connected interrupt subsystem

Fourteen new accepted C functions extend the earlier five. They cover DMA
installation, default interrupt enables, restoring table entries, three
callback setters, VCount enable/disable, the default VBlank callback, HBlank
and VCount handlers, Timer 0 and combined Timer 3/serial handling, and the
no-op callback. The manifest owns every accepted extent, including pools and
alignment. Total: **19 functions, 676 bytes**.

The reconstructed context pointer at `0x03004280` refers to storage at
`0x030042D0`. Its first three fields are callbacks, followed by counters and
still-unknown fields. The IRQ table is at `0x03004290`, initialized from 13
entries at ROM `0x08053558`. Software IRQ flags are at `0x03001DA0`, distinct
from the BIOS flags at `0x03007FF8`. The combined Timer 3/serial table entry's
recovered handler acknowledges `0x40`; it must not be “corrected” to `0xC0`.
These names are authored descriptions, not recovered original identifiers.

The subsequent interrupt milestone adds the VBlank wrapper at ROM `0x1F680`
(468 bytes) and wait at `0x1F970` (40 bytes): **21 matching C functions,
1,184 bytes**. [Wrapper evidence](VBLANK_RECONSTRUCTION.md) records the
DMA0 OAM handoff, nested-entry guard, context counters and audio coordination.
The wait clears software VBlank bit zero and spins on volatile halfword reads;
an explicit loop mask assigned after the clear reproduces the original
register lifetime. Earlier loop candidates and complete raw comparisons are
retained locally. Changing the mask from one to two is rejected.

The ARM dispatcher, CPU IRQ enable/disable helpers and distant shared literal
pool are now explicit assembly: **352 verified glue bytes**, excluded from C
coverage. The priority macro expresses the observed handler-table order.
The dispatcher saves SPSR/IE/IME, acknowledges one selected source, enables
nested sources masked by `0x20F4`, switches to system mode for the handler,
then restores the IRQ context. The Game Pak branch writes its selected value
to the sound register and loops. No runtime execution is claimed.

The dispatcher code owns only `0x160..0x288`; its separate pool owns
`0x2A0..0x2A8`. The intervening Thumb startup copy helper remains unconverted.
The pool aliases preserve the same PC-relative displacements in ROM and after
the 512-byte IWRAM copy; the full-ROM link compares both source extents.
Real source mutations of each glue region must fail comparison. Audio ARM
code remains unconverted, including the self-modifying mixer.

External Thumb function symbols are declared as Thumb to avoid invented ARM
interworking veneers. The two pool-free callback units express zero alignment
with a translation-unit assembly alignment directive; no original instruction
body is embedded. The linker checks each entire extent at its original address.
Headers and source snapshots, commands, objects and failures remain local.

## Complete ROM layout, partial source reconstruction

`make build` first reruns the pinned compiler/source gate. It links accepted C
objects with assembly `incbin` sections for every remaining original region,
using explicit addresses and size assertions. There is no post-link byte
repair, mask, header fix, or substitution of compiled function extents. The
final ELF layout and unresolved relocations are checked before binary output.

The complete **16,777,216-byte** output matches the reference. At the interrupt
milestone **16,775,680 bytes remain unconverted**, including code, header,
assets and padding. This count
is not a code decompilation percentage. Final output is
`build/us-eu/bustin-out.gba`; retained runs include the linker map, script,
objects, coverage ledger and report. A real brightness-clamp source change
from 16 to 15 must produce a same-size linked ROM with differing bytes. The
original bounded setter negative control also remains required.

No runtime/gameplay validation or historical compiler identification is
claimed. Revision 1 remains an audited reference, not a supported build.

## Ghidra workflow

Ghidra is useful for larger callers, shared structures and callback analysis.
The exported images and map support analyzing code at its execution address.
Ghidra was not installed or executed for this milestone.

Import the ROM at `0x08000000` using ARM little-endian ARMv4T settings. Add
initialized memory blocks from the three local exports at their RAM addresses,
or import each export as a separate raw ARM program at its indicated base.
Keep the original ROM block as the load-address evidence. Mark the established
RAM entries as ARM (`TMode=0`), and ROM Thumb functions as Thumb (`TMode=1`).
Do not auto-disassemble the nearly empty EWRAM block or all bytes of the mixed
IRQ copy. Name globals and apply the context layout in `include/irq.h`; leave
unknown fields unknown. Annotate self-modifying sites and analyze runtime
snapshots separately when they become available.

Treat decompiler output as candidate C and verify it through the existing
compile/link/all-byte gates. Official guidance:
[Ghidra memory maps, context and decompiler types](https://ghidra.re/ghidra_docs/GhidraClass/Intermediate/Intermediate_Ghidra_Student_Guide.html).
The IRQ register interpretation follows the primary
[Tonc interrupt reference](https://gbadev.net/tonc/interrupts.html).

The next connected targets are the installed frame callback, input polling,
background and palette transfers, frame-synchronized display transitions,
and audio coordination using the established execution-address map. The fixed
comparison baseline for this goal is **319,640 mapped extent bytes**, measured
on 12 October 2026. It is an earlier static estimate, not a complete inventory
of game code or a source coverage denominator.
