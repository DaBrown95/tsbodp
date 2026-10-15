# Whole-ROM inventory, 15 October 2026

This survey follows the published choice-panel milestone: 1,678 matching C
functions, 236,692 C extent bytes and 500 separately counted glue bytes. Inventory
discoveries add zero C credit. The reference identity and all matching requirements
remain unchanged. The 319,640 mapped extent bytes are a fixed historical
comparison, not the game's complete code denominator.

## Scope and evidence

The survey covers all 16,777,216 physical ROM bytes, all 4,194,304 aligned words,
every Thumb halfword, aligned ARM entry signatures, and all ten configured
ROM-to-RAM installations. The generated ROM map contains a disjoint classification
for every physical interval and summaries for all 256 regions of 64 KiB. Every
classification records its basis and confidence. Unresolved regions are retained
even when they resemble assets or contain no recognizable prologue.

The rooted census starts with matching source/glue entries, established startup
entries, validated copy destinations and callback fields supported by matching
consumers or original load/assignment evidence. It follows direct calls, supported
literal transfers and guarded local switches. Pointer/prologue-only candidates
are excluded from its instruction total. The ordinary map keeps estimated CFG
envelopes separately; these include pools and gaps and do not prove compiler
function ownership. Matching source extents have the stronger compiler/linker
boundary evidence, including their literal pools and alignment.

The public reproduction is `make progress`. The current proof and a bounded set
of useful decoder, source/object, failure and comparison evidence are retained
locally under ignored reports. Obsolete generated raw evidence is retired;
historical receipts do not guarantee its continued availability. No instruction
bodies, ROM payload or extracted assets are published as inventory metadata.

## Results

The authoritative current counts and interval evidence are in
[`assets/rom-inventory.json`](../assets/rom-inventory.json), under `code_census`.
They distinguish qualified static instruction bytes, deliberately dual-use bytes,
referenced literal/switch data, known data, unresolved bytes inside owned or
estimated extents, and all remaining unresolved ROM bytes. These are instruction
classification counts, not C coverage. The treemap continues to award green only
through matching source receipts and changed-source negative controls.

| Disjoint physical classification | Bytes |
| --- | ---: |
| Qualified rooted instructions | 270,050 |
| Qualified instructions also read as data | 4 |
| Referenced literal/switch data | 34,540 |
| Other established data | 18,836 |
| Unclassified inside source/glue-owned extents | 2,956 |
| Unclassified remainder of estimated envelopes | 17,016 |
| Other unresolved ROM | 16,433,814 |
| **Physical ROM total** | **16,777,216** |

Thus 270,054 bytes have qualified static instruction evidence, under the stated
decoder, mode, original-image and ordinary-call assumptions. This confirms their
static instruction role; it does not establish that every instruction executes.
The raw alternative reach is 270,080 bytes. There are 2,321 rooted execution
entries, while the ordinary map has 2,528 entries/candidates and 323,786 estimated
extent bytes. Nine corroborated veneer starts were added (six register veneers and three audio
stubs), and four prior weak starts were folded as interior blocks, for a net five
entries and 24 mapped extent bytes.
The verified C function and byte gains from this inventory are both zero.

The subsequent [record-selection reconstruction](RECORD_SELECTION_RECONSTRUCTION.md)
adds six matching C functions and 1,136 C extent bytes, bringing source coverage to
1,684 functions and 237,828 bytes. Twenty previously unclassified bytes move from
estimated envelopes into compiler-owned extents; they remain unclassified in this
census. Static instruction totals, mapped extent totals and denominator limits
are unchanged. This source gain is separate from the inventory's zero C credit.

Milestone 124 adds four matching C functions and 804 C extent bytes, bringing
source coverage to 1,688 functions and 238,632 bytes with the same 500 separately
counted glue bytes. This source gain is separate from inventory discovery and
does not establish a new code denominator. The regenerated census accounts for
physical classification changes separately: six zero alignment bytes move from
estimated gaps into compiler-owned extents, without becoming instruction bytes.
The historical 319,640-byte comparison and the survey's unresolved-region limits
remain unchanged.

Milestone 125 adds two matching C functions and 664 C extent bytes in the
[paired mosaic transitions](TRANSITION_MOSAIC_REFRESH.md), bringing source
coverage to 1,690 functions and 239,296 bytes, with the same 500 separate glue
bytes. Four further zero alignment bytes move from estimated gaps into
compiler-owned extents and remain unclassified as instructions. The 270,054
qualified static instruction bytes, 323,784 mapped extent bytes, open denominator
and fixed historical comparison remain unchanged.

