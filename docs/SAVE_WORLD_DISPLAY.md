# Selected-row display producers

Seven connected routines add 764 verified matching C bytes: row palette refresh
at `0x0801EEE8` (88), indicator creation at `0x0801EF78` (116), gauge scaling at
`0x0801EF40` (56), percentage scaling at `0x08027524` (20), and percentage ratio
at `0x08027538` (16), plus the row gauge/object updater at `0x0801EB84` (280)
and window completion at `0x0801EAC8` (188). Each complete linked extent includes its alignment and
literal pools. Five sources use ordinary C without register bindings. The 280-byte updater
uses two scoped semantic C register constraints described below; window completion
uses three meaningful scalar/address constraints. Every actual
changed-source control rejects against the fixed reference.

These functions connect the published 56-byte selected-row transition and
nullable object teardown to the original view updater at `0x0801E798`. That
updater tests the row flag `0x400000` before palette refresh, and calls the gauge
scaler for the selected needs display. The accepted gauge updater at `0x0801EB84` iterates eight entries and calls
indicator creation only for an empty slot. The main view function ends at the next prologue `0x0801EAC8`;
its complete 816-byte body is reconstructed below. Static call findings alone do not add C coverage.

Palette refresh compares the full incoming row index to the selection byte at
`0x030040E0 + 0x31`. Only the selected row loads original palette resources at
`0x080D04CC` and `0x080D098C` with extra banks one and two, then the palette-range
configuration at `0x08053518`. Every incoming row clears its flag `0x400000` at
`0x03004130 + index * 56 + 4`. An integer address view expresses these observed
byte strides and the flag-word offset; it introduces no new storage allocation.
The resource data remains in the original ROM and is not included in source.

Indicator creation allocates object id 24, stores it in the requested row slot,
clears the halfword at object `+0x0A`, assigns flags `0x200019`, and clears the
observed display-layer bits. Two original coordinate bytes per entry at
`0x08053528` produce fixed-point positions `(x * 8 + 2) << 16` and
`(y << 19) - 0x20000`. The object acquires palette slot six and animation record
`0x08053538`. The coordinate pair is explicitly packed: its observed stride is
two bytes, whereas this compiler's default two-byte struct occupies four bytes.
The initial unpacked candidate failed across 71 bytes; the packed pair gives
the complete 116-byte match. The original body does not check allocation failure
or its incoming byte index. Eight slots follow from the connected loop; that
loop does not validate arbitrary callers or establish a complete resource bound.

The gauge/object updater selects the same 56-byte row from the current selection
byte. For each of eight entries, a `4 << index` flag or changed need byte causes
a fresh byte snapshot at row `+0x30 + index`, a second need query for the displayed
level, and a one-column, three-row map copy from the pointer at `0x03004124`.
A forced refresh skips the comparison query, while the changed-value branch
performs that query as well. The original separately queries the comparison, snapshot and gauge inputs;
the source retains that observed call sequence. A zero row countdown and `0x400 << index` flag
require an indicator, creating it only if its slot is empty. Other cases release
a non-null slot through the published teardown helper. The final `0xFFFC0003`
mask clears the observed update and indicator-request bits.

The updater retains the actual object-slot byte offset in `r9`, incrementing it
by four for the eight slots. A semantic inline reader briefly holds the computed
slot address in `r0`: row base, plus the observed `0x10` object-array offset, plus
the live slot offset. It makes no call and releases that binding before either
object lifecycle callback. These constraints recover original address lifetimes
without embedding instructions or changing the algorithm. The initial ordinary
pointer loop became a moving object pointer and failed at 272 bytes. Keeping
the scalar slot offset recovered 280 bytes; the scoped address reader and the
observed direct-global argument form for the first need queries closed the full
extent. An otherwise exact trial with an unnecessary cached-pointer binding
remains private; the accepted source uses only the two necessary constraints.

