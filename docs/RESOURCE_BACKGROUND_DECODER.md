# Resource decoders

The game has two decompressors that run from RAM: a background decoder
(assembly) and a tile-run decoder (C). The game copies each into IWRAM at
startup. This note records where the background decoder comes from and how
both were checked.

## Background decoder

[`background_decoder.s`](../src/resource/background_decoder.s) is the 812
bytes at ROM `0x080002EC..0x08000618`, also linked at its copied execution
address `0x03003370..0x0300369C`. It is 203 ARM instructions, with no literal
pool or alignment padding. The installer copies 848 bytes, which also covers
the first 36 bytes of the C frame scheduler that follows; those bytes belong
to the scheduler.

### Where the assembly comes from

The archived
[author index](https://web.archive.org/web/20040212223802id_/http://www.devrs.com/gba/asmcode.php)
lists Jeff Frohwein's PuCrunch v1.0612 as ARM assembly for ARM/Thumb GCC.
The [author's source package](https://web.archive.org/web/20150302021803id_/http://www.devrs.com/gba/files/armpuc.zip)
contains the whole ARM routine, including a halfword-output variant. The
game's routine matches it in register use and in the order of the algorithm
throughout:

| Portion of the routine | Bytes | What corresponds |
| --- | ---: | --- |
| Entry and header/table setup | 72 | Output, escape widths, ranked RLE table and sentinel state |
| Gamma and bit readers | 204 | R0 cursor, R5 value, R8 sentinel and R9 count; shared tails |
| Escape/literal/token decisions | 108 | R11 saved escape, common literal suffix and R10 pending byte |
| Short/long RLE | 128 | Gamma length extension and ranked byte codes below 32 |
| LZ position decoding | 76 | Gamma distance high part, extension bits, low byte and EOF |
| VRAM forward-copy paths | 188 | Pending-byte and distance-one cases, followed by halfword loops |
| Flush and return | 36 | Pending-byte flush, saved state and optional size output |

The private calls return a carry flag straight to conditional branches or ADC
instructions, keep packed parameters in R2 across calls, and share the same
outer register state. This is evidence that the whole routine was written in
assembly, not that a C version was hard to match.

The published source is an earlier version and does not assemble to the
game's bytes. The game's version has a compact header, word input, an
unrolled gamma prefix, halfword bulk copies and an optional decoded-size
output. Which revision it derives from is unknown. No licence for the ARM
translation was found, so that source is not included here. The assembly in
this repository was written independently from the game's instructions and
dataflow, with descriptive labels and constants, and does not copy the
upstream text. The Pucrunch algorithm is by Pasi Ojala; his later licence
statement does not give terms for a separate ARM translation.

### Interface

R0 holds the compressed input, R1 the output and R2 an optional pointer for
the decoded byte count (may be null). On return R0 holds the original
destination; callers treat the function as returning nothing. The display
caller passes a null R2, which its guarded epilogue and the boot observation
support. The tile decoder's count pointer is always supplied, which is a
different contract.

### Checks

The image equals the reference at both its ROM and RAM addresses. Five
changed-source controls alter the gamma limit, RLE threshold, EOF code, copy
step or decoded-size store; each assembles and is rejected by one byte. The
source uses assembly operations only, with no embedded ROM instruction data,
patches or masked comparisons.

Models of the original instructions run selected compressed inputs, and the
[boot observation](RUNTIME_OBSERVATIONS.md) sees one call. None of this covers
all input bounds, malformed streams, writable entry assignments, modifications
of the copied code or gameplay.

### Startup callback writer

The callback word at `0x030036C0` holds the entry of the background decoder.
The unresolved indirect call at ROM `0x0800E1B8` goes through it. Two startup
steps write that word:

- The memory initialiser starts a fixed-zero DMA3 fill of
  `0x030015B0..0x03007D00`, which covers the word and so zeroes it.
- The decoder installer then copies 848 bytes to `0x03003370`, ending just
  before the callback word, and stores the ARM entry `0x03003370` into it.

The game entry runs memory initialisation before decoder installation. The
direct-call graph from the eleven initialisation roots before installation
covers 74 functions, has no missing entry or unresolved transfer, and never
reaches `display_decode_background`. So in the normal startup path nothing
calls the decoder through this site synchronously, assuming the usual decoder,
ordinary-call and BIOS behaviour. Interrupt entry, unusual re-entry and later
writers to the word are not ruled out. The zero value before installation is
just stored data, not a second call target.

## Tile-run decoder

The [tile-run decoder](../src/resource/resource_decode_tile_runs.c) is the 504
bytes at ROM `0x0800B36C..0x0800B564`, linked for execution at
`0x030036D0..0x030038C8`. It is 126 ARM instructions with no literal pool or
alignment tail. The installer copies 528 bytes, which also includes the first
24 bytes of the map drawer that follows; those 24 bytes belong to the map
drawer. ROM and copied-RAM bytes are counted once.

The input is a stream of literal, repeated-byte and backward-copy runs that
ends with a zero command. A pending byte is combined with the next output byte
before each halfword store, and a final odd byte is flushed separately. The
source keeps the aligned halfword loops and the overlapping backward-copy
order. It assumes a valid stream, backing data, alignment and destination
size, and adds no bounds checks or handling of malformed streams.

One ordinary scratch variable holds the count field, then the distance, then
the odd-byte tail, in the phases the original uses. A short R2 low-field value
has a single producer and feeds the distance OR, and the R1 length feeds the
copy and repeat paths. This keeps the original's compare, shift and OR order
and the later register phases. The R14 byte and pair scratch values in the
leaf end before the saved return address is restored. R0, the output cursor,
is the value returned. The source adds no instructions, clobbers, extra
observations or artificial consumers.

The tile callback returns `void *`, the advanced output cursor, and still
writes the decoded byte count through its required third argument. Both shared
declarations, the provider prototype and the copy caller's local callback type
agree. All five callers ignore the return value, which fits the original's
postcondition but does not recover the original C prototype. The background
callback stays `void` with its optional count pointer, and the two-argument
resource dispatchers keep their unsigned count returns.

### Checks

The provider, the five callers and the installer match in normal and strict
builds, and each has a changed-source control that is rejected by one byte.
Separate definitions and layout and API checks also pass, with wrong-signature
and wrong-declaration controls that fail as they should. The shared-header
check covers all 679 affected sources in the normal build and 675 in the
strict build. Four of them give the same strict warnings with the old and new
headers, and are not counted as strict successes. Every affected source has
exact normal output and a rejected control. No declarations or warning
suppressions were added for those four.

The [tile fixture](RUNTIME_OBSERVATIONS.md#installed-tile-decoder) runs the
installed decoder on one input in the emulator. Matching, whole-ROM equality,
the interface checks and those finite runs are separate evidence, and none of
them covers the full set of inputs or writers.