Milestone 126 adds the three connected [attachment job kind 48](FRAME_ATTACHMENT_JOB_48.md)
bodies and 596 matching C extent bytes, bringing source coverage to 1,693
functions and 239,892 bytes. Separate glue remains 500 bytes. Four zero alignment
bytes move from estimated gaps into compiler-owned extents without becoming
instruction bytes. Qualified instruction evidence remains 270,054 bytes and
inventory mapped extents remain 323,784 bytes. The historical comparison and open
denominator remain unchanged.

Milestone 127 adds the three connected [attachment job kind 71](FRAME_ATTACHMENT_JOB_71.md)
bodies and 556 matching C extent bytes, bringing source coverage to 1,696
functions and 240,448 bytes. Separate glue remains 500 bytes. Two observed zero
alignment bytes move from estimated gaps into compiler-owned extents and remain
unclassified as instructions. The 270,054 qualified static instruction bytes,
323,784 inventory mapped extent bytes and fixed 319,640-byte historical comparison
remain unchanged. The complete game-code denominator remains open.

Milestone 128 adds the [row-99 workers and dispatcher](FRAME_ATTACHMENT_JOBS_42_94.md),
three matching C functions and 636 C extent bytes. Source coverage reaches
1,699 functions and 241,084 bytes with the same 500 separate glue bytes. Four
observed zero alignment bytes move from estimated gaps into compiler-owned
extents and remain unclassified as instructions. The 270,054 qualified static
instruction bytes, 323,784 inventory mapped extent bytes, fixed historical
comparison and open denominator remain unchanged. Earlier worker notes now
correctly identify adjustment-table rows applied across eight needs; no C body
or source credit changes from that terminology correction.

Milestone 129 completes the [row-99 selection and allocation path](FRAME_ATTACHMENT_JOBS_42_94.md)
with two matching C functions and 56 extent bytes, reaching 1,701 functions and
241,140 C bytes. Separate glue remains 500 bytes. The begin callback's two zero
tail bytes now have full compiler/linker ownership evidence and extend the
prior estimated envelope by two bytes: inventory mapped extents are 323,786
bytes. Owned unclassified bytes rise by two and other unresolved ROM falls by
two; qualified instruction evidence stays 270,054 bytes. The historical
319,640-byte comparison and open game-code denominator remain unchanged.

Two misleading classifications were investigated explicitly. A presumed return
from the startup call to main leads a Thumb walk into independently established
ARM startup and then scheduler literals. The census preserves that raw alternative
but excludes its descendants only in that startup context; independently rooted
scheduler code remains. The fallback branch remains recorded without assuming
universal absence of nonlocal control flow. Separately, the audio IRQ return word
is read as data by a known patcher. It has both roles and is counted once.

Legacy Binutils 2.10.1 objects lack ARM mapping symbols; the modern linker can
synthesize a whole-function `$d`. That is not evidence that a matching function
is data. The source-object audit therefore left 175 legacy extents, 25,816 bytes,
unclassified by mapping symbols. The independent rooted CFG classifies 22,622 of
those as instructions and 2,896 as referenced data, leaving 298 unresolved.
Across all source-owned gaps in the initial rooted pass, 2,608 bytes were assembler
data/alignment, 298 had no legacy mapping and eight were assembler-tagged Thumb
NOPs not reached by the CFG. All 92 explicitly excluded inline-glue bytes were
recognized as instructions. The census does not turn remaining zeros into padding
without evidence, or trust a linker-generated data label.

## Indirect control flow

The initial map had 301 physical transfer annotations: 100 guarded local switches,
79 resolved veneer calls, 11 literal transfers and 111 open physical sites.
The latter comprised 101 callback/call observations and 17 terminal observations
with seven overlapping sites. All were reviewed against native consumers,
matching sources, assignments and existing failed attempts.

| Producer of the initially open site | Sites | Remaining uncertainty |
| --- | ---: | --- |
| Fixed ROM table | 28 | Observed prefix and field role do not close runtime index domains. |
| Writable object/record field | 35 | Other assignments and object populations remain open. |
| Writable global | 19 | Initialization and replacement writers are not exhausted. |
| Writable field populated from a ROM table | 14 | Assignment edges do not replace all targets of a generic callback slot. |
| Register forwarded from caller | 10 | Incoming register targets remain caller-dependent. |
| Fixed literal | 3 | Static producer can be resolved separately from copied-memory state and argument validity. |
| Writable IRQ handler table | 1 | Defaults are known; setters can replace them. |
| Indexed writable record | 1 | Record population and bounds remain open. |

The assignment survey found 135 accepted-source statements in 84 functions and
128 distinct native literal-writer candidates. These are observed populations,
not an exhaustive write proof. All indexed BX instructions had transfer or return
annotations. Raw BX-looking words outside corroborated CFGs remain unproven.