The percentage helpers pass word products to the original signed division
provider at `0x0804C8C8`. Scale narrows only its second formal to an unsigned
halfword, multiplies it by the full first word, and divides by 100. Ratio
multiplies the full numerator by 100 and passes the full denominator unchanged.
Unsigned intermediate multiplication retains the observed low 32 bits before
the explicit signed argument conversion. No new denominator guard or saturation
is added, and the provider's exceptional-case behavior remains an original
implementation dependency. Gauge accepts a signed halfword value, unsigned
halfword maximum, and byte step count; for positive values it narrows the ratio
result to a halfword before scaling by `steps + 1`, then clamps the signed result
to zero through the step count. Nonpositive values return zero.

Window completion at `0x0801EAC8` accepts a full row index and an explicitly
narrowed byte option. Option one stores a zero countdown; other byte values store
twenty. It then recomputes the row view and reloads that countdown. A nonzero
countdown configures window one, its rectangle and a twenty-step vertical move.
It writes a five-by-fifteen background map from the pointer at `0x03004210`, sets
row flags `0x3FC`, invokes the matching gauge/object updater, then sets the row's
ready word to one. It retains the original unchecked index, full flag sequence
and absence of a map-pointer guard; timer units and UI behavior remain provisional.

The real index-times-seven intermediate uses `r0` only before the row is formed,
then its times-eight byte offset uses `r6` across the window and map calls. A
separate inline address view briefly retains `base + 4` in `r1` and returns the
sum with the byte offset, without overwriting that base-address scalar. It makes
no call and the binding ends before the gauge updater. The initial multiplication
candidate matched 188 bytes with nine differing register bytes. Splitting the
actual seven-times-index intermediate reduced that to four, its scoped lifetime
to two, and the distinct base-address return expression closed the full extent.
The call-clobbered `r0` and `r1` bindings end before calls, while the live byte
offset uses the callee-saved `r6`. No original instructions are embedded.

The existing pinned `binutils2101` assembler profile reproduces the original
zero alignment halfwords in the gauge and percentage helpers. Their modern
assembler trials retained the same instruction bodies but emitted a different
alignment halfword; those failed comparisons remain local. No padding statement,
section stripping, output patch or ignored comparison range is used. Positive
and actual mutated-source objects have `.text` as their only nonempty allocated
section, and the linked extents retain no unresolved relocations.

Proof inputs, failed candidates and raw bytes are retained under ignored
`reports/agents/display_audio/save-stream/`, with fresh canonical proofs in
`selected-row-public-proofs-*`. The ready receipt records exact sizes, symbol
addresses, assembler selection, source and header pins, and negative comparisons.
This establishes source compilation and byte equality. Timer units, complete row
roles, arbitrary index bounds and runtime UI behavior remain uncertain.

## Connected row notifications

Three direct children of the 816-byte view coordinator add 364
matching C bytes: `save_world_show_row_notice` at `0x0801EC9C` (152),
`save_world_show_row_flag_notice` at `0x0801ED34` (124), and
`save_world_show_notice` at `0x0801EDB0` (88). This selected-row display path now
contained ten verified functions and 1,128 bytes before the pending providers
below. The coordinator was unconverted at that milestone; its later complete
match is recorded below. All three use ordinary C and share a semantic
inline centering helper that emits no additional out-of-line function.

The first row helper tests a single snapshot of its row flags. Flag `0x100000`
selects text id 289 and sequence notification 58; otherwise flag `0x80000`
selects id 290 and notification 57. The second helper tests flag `0x40000`,
selecting id 291 and notification 58. Both continue to center the currently
stored result text even when their tested flags are absent. The general helper
first plays animation cue three, then narrows its full incoming text id through
the observed halfword result store. These static roles do not establish the
meaning of the flags, text or audio contents.

Each helper separately looks up the retained result text for width and height,
narrows each returned dimension to a byte, clears the existing notification
active byte, and writes `(30 - (width >> 3)) / 2` and `7 - (height >> 4)` through
the published notification overlay at `0x03005A00`. Signed division truncation,
byte stores and repeated lookup calls are preserved; no clamp or text-bound
guard is introduced. The final call uses the already matching canonical
`scene_submit_default_request(2)` provider at `0x08027DC0`. Shared representation
and source controls are verified without assuming a runtime notice was shown.

## Pending notification providers

