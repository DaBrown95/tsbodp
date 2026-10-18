# Whole-ROM inventory

The initial 15 October survey followed the choice-panel milestone: 1,678 matching
C functions, 236,692 C extent bytes and 500 separately counted glue bytes. The
results table includes subsequent matching milestones described below. Inventory
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

The table below is a historical survey snapshot. Current source ownership is
recorded in the generated [progress data](../assets/progress.json) and the
[remaining-work list](COMPLETION_BLOCKERS.md). The separately counted 4,060
assembly extent bytes include the 1,604-byte mixer family,
140-byte timer IRQ, 140-byte startup exceptions, eight-byte BIOS wait wrapper,
60-byte compiler register-call family, 672-byte division/remainder family and
812-byte background decoder and 72-byte audio interworking entries/pools and 60-byte debugger adapter, with
their genuine data and alignment; it is not a C gain. Exact source and full-ROM/control gates verify these replacements.
See [audio](AUDIO_RECONSTRUCTION.md),
[startup](STARTUP_RECONSTRUCTION.md), [compiler assembly](RUNTIME_REGISTER_CALLS.md) and the concise
[remaining-work list](COMPLETION_BLOCKERS.md).

The generated inventory records the current qualified static instruction union.
Source extents include their literal pools and alignment; instruction-byte
counts describe separately qualified code. Compiler matches do not establish
runtime execution. The separate
[bounded boot experiment](RUNTIME_OBSERVATIONS.md) records selected entry and
write observations without closing target domains. The static census's
estimated envelope bytes, the treemap's mapped extent bytes and fixed 319,640
historical comparison remain distinct, with no complete game-code denominator
established.

The authoritative current counts and interval evidence are in
[`assets/rom-inventory.json`](../assets/rom-inventory.json), under `code_census`.
They distinguish qualified static instruction bytes, deliberately dual-use bytes,
referenced literal/switch data, known data, unresolved bytes inside owned or
estimated extents, and all remaining unresolved ROM bytes. These are instruction
classification counts, not C coverage. The treemap continues to award green only
through matching source receipts and changed-source negative controls.

| Disjoint physical classification | Bytes |
| --- | ---: |
| Qualified rooted instructions | 270,604 |
| Qualified instructions also read as data | 4 |
| Referenced literal/switch data | 34,728 |
| Other established data | 18,836 |
| Unclassified inside source/glue-owned extents | 3,068 |
| Unclassified remainder of estimated envelopes | 16,182 |
| Other unresolved ROM | 16,433,794 |
| **Physical ROM total** | **16,777,216** |