All 200 consecutive indexed-pointer runs were triaged: 168 lie in corroborated
observed prefixes, 30 were identified immediately as literal-pool sequences, one
crosses the two known transition tables and one initially remained unresolved.
A bounded follow-up resolved that last 32-byte run at ROM `0x4C89C` as eight
PC-relative audio veneer literals, not indexed dispatch data. Seven simple
load/BX stubs and one preserving wrapper with a private helper corroborate all
eight words. Three previously unindexed audio stub starts were added; caller and
runtime reachability remain unproved. No other pointer runs were inferred from
this local result. Eleven additional table prefixes
support 525 unique Thumb destinations, including 310 previously candidate entries.
The public configuration records roots, strides, callback fields, observed counts,
source/native evidence and prefix hashes. It never seeds noncallback fields.
Phase consumers now select their own begin/step/end column rather than a union of
all three. Runtime target completeness remains false for observed tables.

The route table has eight descriptors, with a null callback in mode seven. The
need-effect prefix has 149 observed records; its next object is the threshold
table. The volume-effect prefix has ten corroborated records. A four-bit selector
alone does not establish sixteen valid records. Three resource-transition callbacks
and two audio activity callbacks are assignments into writable slots, not closed
target sets at every downstream consumer.

The adjacent fifteen-register veneer sequence corroborates six previously
unindexed entries. Their BX instructions and following NOP alignment are kept
separate. No caller or runtime execution is inferred for those six slots.

## Copied code and audio kernels

The ten installation lengths sum to 19,360 bytes but cover only 19,188 distinct
ROM source bytes. Five overlaps account for 172 bytes copied more than once,
usually prefixes of following routines. Physical ROM ownership is counted once;
execution addresses remain aliases. Copy length does not establish function size.
The initial EWRAM image has no established executable entry; later executable
writes remain possible.

| Provisional audio name | ARM entry | Reachable instruction bytes |
| --- | --- | ---: |
| mixLeft | `0x03000604` | 128 |
| mixRight | `0x03000684` | 136 |
| mixCenter | `0x030006A4` | 132 |
| mixStereo | `0x03000728` | 152 |
| mixLeftHQ | `0x030007C0` | 228 |
| mixRightHQ | `0x030008A4` | 236 |
| mixCenterHQ | `0x030008C8` | 232 |
| mixStereoHQ | `0x030009B0` | 260 |

Independent original-image walks establish a union of 300 ARM instructions,
1,200 distinct bytes, at ROM `[0xFDAA7C,0xFDAF2C)`. Individual reaches sum to
1,504 bytes because the right paths share 304 bytes with left paths. No literal
pool, intervening alignment, direct call or unresolved PC write was found within
this family. It is a set of shared assembly paths, not eight disjoint compiler
function extents. Null kernel slots and the separate matching ROM fade function
remain explicit.

All 300 normalized instructions and eight entry labels agree semantically with
the retained Krawall `lib/mixer_func.S`, revision
`8d338581bf0ed0afad15b66bf5979ad4c4d15ed0` (LGPL-2.1-or-later). This is textual
instruction correspondence, not an assembled-byte match, proof of unique
historical provenance or recovered C. No upstream kernel source was copied into
the publication.

Known IRQ and shift-patch writers do not intersect the kernel union. The latter
clears bits `0xF80` and ORs the incoming argument shifted by seven without a local
range mask; describing it as changing only a shift field requires an input-range
assumption. Unknown writers and runtime-modified states remain open. The historical
`frame_draw_iwram` key denotes object-table ordering/sort, not display drawing.

## Denominator and limits

No complete game-code denominator or single reconstruction percentage is justified
by this pass. Rooted, mode-qualified instructions provide a reproducible static
lower population under the recorded ARM7/original-image assumptions. Estimated
envelopes are a different unit. The verified C numerator includes pools and
alignment, so dividing it by instruction bytes would mix units.

Closure is prevented by open writable callback populations and serialized index
domains, unclassified extents and ROM banks, naked/missing-prologue code, possible
unidentified copied/decompressed/generated code and self-modified states. Six
outside-main Thumb pointer/prologue coincidences remain unresolved. ARM signature
matches, including eight pointer coincidences, were never promoted solely on that
pattern; established entries retain their independent evidence. Absence of familiar entry patterns does not
prove a ROM bank is data. A useful narrow upper bound cannot exclude those banks
without additional format, reference or execution evidence.

No new runtime execution was collected. The checked analysis environment had no
available ARM emulator; the retained finite engine is Thumb-only. That is a bounded
availability observation, not a machine-wide absence claim. Even observed execution
would not prove all possible targets or writers had been found.

The inventory checkpoint ends with these limits explicit. Connected matching C
work resumes at the phase-7 initializer and copied object ordering path, followed
by the held renderer/finalizer work. Inventory closure is not a prerequisite for
further reconstruction.