Two further direct children of the view coordinator add 124 matching
C bytes: `save_world_show_pending_column` at `0x0802A920` (44) and
`save_world_show_pending_event` at `0x0804560C` (80). The connected selected-row
display path now contains twelve verified functions and 1,252 bytes. Both use
ordinary C without register bindings. Their full extents, literal pools and
alignment match, and their actual changed-source controls reject.

The column provider passes its unchanged word row and column arguments to the
matching `condition_lookup_kind`, adds 6,025 to the returned text index, copies
that lookup into text field one, stores result id 299, then activates the existing
actor scene request. It introduces no row, column or lookup bound. The original
next prologue at `0x0802A94C` belongs to the already matching
`condition_publish_row_displays`; its `resource_set_display_kind` child is also
already reconstructed. Those existing providers receive no additional credit.

The event provider compares world byte `+0x748` with four, selects result id 307
or 306, stores the return from `frame_create_scene_object(193, 266, 15, 0)` in the
existing request's object slot, then activates that request. The selector is
`SaveWorldInitState.prefix.unknown748`, distinct from the aligned countdown
word at world `+0x74C` in `SaveWorldInitState.pending`. Byte `+0x750`, pending row
`+0x751` and pending-column mask `+0x752` are separate observed fields. The
initializer's matching countdown store already uses `+0x74C` and is unchanged.
An earlier private coordinator attempt confused these two offsets; its raw
failure is retained and excluded from coverage. The ordinary event provider
matches after the byte-offset correction. No object-allocation guard, text or
audio-content meaning, complete state boundary or runtime notice is inferred.
Its extent ends at the next original prologue `0x0804565C`.

## View initialization producer

`scene_initialize_view` at `0x0801E5F4` adds 420 matching C bytes. The next
original entry is the coordinator at `0x0801E798`, reconstructed below; the accepted
extent includes every intervening literal and alignment byte. The connected
selected-row display family now contains thirteen verified functions and 1,672
bytes. A real edit of the redraw mask rejects, and the accepted
`scene_initialize` caller is freshly verified with its own changed-source
control. Whole-ROM integration remains a separate gate.

The existing two-word calling interface is preserved. The producer explicitly
consumes the low byte of its mode argument. Mode zero refreshes the row palette;
when the word row index equals the shared selection byte, it copies eight
observed need values into row bytes `+0x30..+0x37`, stages five background
resources, and performs the original map rectangle operations. The loop has
eight iterations; this does not prove that every incoming row index is valid.
Nonzero low-byte mode stores all ones in the row flags. It then configures the
text background/font. Ready value one invokes the already matching immediate
transition, sets flags `0x3FC`, updates the gauges, and restores that ready word.
Flags one and two are always added at the end.

The producer establishes the existing gauge-map pointer at `0x03004124` from the
decoded-word resource result. The explicit pointer cast is a shared access view
used by the matching gauge consumer, without an asset-format completeness claim.
The already named row palette descriptor at `0x080D04CC` is reused. Four other
descriptor letters record only their load order. Their data remains original
ROM input. Its resource producers at `0x0803AFF0` and `0x08034630` are
reconstructed below; the first receives the world child at `+0x20`. This caller
alone does not establish the child's full extent or either provider's complete
role.

Three semantic C register constraints preserve observed lifetimes: a short
row-index access value in `r1`, the bottom row root in `r6` across the transition
and gauge calls, and the final flags pointer in `r0` for its one word update.
The input index and eight-times-index value are ordinary locals. The helpers
inline without additional function spans. Failed fixed-stride experiments that
overwrote a live stride with the row root are retained privately and excluded.
No instruction body, output fixup or allocated section is added. The main
coordinator is reconstructed below; its useful failed C attempts and raw
comparisons remain private and receive no coverage credit. Runtime notices,
background appearance, asset meanings and complete state bounds remain unproved.

## Selected background and palette producer

`scene_view_load_selected_resource` at `0x0803AFF0` adds 236 matching C bytes,
including its two observed zero alignment bytes before the next original entry
at `0x0803B0DC`. This brings the selected-row display path to fourteen verified
functions and 1,908 bytes. The producer and its accepted initializer caller are
freshly compared with actual changed-source controls. It uses ordinary semantic
C without register constraints; a standard alignment directive preserves the
function's trailing alignment rather than adding an instruction body.

