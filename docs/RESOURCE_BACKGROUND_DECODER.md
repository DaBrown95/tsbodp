# Copied resource decoders

[`background_decoder.s`](../src/resource/background_decoder.s) rebuilds all
812 bytes at ROM `0x080002EC..0x08000618`, also linked independently at the copied
execution address `0x03003370..0x0300369C`. These are 203 ARM instructions,
with no literal pool, alignment payload or C credit. The 848-byte installation
also copies the first 36 bytes of the following matching C frame scheduler;
that prefix remains a separate source owner.

## Assembly-origin evidence

The archived [author index](https://web.archive.org/web/20040212223802id_/http://www.devrs.com/gba/asmcode.php)
identifies Jeff Frohwein's PuCrunch v1.0612 as ARM assembly for ARM/Thumb GCC.
The [author's source package](https://web.archive.org/web/20150302021803id_/http://www.devrs.com/gba/files/armpuc.zip)
contains its whole-function ARM source, including the halfword-output variant.
Its distinctive register protocol and algorithm order correspond across the
entire native routine:

| Native portion | Bytes | Correspondence |
| --- | ---: | --- |
| Entry and header/table setup | 72 | Output, escape widths, ranked RLE table and sentinel state |
| Gamma and bit readers | 204 | R0 cursor, R5 value, R8 sentinel and R9 count; shared tails |
| Escape/literal/token decisions | 108 | R11 saved escape, common literal suffix and R10 pending byte |
| Short/long RLE | 128 | Gamma length extension and ranked byte codes below 32 |
| LZ position decoding | 76 | Gamma distance high part, extension bits, low byte and EOF |
| VRAM forward-copy paths | 188 | Pending-byte and distance-one cases, followed by native halfword loops |
| Flush and return | 36 | Pending-byte flush, saved state and native optional size output |

The native private calls return a carry flag directly to conditional branches
or ADC operations, keep packed parameters in R2 across calls, and share the
same persistent outer register state. This is positive whole-routine assembly
lineage evidence. It does not arise from difficulty compiling a C candidate.

The historical source is earlier and does not assemble to the game bytes.
The game version uses a compact header, word input, unrolled gamma prefix,
halfword bulk copies and an optional decoded-size output. Its exact historical
revision remains unidentified. No explicit reuse grant was found for the ARM
translation; that source is retained privately as evidence only. The published
assembly was independently reconstructed from the fixed native instructions
and dataflow, with descriptive labels and constants; upstream source text is
not copied. Pucrunch's original algorithm is by Pasi Ojala. His later licence
statement does not establish terms for a separate ARM translation.

## Verification and contract

The complete positive image equals the reference at both ROM and RAM linkage
addresses. Five separate source controls alter the gamma limit, RLE threshold,
EOF code, copy step or decoded-size store; each assembles and rejects by one
byte. Instructions are written as assembly operations, with no embedded ROM
instruction data, patches or masked comparisons.

Entry arguments are compressed input in R0, output in R1 and a nullable decoded
byte-count pointer in R2. The native return restores the original destination
into R0; existing callers use a void contract. The accepted display caller
passes a null R2, supported by its guarded epilogue and the bounded boot entry.
The tile decoder's count pointer is unconditional and remains distinct.

The existing original-instruction models exercise selected compressed inputs,
and the bounded HLE boot observes one entry. Source ownership, these finite
observations and whole-ROM equality do not close all input bounds, malformed
streams, writable entry assignments, copied-memory modifications or gameplay.
The separate [tile decoder](#matching-tile-decoder) now has matching C source.


## Startup callback writer

For the unresolved background call at ROM `0x0800E1B8`, the callback word at
`0x030036C0` has an additional established startup writer. The matching memory
initializer requests a fixed-zero DMA3 fill of `0x030015B0..0x03007D00`, which
includes that word. This establishes its pre-install zero state under the
platform DMA contract. The matching decoder installer then copies 848 bytes to
`0x03003370`, ending immediately before the callback word, and explicitly stores
the even ARM entry `0x03003370` into it. The target's 812-byte source ownership
does not itself exhaust callback writers.

The matching game entry orders memory initialization before decoder installation.
The current qualified direct-call graph for its eleven initialization roots
before installation covers 74 entries, has no missing entry or unresolved
transfer, and does not reach `display_decode_background`. This supports the
absence of a synchronous call to this site in that normal startup prefix under
the existing decoder, ordinary-call and BIOS assumptions. IRQ entry, nonordinary
re-entry, later aliases and writers remain open. Pre-install zero is a storage
state, not an additional executable target; the transfer remains unresolved.


## Matching tile decoder

The [tile-run decoder](../src/resource/resource_decode_tile_runs.c) rebuilds all
504 bytes at ROM `0x0800B36C..0x0800B564`, independently linked for execution at
`0x030036D0..0x030038C8`. These are 126 ARM instructions, with no literal pool
or alignment tail. The 528-byte installation also copies the first 24 bytes
of the separately matching [map drawer](FRAME_MAP_STAGING.md); it is not a
528-byte C owner.
ROM and copied-RAM bytes are counted once.

The stream has literal, repeated-byte and backward-copy runs, ending at a zero
command. A pending byte combines with the next output byte before a halfword
store; the final odd byte is flushed separately. The source preserves the
native aligned halfword loops and overlapping backward-copy order. Valid
stream, backing, alignment and destination-capacity premises remain required;
no bounds guard or malformed-stream policy is added.

One ordinary scratch variable holds the count field, then distance, then the
odd-byte tail in their actual phases. A short R2 low-field value has one real
producer and feeds the distance OR; the R1 length feeds the copy and repeat
paths. This preserves the native compare, shift and OR order and the later
register phases. The leaf's R14 byte/pair scratch values end before the saved
return address is restored. Its R0 output cursor is the actual returned value.
There are no inserted instructions, clobbers, extra observations or artificial
consumers. The source experiments and full failed comparisons remain local.

The canonical tile callback now returns `void *`, the advanced output cursor,
and still writes the decoded byte count through its required third argument.
Both shared declarations, the provider prototype and the copy caller's local
callback type agree. All five located callers discard that return. This is
compatible with the observed native postcondition; the historical C prototype
is not uniquely recovered from an ignored return. The separate background
callback remains `void`, with its nullable count pointer; the two-argument
resource dispatchers keep their unsigned count returns.

The new provider, five callers and installer pass normal and strict matching
checks. Their genuine changed-source controls each reject by one byte. Actual
separate definitions and layout/API checks also pass, with meaningful wrong
signature and declaration controls. Full-ROM equality and source controls,
these static interface checks and the earlier finite decoder models and boot
observations remain separate evidence. This milestone adds no runtime execution
or complete writer/input population claim.

The broader shared-header check covers all 679 affected owners normally and
675 strictly. Four owners reproduce their existing strict warnings under both
old and new headers; none is counted as a strict success. Every affected owner
has exact normal output and a rejecting source control. No declaration or
warning suppression was added for those unrelated cases.