Thus 270,608 bytes have qualified static instruction evidence, under the stated
decoder, mode, original-image and ordinary-call assumptions. This confirms their
static instruction role; it does not establish that every instruction executes.
The raw alternative reach is 270,634 bytes. There are 2,324 rooted execution
entries, while the ordinary map has 2,523 entries/candidates and 324,014 mapped
extent bytes. In the initial survey, nine corroborated veneer starts were added (six register veneers and three audio
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

Milestone 130 adds the two connected [link status polling](LINK_STATUS_POLLING.md)
functions and 320 matching C extent bytes, reaching 1,703 functions and 241,460
C bytes. Separate glue remains 500 bytes. Six observed zero bytes move from
estimated gaps into compiler-owned extents; they add no instruction evidence.
Qualified static instructions remain 270,054 bytes, inventory mapped extents
remain 323,786 bytes and the complete game-code denominator stays open. The
original status reader and installed IRQ handler remain explicit boundaries;
the fixed 319,640-byte historical comparison is unchanged.

Milestone 131 adds the connected [serial handshake IRQ and timeout](SERIAL_HANDSHAKE.md)
with two matching C functions and 652 extent bytes, reaching 1,705 functions and
242,112 C bytes. Separate instruction glue remains 500 bytes. Two new compiled
entry roots promote the existing original start-provider entry through a direct
call; all three were previously weak candidates. Their combined 554 instruction
and 188 referenced-data bytes become qualified static evidence, without new
C credit for the original provider. The instruction union reaches 270,608 bytes
and the referenced-data union 34,732 bytes; both include the unchanged four-byte
dual-use word. Eight zero bytes acquire compiler extent ownership, including
the timeout's two newly bounded trailing bytes. Inventory mapped extents become
323,788 bytes, with 2,970 owned unclassified bytes, 16,262 estimated unclassified
bytes and 16,433,812 other unresolved bytes. No new runtime evidence or complete
code denominator is claimed; the historical 319,640-byte comparison stays fixed.

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

The custom background decoder now has 812 separately counted assembly-origin
source bytes, verified at ROM `0x2EC` and RAM `0x03003370`. Its whole-function
Pucrunch ARM lineage is documented in [the origin review](RESOURCE_BACKGROUND_DECODER.md);
the native version is independently reconstructed and is not identified as the
exact earlier release. The 848-byte installation consists of that body and
36 bytes of the following C frame scheduler. Source ownership of this copy
does not close writable entry assignments or later code modifications.

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

The later [event payload copy repair](EVENT_HANDOFF.md) refreshes the complete
matching build, inventory and treemap without changing any static classification
or coverage count. Its existing 244-byte recorder gains no additional C credit.
The total remains 1,705 matching C functions and 242,112 C extent bytes; the fixed
319,640-byte historical comparison and unresolved game-code denominator remain
unchanged.

### Linked entry setup and final-row observation counts

The linked-scene object builder at `0x08003F08` adds one matching C function and
344 extent bytes: totals are now 1,706 functions and 242,456 C bytes, with 500
instruction-glue bytes separate. Its full comparison includes 292 instruction
bytes, 48 referenced pool bytes and four zero alignment bytes. The former
326-byte estimate stopped at the return; the full extent ends at `0x08004060`.
It absorbs the weak eight-byte pointer candidate at `0x0800404E`, leaving 2,527
inventory entries and 323,798 mapped extent bytes. The treemap's inherited
accounting reports 323,806 mapped extent bytes. Neither is a complete code
denominator; the fixed historical comparison remains 319,640 bytes.

Publication checks exposed stale per-row counts after known extents and split
remnants replaced scanner estimates. Counts are now recomputed from retained
observations within each final row, before raw offset sets are discarded. Seven
row summaries change; every final instruction and literal count is bounded by
its row size. Four regression tests cover trailing pools, observations outside
ownership, dual roles and split remnants. The global unions remain 270,608
qualified instruction bytes and 34,732 referenced data bytes. No additional
execution, recovered C or complete-boundary claim is inferred from this counter
repair. Callback domains, copied-code and unresolved-region limits above remain
open. At that checkpoint the adjacent builder and begin/step callbacks remained
unconverted.

### Linked entry begin callback

The begin callback at `0x08003750` adds one matching C function and 876 extent
bytes: totals are 1,707 functions and 243,332 C bytes, with 500 instruction-glue
bytes separate. It contains 738 instruction bytes, 132 referenced pool bytes,
four internal zero alignment bytes and two trailing zero alignment bytes. The
sole function symbol spans 874 bytes; the accepted full extent includes the
final alignment before the step entry at `0x08003ABC`.

Only this inventory row changes. Its previous 874-byte control-flow envelope
becomes the bounded 876-byte matching extent; there are still 2,527 entries.
Inventory mapped extents are now 323,800 bytes; the treemap's inherited accounting
reports 323,808 bytes. Qualified instruction and referenced-data unions remain
270,608 and 34,732 bytes. Disjoint classification reports 270,604 instruction
bytes, 34,728 referenced-data bytes, four dual-use bytes, 18,836 known-data bytes,
2,980 unclassified owned bytes, 16,254 unclassified estimated-envelope bytes and
16,433,810 unresolved bytes. These classifications do not establish a complete
game-code denominator. The fixed historical comparison remains 319,640 bytes.

Shared field and character-interface repairs preserve all existing matching
function bytes and add no separate C credit. The refresh helper, adjacent
builder, step callback and renderer/finalizer remain unconverted. No new runtime
execution or completeness claim is inferred from this update; the inventory
limits above remain open.

### Linked offer refresh and its connected caller

The linked offer-refresh helper at `0x08004824` adds one matching C function and
288 extent bytes: totals are 1,708 functions and 243,620 C bytes, with 500 glue
bytes separate. The 234 instruction bytes, 52 referenced pool bytes and two zero
alignment bytes all match. Its begin caller uses the accepted provider's name at
the same address and retains identical positive and changed-source-control bytes.

The earlier 94-byte row stopped at the weak `0x08004882` candidate. Existing
instruction reach and literal references already supported the full span through
`0x08004944`; the compiler/linker comparison now establishes its matching extent.
The weak start is absorbed as alignment/pool context. This leaves 2,526 entries,
323,980 inventory extent bytes and 323,988 treemap extent bytes. Those extra 180
mapped bytes are a boundary repair, not additional C credit beyond the accepted
288-byte function.

The global qualified unions remain 270,608 instruction bytes and 34,732 referenced
data bytes. Two zero bytes move from estimated gaps to unclassified owned bytes;
the current disjoint counts appear in the Results table. The fixed historical
comparison stays 319,640 bytes. Catalog alignment and representation checks do
not establish its complete table capacity, historical types, runtime execution or
a complete game-code denominator. The other refresh helper, adjacent builder,
step callback and renderer/finalizer remain explicit original regions.


### Quantity display and its connected caller

The quantity-display helper at `0x08004944` adds one matching C function and 376
extent bytes: totals are 1,709 functions and 243,996 C bytes, with 500 glue bytes
separate. Its 342 instruction bytes, two alignment zeros and 32 referenced pool
bytes match through `0x08004ABC`. The begin caller replaces the original-service
name at the same address, with identical positive and changed-source-control
bytes. No inventory discovery receives C credit.

Only this ordinary inventory row changes; its existing 376-byte estimate gains
the matching source/compiler ownership evidence. There remain 2,526 entries,
323,980 inventory extent bytes and 323,988 treemap extent bytes. Qualified static
unions stay 270,608 instruction bytes and 34,732 referenced-data bytes. Two zero
bytes move from estimated gaps to unclassified owned bytes; the Results table
records that classification separately. The historical comparison remains
319,640 bytes, with no complete game-code denominator or new execution claim.

At that milestone the linked-player quantity helper, other offer refresh, object
builder, step callback and renderer/finalizer remained unconverted. The callback domains,
eight copied-audio-kernel extent uncertainties and other survey limits above
remain open. The field, API and source-control checks do not close those gaps or
establish complete table capacities and historical types.

### Linked participant quantity display

The connected helper at `0x08004ABC` adds one matching C function and 556 extent
bytes: totals are 1,710 functions and 244,552 C bytes, with 500 glue bytes counted
separately. The complete span includes 502 instruction bytes, 52 referenced
literal bytes and two zero alignment bytes, ending at `0x08004CE8`. Its begin
caller replaces only the provider name at the same address and retains identical
positive and changed-source-control bytes. Inventory discoveries add no C credit.

Only this ordinary inventory row changes. Its existing estimate gains compiler
ownership evidence; there remain 2,526 entries, 323,980 inventory extent bytes
and 323,988 treemap extent bytes. Qualified static unions remain 270,608
instruction bytes and 34,732 referenced-data bytes. Two zero bytes move from
estimated gaps into unclassified owned bytes, as recorded in the Results table.
There are 762 bounded estimated bodies, 100 switch tables, 22 unresolved dispatch
sites and 98 unresolved callback call sites. Observed reach does not close every
possible target.

The other offer refresh, object builder, step callback and renderer/finalizer
remain unconverted. The eight copied-audio-kernel extent uncertainties and the
other survey limits remain open. No new runtime observation or complete code
denominator is claimed; the fixed historical comparison remains 319,640 bytes.

### Connected entry panel

The helper at `0x08004060` adds one matching C function and 356 extent bytes,
bringing coverage to 1,711 functions and 244,908 C bytes, with 500 glue bytes
separate. The complete span ends at the separately called entry `0x080041C4` and
contains 238 instruction bytes, 108 referenced data bytes and ten alignment zeros.
The referenced data includes the existing twelve-case switch table. The begin
caller's canonical provider name retains identical positive and source-control
bytes. Inventory discoveries themselves add no C credit.

The verified envelope replaces four old map rows: the root and weak starts at
`0x0800408A`, `0x080040E2` and `0x080041C2`. It also covers an eighteen-byte gap
between prior estimates. The ordinary map therefore has 2,523 entries and 323,998
mapped extent bytes; the treemap has 324,006 extent bytes. Its inherited eight-byte
difference remains separate. Ten already observed alignment zeros move from
estimated gaps into owned unclassified bytes. Qualified static instruction and
referenced-data unions remain 270,608 and 34,732 bytes. This is stronger function
ownership evidence, not newly observed execution.

The eight copied-audio-kernel extent uncertainties, unresolved indirect targets,
other estimated boundaries and remaining survey limits still prevent a complete
game-code denominator. The historical comparison stays fixed at 319,640 bytes.

### Linked entry header value

The helper at `0x08005684` adds one matching C function and 160 extent bytes,
bringing coverage to 1,712 functions and 245,068 C bytes, with 500 glue bytes
separate. Its existing 160-byte estimate gains compiler ownership evidence for
138 instruction bytes, twenty literal bytes and two internal alignment zeros.
The referenced pool ends at the separately called countdown entry `0x08005724`.
The canonical begin caller and unchanged panel header consumer retain their
positive and changed-source-control bytes.

Only this ordinary map row changes. Entry count remains 2,523, inventory extent
bytes remain 323,998 and treemap extent bytes remain 324,006. Two observed zeros
move from estimated gaps into owned unclassified bytes. Qualified instruction and
referenced-data unions remain 270,608 and 34,732 bytes. The original rasterizer
and row reader were replayed for the font-control write-footprint witness; this
adds neither C coverage nor runtime observations. The copied-audio extent gaps,
unresolved targets and complete-denominator limitations remain open. The fixed
historical comparison is still 319,640 bytes.

### Actor need-target selector

The connected actor-state selector at `0x08006F20` adds one matching C
function and 272 extent bytes, bringing coverage to 1,713 functions and 245,340
C bytes, with 500 glue bytes separate. Its earlier 270-byte control-flow
estimate now has compiler ownership through the two trailing alignment zeros
before the independently called state-34 entry at `0x08007030`. The full span
contains 256 instruction bytes, twelve literal bytes and four alignment zeros.

Only this ordinary map row changes. Entry count stays 2,523; inventory extent
bytes become 324,000 and treemap extent bytes 324,008. Two internal zeros move
from estimated gaps into source-owned unclassified bytes, and two trailing zeros
move from unresolved ROM into that owned category. Qualified instruction and
referenced-data unions remain 270,608 and 34,732 bytes. The two callback sites
retain open writable-population evidence; finite table assignments and the
seven-byte writer contract are detailed in
[FRAME_NEED_TARGET_SELECTION.md](FRAME_NEED_TARGET_SELECTION.md).

No inventory discovery, existing provider or callback gains C credit here.
The copied-audio-kernel extent uncertainties, unresolved targets and other survey
limits still prevent a complete code denominator. The historical comparison
remains fixed at 319,640 mapped extent bytes.

### Connected need-action writers

Two callbacks at `0x080432CC` and `0x08016F24` add two matching C functions
and 236 extent bytes, bringing coverage to 1,715 functions and 245,576 C bytes;
500 glue bytes remain separate. The complete spans contain 230 instruction
bytes, four literal bytes and two internal alignment zeros. Existing callers,
providers and inventory findings add no C credit.

These two existing map rows gain compiler ownership. Entry count remains 2,523,
inventory extent bytes remain 324,000 and treemap extent bytes remain 324,008.
Two internal zeros move from estimated gaps into source-owned unclassified bytes;
qualified instruction and referenced-data unions remain 270,608 and 34,732.
The observed callback prefix and provisional owner/type limits are detailed in
[FRAME_NEED_TARGET_SELECTION.md](FRAME_NEED_TARGET_SELECTION.md).

At that milestone, the row-97 writer remained unconverted: its closest
124-byte candidate differed in four bytes, and its proposed trailing alignment
gained no ownership there.
Copied-audio extent gaps, unresolved transfers and other survey limits still
prevent a complete code denominator. The historical comparison remains fixed
at 319,640 mapped extent bytes. No new runtime observations are claimed.


### Zero-index action writers

The row-97 writer at `0x08017AC4` and row-87 writer at `0x080220C0` add two
matching C functions and 224 extent bytes, bringing coverage to 1,717 functions
and 245,800 C bytes. The same 500 glue bytes remain separate. The complete
spans contain 186 instruction bytes, 32 referenced data bytes and six alignment
zeros. The data includes the bounded six-case switch table and its pointer.
Existing callers, providers and inventory findings add no C credit.

The former row-97 hold now matches all 124 bytes. These two ordinary map rows
gain compiler ownership through two trailing zero bytes each; entry count stays
2,523, inventory extent bytes become 324,004 and treemap extent bytes 324,012.
Four trailing zeros move from unresolved ROM into source-owned unclassified
bytes; two internal zeros move there from estimated gaps. The source-owned
unclassified total therefore becomes 3,010, estimated-envelope remainder
16,230 and other unresolved ROM 16,433,804. Qualified instruction and
referenced-data unions remain 270,608 and 34,732 bytes.

The source preserves eight address operations in ordinary target-specific C.
Their local indices are proven zero and unescaped; pointer/integer width and
conversion requirements are explicit, without inferring historical spelling,
nonzero-index behavior or address packing. The high-level condition/switch and
provider logic remains present. No instruction body or output patch is added.
The existing alignment directive requests only alignment. The exact source,
callback/field/API domains, meaningful controls and static route limits are
detailed in [FRAME_NEED_TARGET_SELECTION.md](FRAME_NEED_TARGET_SELECTION.md).

Row 97 remains disabled in both guarded selectors. The choice-builder route
is conditional; row 87 is enabled, but all codes emitted by these writers have
action halfword eight and cannot match the need selector's zero-through-seven
ordinal. These findings establish neither gameplay use nor all callback
assignments. Copied-audio extent gaps, unresolved transfers and the other
survey limits still prevent a complete game-code denominator. The historical
comparison remains fixed at 319,640 mapped extent bytes; no runtime observation
is added.


### Row-87 attachment lifecycle

The connected worker at `0x08021E98`, begin callback at `0x0802212C` and
dispatch callback at `0x08022148` add three matching C functions and 572 extent
bytes. Coverage reaches 1,720 functions and 246,372 C bytes, with the same 500
separate glue bytes. The complete spans contain 536 instruction bytes, 28
referenced literal bytes and eight alignment zeros. Existing providers, callers
and inventory discoveries add no C credit. The other row-87 callbacks remain
explicit original regions.

These three existing map rows gain compiler ownership. The worker's former
506-byte estimate extends through two trailing zero bytes to the independently
rooted next entry; the begin callback's 26-byte estimate similarly extends to
28. Dispatch's existing 36-byte extent is unchanged. Entry count remains 2,523,
inventory mapped extents become 324,008 and treemap extents 324,016. Four
internal zeros move from estimated envelopes into source-owned unclassified
bytes, and four trailing zeros move there from other unresolved ROM. Those
categories become 3,018, 16,226 and 16,433,800 bytes respectively. Qualified
static instruction and referenced-data unions remain 270,608 and 34,732 bytes.

The [connected source evidence](FRAME_NEED_TARGET_SELECTION.md#row-87-attachment-lifecycle)
records exact action-kind dispatch, indicator and parameter phases, the
per-access optional-mode requirement, bounded canonical representation copies,
provisional shared-world and legacy owner relationships, and meaningful source
controls. The existing thirteen worker providers are reused without new credit.
Finite callback assignments and a matching build do not establish runtime use
or exhaust indirect targets. Copied-audio-kernel extent gaps and other survey
limits still prevent a complete code denominator. The historical comparison
remains fixed at 319,640 mapped extent bytes; no runtime observation is added.


### Fixed-parameter kind-72 lifecycle

The connected worker at `0x08029A38`, begin callback at `0x08029C1C` and
dispatch callback at `0x08029C64` add three matching C functions and 528 extent
bytes, bringing coverage to 1,723 functions and 246,900 C bytes. Separate glue
remains 500 bytes. The complete spans contain 504 instruction bytes, twenty
referenced literal bytes and four internal alignment zeros. The sixty-byte
intervening original region and all existing providers gain no C credit.

These three existing map rows gain compiler ownership without extent growth.
Entry count remains 2,523, inventory mapped extents remain 324,008 and treemap
extents remain 324,016. Four internal zeros move from estimated envelopes into
source-owned unclassified bytes, making those categories 3,022 and 16,222 bytes.
Other unresolved ROM stays 16,433,800 bytes. Qualified static instruction and
referenced-data unions remain 270,608 and 34,732 bytes.

The [connected source evidence](FRAME_NEED_TARGET_SELECTION.md#fixed-parameter-kind-72-lifecycle)
records fixed parameter index five, the shared bounded world, route/status and
record contracts, exact phase distinctions and source controls. Observed rows
16 and 17 remain disabled in the guarded selectors; conditional callback routes
do not establish gameplay use or exhaust writable populations. Copied-audio
extent gaps and other unresolved survey limits still prevent a complete game-code
denominator. The historical comparison remains fixed at 319,640 mapped extent
bytes; no runtime observation or inventory C credit is added.


### Row-3 attachment dispatch and steps

The three workers at `0x080358B0`, `0x0803594C` and `0x08035A04`, together
with the dispatcher at `0x08035CE8`, add four matching C functions and 932
extent bytes. Coverage reaches 1,727 functions and 247,832 C bytes; the same
500 glue bytes remain separate. The complete spans contain 780 instruction
bytes, 144 referenced literal/switch bytes and eight internal alignment zeros.
Existing providers, action writers, callers and intervening original callbacks
gain no C credit.

All four existing map rows gain compiler ownership without extent growth.
Entry count remains 2,523, inventory mapped extents remain 324,008 and treemap
extents remain 324,016. Eight internal zeros move from estimated envelopes
into source-owned unclassified bytes, making those categories 3,030 and 16,214.
Other unresolved ROM remains 16,433,800 bytes. Qualified static instruction and
referenced-data unions remain 270,608 and 34,732 bytes. Regenerated assets remain
the authoritative current census.

The [connected source evidence](FRAME_NEED_TARGET_SELECTION.md#row-3-attachment-jobs-12-31-33-and-45)
records the enabled row-3 route, exact running-byte and phase distinctions,
the two bounded sample representations, real unsigned-halfword countdown,
provider lifetimes and meaningful controls. The inherited allocator/state
compatibility limits remain explicit. Larger row-97 workers and the renderer
remain unconverted. Copied-audio extent gaps and other unresolved survey limits
still prevent a complete game-code denominator. The historical comparison
remains fixed at 319,640 mapped extent bytes; no runtime observation or
inventory-discovery C credit is added.


### Row-3 allocation and canonical secondary-list access

The begin callback at `0x08035CA0` adds one matching C function and 72 extent
bytes, bringing source coverage to 1,728 functions and 247,904 C bytes. The same
500 glue bytes remain separate. All 72 new bytes are instructions, with no pool
or alignment bytes. Existing row-3 dispatch/step bodies and providers gain no
additional credit; the intermediate eight-byte callback remains original.

The existing map row gains compiler ownership without changing its 72-byte
extent. Entry count stays 2,523, inventory extents stay 324,008 and treemap
extents stay 324,016. Qualified static instruction and referenced-data unions
remain 270,608 and 34,732 bytes. No unclassified bytes move: source-owned,
estimated-envelope and other unresolved categories remain 3,030, 16,214 and
16,433,800. The bounded estimated-body count becomes 744 because this existing
body now has matching-source ownership.

A separate canonical-field/source-quality repair names the producer-backed
secondary-list pointer at world `+0xF0` and removes reset's fixed-register
constraint without changing its 116-byte match or source coverage. Target
checks show that old and refined record/union sizes and alignments are already
the same; no ABI-size change is claimed. The [row-3 allocation contract](FRAME_NEED_TARGET_SELECTION.md#row-3-allocation-and-route-handoff)
and [secondary-list evidence](ACTOR_ENTRIES_RECONSTRUCTION.md#producer-backed-secondary-list-member)
retain provider, lifetime, layout and legacy-owner limitations. All affected
importers require matching-source controls; neither the type refinement nor
inventory findings add C credit. The historical comparison remains 319,640 mapped
extent bytes, and the complete game-code denominator remains open. No runtime
observation is added.


### Parameter and activity attachment paths

Seven bodies in the [parameter/activity attachment paths](FRAME_NEED_TARGET_SELECTION.md#parameter-jobs-64-and-65-and-activity-jobs-88-and-89)
add 2,160 matching C extent bytes, bringing source coverage to 1,735 functions
and 250,064 C bytes. The same 500 separately counted glue bytes give 250,564
source/glue-owned bytes. Raw C section extents total 250,156, including the
already accounted 92 inline glue bytes; those do not add C credit.

Kinds 64 and 65 now have the primary worker and begin/dispatcher pair in C.
The dispatcher retains an explicit original call for kind 66. The kind-88/89
pair has both substantial workers and its begin/dispatcher in C. The original
choice writer, intermediate callbacks and neighboring predicates are not
silently counted. The renderer and other held candidates remain original.

The two activity workers had CFG extent estimates of 518 and 514 bytes. Their
complete linked slots are 520 and 516, including the two observed zero tail
bytes in each. Actual function symbols remain 518 and 514; boundary confidence,
section extent and symbol size are not interchangeable. Each span has 372
instruction bytes, 136 or 132 referenced literal/switch bytes, and twelve zero
alignment bytes. The ordinary source switch creates the table; the source does
not contain an original instruction or table payload.

The generated inventory and treemap retain their separate rooted instruction,
referenced-data and unclassified accounting after these rows gain compiler
ownership. Inventory discovery, the include guard and reused provider/type
facts add zero C credit. The fixed historical comparison remains 319,640 mapped
extent bytes. The complete game-code denominator remains open, and no gameplay
or runtime observation is added. The current generated assets, rather than a
function-count percentage or inferred ABI, provide the physical census totals.

## Outside-main Thumb coincidences

All twelve selected endpoints of six weak pointer/prologue coincidences now
have positive data roles. The source-backed routes below preserve both endpoints
independently. No classifier changes or C credit follow from these findings.

| Apparent pointer source | Selected data role | Apparent Thumb target | Selected data role |
| --- | --- | --- | --- |
| `0x46B664` | Kind-29 need-effect sprite, variant 3, frame 1: compressed pixels `0x46B3F8..0x46B6A0`. | `0xD05342` | Sample-table index 395: offset 8,092 in the declared 13,111-byte sample `0xD033A6..0xD066DD`. |
| `0xFD6368` | Scene-map codec-3 input `0xFD5A5C..0xFD7320`. | `0x15EB5C` | Completion-screen row 6's next background: codec-3 input `0x15CC80..0x161154`. |
| `0x888668` | Group-zero/clothes-zero animation 13, variant 3, frame 10: compressed pixels `0x88863C..0x888688`. | `0x428660` | Actor 30, animation 1, variant 4, frame 6: compressed pixels `0x428620..0x4288C8`. |
| `0xA7B4DC` | Text bank 4, string 3239: compressed bytes `0xA7B4D2..0xA7B4E4`. | `0x67E758` | Actor 41, animation 46, variant 3, frame 18: packed sprite part `0x67E758..0x67E75C`. |
| `0x176614` | Activity-five background: codec-3 input `0x175120..0x1770DC`. | `0x9ADDC4` | Text bank 0, string 4095: compressed bytes `0x9ADDA8..0x9ADDC9`. |
| `0xA3705C` | Text bank 3, string 254: compressed bytes `0xA37057..0xA37063`. | `0xF61400` | Menu code-nine secondary result, row 14, variant 4: codec-3 input `0xF6086C..0xF61560`. |

The unchanged original-instruction decoder models consume every selected
compressed-background or pixel word and reject truncation before it. The
`0x46B664` sprite produces 1,376 output bytes; its 48-by-88 geometry does not
imply a dense rectangular pixel payload. Small transcriptions of the matching
text-loader C consume each selected text word and reject truncation; those are
source-semantic models, not original-instruction traces. Matching sprite-part
and mixer consumers establish the packed-part and sample data roles. The sample's
declared end plus 69 silence bytes and two alignment bytes reaches the next header.

These are typed static routes and finite model observations, without gameplay
selection. Observed table prefixes are not capacities. Positive data roles do
not exclude executable dual use, identify every incoming transfer or close a
ROM bank. The six weak coincidences therefore remain unresolved in the static
inventory. Source/hash checks, truncation controls and bounded receipts remain
under ignored `analysis/outside-thumb-*/` and `analysis/source-word-46b664/`.


### Standalone reflected-byte checksum

The separate entry at `0x08013390` now owns 68 matching C instruction bytes as
[`crc8_reflected`](../src/runtime/crc8_reflected.c). It starts checksum zero and
updates each byte through eight reflected polynomial-`0x8C` steps. A first
fetch-postincrement recipe was 68 bytes / 60 differences. Moving pointer
advancement to the outer iteration clause gives exact identity: GCSE PRE forms
independent next-pointer and next-count values before the bit loop and restores
the argument homes at its backedge. The retained pass output corrects the
initial prediction that this would first occur in the later loop pass.

Changing the real polynomial to `0x8D` rejects one byte at the same size. Strict
ARM API checks and a wrong-length-type rejection pass; defined host C witnesses
distinguish the actual control and include zero length. These are not game
observations. Valid byte-array/pointer-advance domains are required. No direct
caller or odd ROM pointer has been identified; name, unused formals and the
chosen compatible API remain provisional. Source ownership adds no complete
incoming domain. The full matching/control and progress gates pass.


### Computed collision callback index

The copied collision dispatcher at ROM `0xB0E8` loads callbacks through
`object + 0xC8 + 4*index` at calls `0xB2B0` and `0xB2D8`. The byte loop indices
are tested against object byte `+0xAF`, with no local two-entry bound. Index
nine selects offset `0xEC` if the count reaches ten. Accepted animation and
part-collider updaters obtain that count from serialized sequence byte `+0x0B`
and selected-part updates; their full input/header domain remains open. The
existing `+C8/+CC` shorthand does not establish an exhaustive local slot range.

The actual scratch-array producer collects scene-object pointers, while
need-effect states use a separate allocation pool. This identifies a computed
field-load caveat, not a generic need-effect EC consumer or action-delivery
route. Count/header and base-alias closure remain required. All selected
consumers, count producers and callers already have source. No new compiler or
runtime observation, source credit or complete target set follows.


## Installed serial IRQ target

The accepted handshake installs Thumb target `0x0803DC49` in writable IRQ slot
zero at `0x0803DB30` and `0x0803DBB2`. Its original literals at `0x0803DB78`
and `0x0803DBF8` agree. The owned ARM dispatcher calls that slot for mask `0xC0`.
The existing bounded-entry map now records the handler after checking these
installation sites. The literal remains within its owned handshake extent;
it is not a separate data region or a ROM dispatch-table capacity. Installation
and partition pins are review evidence, not extra schema validations.
This promotes the previously weak `0x0803DC48` entry to a statically grounded
callable target; it supplies no runtime observation or recovered-C credit.

Within `0x0803DC48..0x0803E298`, the bounded native CFG partitions all 1,616 bytes:
1,242 instruction bytes, 356 referenced literal bytes and 18 zero-alignment bytes.
There are no overlapping roles or interior entry roots in the current census;
the final referenced words end at the independent next prologue. The retained
C frontier still mismatches. Its transport-record ownership and initialization,
other IRQ-table writers, enable conditions and complete incoming/writable target
domains remain open. This discovery does not establish inventory completeness.


### Scene-table row 24 source ownership

Seven connected [row-24 bodies](SCENE_RECONSTRUCTION.md#scene-table-row-24-selection-path)
add 1,244 matching C extent bytes, joining the existing selection step and
direction helper. The nine observed bodies total 1,544 bytes and include all
three table callbacks. Existing mapped entries supply the seven boundaries;
no manual entry or new runtime observation is added. Source controls and the
full matching/progress gate cover the complete extents, pools and alignment.

This closes these source bodies, while input and scene/index populations,
resource/text backing and later writers remain open. Current inventory and
mapped counts come from the fresh generated assets; the fixed 319,640-byte
historical comparison remains a separate baseline, without a complete code
denominator.

### Source-owned alignment and data roles

The existing code-evidence configuration now records optional
`source_owned_data_regions`. There are 1,870 exact spans accounting for 3,766
bytes: the debugger's 28-byte inline packet and 3,738 alignment bytes. Each
record pins the owning source, complete owner extent and original bytes.
Compiler data mapping symbols and emitted alignment, together with native
branches or returns, supply the role evidence. These classifications add no
C bytes or new ownership.

A bounded pass over 1,863 previously unclassified two-byte gaps qualified 1,685
spans: 1,168 compiler-emitted alignments, 511 explicit C post-function zero
alignments and six authored assembly alignments. The retained complete linked
texts match the fixed native extents. A source-layout interpretation, actual
object bytes and data mapping symbols identify each padding directive; unknown
forms stay unresolved. Independent review checked the method and ledgers,
all 511 explicit terminal source directives and three physical witnesses.
Six records in four renamed offer-state users were rebound only after fresh
matching output confirmed their roles; the earlier source pins remain historical.
The new linked offer controller contributes two more two-byte alignment records.

A separate old-assembler check establishes 161 further two-byte spans: 131
come from GNU 2.10.1 alignment directives and thirty are zero-filled linker
tails. Retained compiler output and source-object witnesses establish their
roles across 111 owners; the current full build and changed-source controls
verify the complete native extents. Eleven additional alignment spans / 22 bytes
come from the matching row 85 counter-choice bodies, with actual compiler
assembly, object data symbols and native bytes agreeing.

The remaining seventeen gaps / 34 bytes stay explicit: fifteen are authored
NOP instructions after returns and two audio tails have unresolved source-layout
attribution. They have not been relabelled as padding. The known data total is
22,618 bytes; 4,718 bytes inside estimated envelopes and 16,432,926 elsewhere
remain unresolved.

The census validates those pins and feeds the spans through its existing known
data handling. A conflicting strong instruction remains an explicit ambiguous
instruction/data result; the field cannot suppress execution evidence. The
ordinary map and display partition remain separate from these overlapping
source-owned roles. Tests reject stale pins, malformed or overlapping records
and preserve that execution conflict. Complete code inventory and executable
write domains remain unresolved.