The producer selects a resource from the pointer table at `0x08D73650` using
selection bytes zero and two, stages its background data through the matching
DMA resource provider, and fills a four-by-four map rectangle. Incoming tile
and palette words are explicitly narrowed through halfword locals. Its second
resource lookup occurs after those calls, as in the original. Bytes one, three
and four select palette segments with a 32-byte stride. The four-byte union
prefix expresses the original masked word read without traversing beyond a
declared byte array. Only the first five input bytes are accessed; complete
storage and index bounds remain unknown.

When the masked group/variant word equals `0x00030000`, the three palette copy
windows contain 14, eight and eight bytes. Otherwise two windows contain 18 and
twelve bytes. All copies start at buffer byte two or later. The first palette
halfword is deliberately unwritten before the full sixteen-colour staging
call, preserving the original non-clearing behaviour. This establishes neither
an initialized first colour nor runtime palette appearance. The matching
palette wrapper stages all 32 bytes through `display_transfer_palette` and the
existing `heap_copy` address alias, then transfers sixteen halfwords by DMA3.
That C copy helper reads bytes on its unaligned path and words on its aligned
path; the chain is not a BIOS-only transfer, and defined C-language behaviour
for the unwritten colour is not established. Offset-first byte
address calculations preserve the raw instruction scheduling without changing
the selected byte windows. A real copy-length edit from 14 to twelve rejects.
The complete coordinator match is recorded below, with useful failed trials
retained privately.

## Fixed background resource placement

`scene_view_load_fixed_resource` at `0x08034630` adds 48 matching C bytes through
the next original entry at `0x08034660`. The connected selected-row display
family now contains fifteen verified functions and 1,956 bytes. This producer
stores the background word at `0x03001F04`, the tile halfword at `0x03001F08`, and
the palette halfword at `0x03001F0A`, then reloads the tile and stages the fixed
resource at `0x080D098C` through the already matching background resource loader.
These separate global declarations are address views of the same observed
eight-byte placement record. They do not imply independent storage ownership.
The descriptor's asset meaning remains unknown.

The incoming word interface is retained. A halfword local bound to `r3` captures
the palette, and its ordinary word promotion occurs before the stores. That
short semantic lifetime reproduces the original early zero extension; the
value is consumed as the loader's fourth argument and is unused after the call.
No binding spans a call. An actual changed palette assignment rejects, and the
420-byte initializer is freshly verified after both same-address provider
renames. The other accepted selected-resource caller, the 744-byte menu
initializer, now uses the same canonical typed declaration at the same address.
Its existing constant tile/palette arguments preserve the raw call. All current
menu-scene header importers are freshly verified with their own actual controls;
this alias correction adds no source-coverage credit. Genuine compiler-profile
attempts that emitted extra allocated data
were rejected rather than stripped; raw failures remain private. The full
producer extents, pools and source controls pass independently of runtime
background appearance or complete palette/index bounds.

## Complete selected-view coordinator

`scene_update_view` at `0x0801E798` adds 816 verified matching C bytes, through
all intervening literals and alignment to the next original prologue at
`0x0801EAC8`. The connected selected-row display family described here now
contains sixteen verified functions and 2,772 bytes. The full incoming word
index remains unchanged. Its two accepted direct callers, `scene_initialize`
and `scene_primary_step`, retain their existing interfaces and exact bytes.
All twenty-two distinct direct function providers are already reconstructed;
this closes their immediate coordination path without claiming their entire
transitive call graph or the whole game is reconstructed.

The coordinator first refreshes the row palette when flag `0x400000` is set.
Flags two and one separately redraw the world number and formatted clock text,
clearing their respective bits. The ordered notice branches then consume
`0x800000`, `0x40000`, `0x180000` or `0x200000` through the matching notice
helpers. Otherwise, a single pending-column-mask snapshot searches six low
bits, shows the first pending column, and clears only its bit. When that mask
is zero, the separate byte at world `+0x748` may show a pending event and is
then cleared. The independent byte at `+0x750` stores result text 309,
coordinates the sequence notification and activates the scene request before
clearing itself. These names describe the static calls and stores, not the
meaning of original text/audio contents or demonstrated runtime behavior.

The 56-byte row countdown is queried, decremented and stored as a halfword.
When its low halfword reaches zero and the row's ready word is zero, the source
retains that actual zero word as the rectangle tile argument. For the currently
selected view, and only without game flag `0x100000`, ready values zero and one
coordinate the matching begin/finish transitions and gauge updater. Both
transition tests use the existing input halfword table at `0x03004228`, mask
`0x200`, and object states 16 or 27. The source reuses the canonical
`g_input_pressed` and the existing result-id object at `0x030059F0`, replacing
private provisional palette/text aliases. The last need-average query selects
an original background descriptor from the pointer table at `0x08D70E4C` and
stores its decoded map result. No arbitrary row, object-slot, text-buffer or
resource-table bound is inferred, and no allocation, pointer or index guard is
added.

Unsigned index arithmetic preserves the original eight-times-index value and
hands it to the later row operations in each completed notice path. The timer
uses `(eight_index - index) << 3`; the inline ready reader assigns its table
root first, then uses `(eight_index << 3) - (index << 3)`. These are the same
56-times-index byte offset modulo the target's 32-bit unsigned word. Expressing
the two consuming phases separately preserves the original address and saved
index lifetimes without a new read or control branch. The earlier reassociated
and cached-index candidates are retained with their raw differences.

Ten necessary semantic C register bindings remain after eight redundant
bindings were removed and every resulting full extent rechecked. The initial
byte pointer and its mask snapshot briefly use `r0` and `r2`; the available-mask
word uses `r1` until the first matching bit. The later actual bit-clear address
briefly uses `r1` after the notification calls. A pending-byte pointer uses
callee-saved `r8` across its two calls. Its field offset is expressed in
eight-byte units through a short `r2` scalar, consumed before the address is
formed: the observed `0x748` offset is exactly 233 units. The known value fits
both a byte and a halfword; both private forms matched, while the accepted
source uses the halfword form. This temporary unit/type choice is an
implementation view, not evidence for an original array, original declaration
or new game-state bound. It adds no memory traffic or arithmetic to the linked
extent. Removing its binding leaves the three preserved address-register
mismatches. The timer's table root, row byte offset, computed address and ready
word use short `r1`, `r0`, `r2` and `r1` lifetimes. The root dies before the ready
snapshot, and these call-clobbered bindings end before calls. No embedded
instruction body, invented read, volatile qualifier, dummy initialization or
comparison mask is used.

The connected 44-byte `display_fill_background_constant_rectangle` provider at
`0x0800D7FC` now declares its observed incoming tile as a full word and explicitly
narrows it to a halfword before the background-state lookup. The original loads
the sixth stack argument as a word, then performs that narrowing itself. The
new coordinator's unmodified ready word is passed without a separate caller
narrowing, as in the original. The map writer still consumes a halfword. A
minimal guarded `display_map_fill.h` owns this contract; six existing role
headers import it in place of their older narrow declarations. This correction
adds no C-coverage bytes, and all eight earlier direct fill callers retain exact
bytes. All 43 affected existing functions, totaling 11,648 bytes, are freshly
compiled against the final literal header closure with their actual source
controls; each positive matches and each control rejects. The new coordinator's
notification edit rejects at one byte, and the provider's existing x-coordinate
edit rejects at sixteen bytes.

The accepted C objects and linked extents contain only their expected allocated
text sections, resolve at the original Thumb addresses and retain all pools and
alignment. Raw progression from 195, twelve, eleven and three differences to
zero, minimal-constraint trials, the failed wide-offset and neighbouring-field
experiments, and fresh current-header controls remain in ignored local reports.
The original buffer, unchecked row/object access, shared game-state overlays,
countdown units and resource bounds retain their stated uncertainties. Source
byte equality, whole-ROM integration and runtime UI behavior remain separate
claims.
