# Factory slot 11 and scene kind 21

This connected path has twenty-five matching C extents, 5,752 bytes: resource factory
slot 11 creates a contact trigger, its paired collision callback submits scene
kind 21, and that scene initializes, processes input, refreshes selection, manages a
quantity editor, draws labels and a tile frame, and shuts down. The names describe observed catalog and selection accesses; they
are provisional. Compiler matching, static ownership and gameplay behavior are
separate claims. No gameplay run is claimed here.

| Function | ROM offset | Full extent |
|---|---:|---:|
| `frame_create_scene_trigger` | `0x3ACCC` | 148 |
| `frame_scene_trigger_contact` | `0x111F8` | 68 |
| `scene_catalog_initialize` | `0x41C4C` | 700 |
| `scene_catalog_step` | `0x41F08` | 876 |
| `scene_catalog_selection` | `0x42D38` | 200 |
| `scene_catalog_shutdown` | `0x42FE8` | 36 |
| `scene_catalog_update` | `0x42274` | 196 |
| `scene_catalog_draw` | `0x42338` | 208 |
| `scene_catalog_begin_quantity` | `0x42E00` | 192 |
| `scene_catalog_quantity` | `0x42EC0` | 160 |
| `scene_catalog_build` | `0x430A4` | 80 |
| `scene_view_draw_frame` | `0x34480` | 432 |
| `scene_catalog_fill` | `0x42408` | 588 |
| `scene_catalog_prepare` | `0x42654` | 664 |
| `scene_catalog_basic_value` | `0x428EC` | 120 |
| `scene_catalog_page_value` | `0x43074` | 48 |
| `scene_catalog_has_next` | `0x430F4` | 40 |
| `scene_catalog_option` | `0x42BF4` | 324 |
| `scene_catalog_notice` | `0x4311C` | 156 |
| `scene_catalog_previous` | `0x431B8` | 60 |
| `scene_catalog_next` | `0x431F4` | 80 |
| `scene_catalog_is_basic_row` | `0x43244` | 32 |
| `scene_catalog_refresh_basic_arrows` | `0x42F60` | 136 |
| `scene_catalog_refresh_page_arrows` | `0x43264` | 104 |
| `scene_catalog_refresh_quantities` | `0x4300C` | 104 |

Every extent includes its literal pools and original trailing alignment. The
constructor ends at the distinct original no-op entry `0x3AD60`; that four-byte
callee remains original and receives no C credit. The contact callback ends at
the distinct movement callback `0x1123C`. The initializer and step own the
adjacent ranges through `0x41F08` and `0x42274`. Selection owns its pools through
`0x42E00`; shutdown ends at the distinct `0x4300C` helper.

## Entry types and transfer evidence

The resource factory table at `0x4F278`, slot 11 at `0x4F2A4`, contains
`0x0803ACCD`. The existing `ResourceObjectFactory` uses two byte arguments.
The constructor has those compatible formals, then uses explicit low-byte
word locals for the payload provider. Its serialized payload is a 12-byte,
word-aligned partial record: ID word at zero, signed X/Y halfwords at 4/6,
width/height bytes at 8/9 and a selector byte at 10. Coordinates multiply signed
halfwords by 65,536. The selector is zero-extended into a halfword at object
`+0x64`; its field width is not inferred merely from the payload byte.

The full partial `SceneTriggerView` begins at the object base, size 204 and
alignment 4. Its player byte is at `+0x13`, state byte at `+0x4D`, selector at
`+0x64`, step callback at `+0x88`, bound count at `+0xAF`, four signed bounds at
`+0xB0..B3`, bound kind at `+0xB4` and paired callback at `+0xC8`. The constructor
sets flags `0x20404`, resets transition state, installs callback `0x080111F9`
and original no-op `0x0803AD61`, and records symmetric width/height bounds.

The callback's formals and role field use the existing two-pointer
`CollisionCallback` contract. The copied ARM collision dispatcher supplies both
objects in R0/R1, invokes the candidate's `+0xC8/+0xCC` slot, then handles the
reversed pair. The generic one-argument actor `on_interact` view remains a
separate provisional access view; this batch changes none of its declarations.
The new callback requires the other object's ID zero and state 16, reads
`g_input_pressed[other.player] & 1`, submits kind 21, mode zero and the owner's
halfword selector, then clears input. It does not test or write owner state.
This differs from the preceding contact-action callback at `0x111AC`.

The scene callback table at `0x5797C` uses 12-byte begin/step/end rows. Kind 21
contains `0x08041C4D`, `0x08041F09`, `0x08042FE9`. The accepted scene loaders call
these no-argument callbacks. Actual factory, collision and scene callback
assignments are checked with the pinned compiler; restored incompatible
factory word formals and `FrameObject *` collision formals are rejected.

## State, input and display behavior

The new scene header supplies partial, overlapping RAM views. State at
`0x030021C8` has page start, count, row, value and selector bytes at offsets
0..4; its compiler size/alignment is 8/4. The page-start name follows the
original page navigation helpers' four-entry increments and decrements. The
world view at `0x03003950` has an eight-byte clock at `+8`, quantity bytes at
`+0xE0`, value bytes at `+0xE9`, a catalog pointer at `+0xF0` and eight-byte
entry strides at `+0xF8`. The entry member contains the observed 14-entry
prefix for known selectors 0..13, giving this partial world view size/alignment
360/4; its complete capacity is unknown. These declared array lengths describe observed
accesses, not validated capacities. The catalog count is a one-byte,
`packed, aligned(1)` read view of the pointer target; the recovered drawing and preparation helpers also read a word pointer at
target `+4`; these views do not claim a complete target record.

Initialization captures the requested selector, clears request selection,
quantity and phase, and derives count/value through those views. Signed clock
hour comparisons against the ROM records at `0x7FB48/0x7FB50` gate selectors
7/9. Selector 4 changes the first/action/last row limits and backgrounds;
selector 13 chooses another background. The phase-one branch draws a notice;
the other branch prepares objects, draws labels and calls the recovered panel,
item, heading and refresh helpers. Shutdown runs the second transition,
releases the object list and resets display, palette jobs and object slots.

The step callback keeps request phase zero's directional navigation and
confirmation, phase two's quantity edit and commit/cancel, phase one's notice
dismissal and phase three's local pressed-input mask. Shared and local pressed
arrays are distinct: phase zero gates direction with the shared array, reads
actual direction through the local array, then captures a fresh shared word for
confirmation. Phase two captures local words separately before and after the
quantity helper. It updates quantities, game value and flags on object slots
11/12 only on their original branches. Phase three masks the captured phase
word with local input; it does not turn that test into a new boolean condition.

Selection preserves the captured selector across an opaque item-refresh call:
selector 4 switches object zero's subtype 10/12, updates the selected row and
uses ID offsets 123 or 38. Other selectors use offset 39. Object pointers are
read again after refresh calls, and page/row bytes are read afresh for the fill
and draw calls. It then sets variant 58. A changed variant control differs at
all three actual call sites.

Two allocation hints express real value lifetimes. Initialization's R4 style
value is assigned after the first text lookup and stays live through the first
draw and second lookup to become the second draw's real argument. Step's R1
input value is assigned by each genuine input read; each captured word is dead
before any provider call, or is read on a path with no intervening call. The
next phase read starts a new lifetime. Removing these hints alone yields
700/79 and 876/10 byte differences. No instruction bodies, artificial reads,
volatile accesses or dummy dependencies are embedded.

## Explicit original helper boundary

Selection, object preparation, item drawing, panel filling, its value providers,
the paging predicate and the text/quantity helpers are recovered. The bodies below
remain original. Their no-result call contracts use `void`
because these callers consume only effects; this is a scoped declaration, not
proof of the original source return type. The recovered draw/fill entries retain full
word arguments: their native prologues preserve incoming words and use word
index arithmetic, while the reconstructed callers explicitly load bytes or
pass zero. The remaining original helpers consume no incoming arguments on
the observed paths.

| Original helper | ROM offset | Retained static extent |
|---|---:|---:|
| Confirm | `0x42964` | 656 bounded envelope, including two original zero alignment bytes |

These are local static boundary estimates, not an exhaustive inventory. The failed
item-drawing source attempts remain private: first 220/197, followed
by genuine iterator/common-branch/slot-view trials 200/174, 200/177, 192/194.
They receive no C credit. The unconverted helpers may mutate scene state or
object pointers. Unchecked player, selector, object, array and resource inputs
remain unchecked; no runtime capacity or pointer-target validity is claimed.

Fresh canonical verification covers the six sources and all 37 connected
accepted providers/dispatchers: 43 positive/changed-source pairs, plus six
strict diagnostic pairs. Pinned layout controls reject a shifted player,
incorrect object packing, default count-view alignment, the former one-entry prefix and a byte selector;
the byte-selector factory also fails the actual ROM comparison. Removing an
actual audio prototype fails strict compilation. Native sections, pools,
alignment, current literal headers, source changes and global aliases are
audited separately. Whole-ROM integration remains a subsequent publication
gate, not a claim made by these local proofs.

## Quantity and text continuation

The second connected batch adds five extents, 1,060 bytes. The initializer and
step now call the four recovered helpers by their own names. These are only
identifier changes at the existing addresses: update `0x08042275`, headings
`0x080430A5`, quantity `0x08042EC1` and quantity setup `0x08042E01`. Both callers'
body constants, control logic, compiler profiles and extents are unchanged;
the complete affected literal importer closure is refreshed.

Quantity setup reads the selected quantity byte into a word. Zero plays cue 3
and returns. Otherwise it sets phase 2 and parameter 1, selects the font, loads
the fixed frame resource and measures text 439. Its unsigned width calculation
is `((width + 7) >> 3) + 2`; centering also uses an unsigned shift, preserving
the original word behavior if the measured width is out of range. It selects
the text layer, stages the captured available quantity, draws texts 438/439,
refreshes the quantity label and plays cue 1. The captured quantity stays live
through the opaque display calls.

The quantity label toggles object slots 12 and 11 from parameter==1 and
parameter==available quantity, clears its tile rectangle, formats the quantity
and draws it. The 20-byte native stack frame has eight outgoing argument bytes
and a 12-byte text region. This is not a general formatter capacity guarantee:
the accepted formatter can produce more than twelve bytes for wider word
inputs. The recovered setup initializes parameter 1 and the step edits it
against a byte quantity, but external writers, row validity and gameplay
coverage are not complete. No new guard or larger stack allocation is added.

The label updater handles the selected row versus the action row, request mode
and selector 13's object visibility. Its real zero color is assigned within the
actual rectangle-fill argument and then used as the later label's style. That
ordinary C lifetime change closes the initial 196/5 mismatch without new
traffic. The headings helper reads the signed value word at world `+4`, stages
it as a text substitution and draws text `0x184C`. The separate eight-byte,
word-aligned access view overlaps the existing world view; it does not claim an
independent object or complete world structure. The signed word type follows
the already accepted game-value update provider.

The frame drawer owns `0x34480..0x34630`, including its two-byte original zero
alignment and three literal words. The adjacent fixed-resource loader remains
a distinct accepted function. Full word X/Y/width/height arguments are retained;
only right and bottom endpoints wrap to bytes. It draws the three-by-three
frame pieces in the original order, with the center last:

| Row | Left | Middle | Right |
|---|---:|---:|---:|
| Top | tile+0 | tile+1 | tile+2 |
| Middle | tile+3 | tile+4 | tile+5 |
| Bottom | tile+6 | tile+7 | tile+8 |

Each draw reloads the background word, tile halfword and palette halfword from
`0x03001F04/1F08/1F0A`. Tile addition precedes palette OR and then wraps to a
halfword; the rectangle provider itself accepts a full word. Separate inner
width/height values and assignments in their actual draw arguments recover
the native lifetimes: 412/351 becomes 432/28, then 432/12, 432/10 and 432/0.
No register binding is needed. Dimensions below two, wrapped endpoints and
other unchecked geometry retain their original behavior.

The three original incoming frame-drawer sites besides quantity setup and the
recovered notice remain unconverted at `0x21B9C`, `0x343EC` and `0x347EC`.
Their existence is static evidence, not reconstructed source or runtime coverage. The selected
and fixed frame-resource producers are included in the current proof context.
The five new functions have real changed-source and strict diagnostic controls;
layout/type checks distinguish byte equality from a correct word rectangle
prototype, signed value view and word geometry contract. Prior failed sources,
the former narrower private rectangle declaration and raw comparisons remain
local evidence. Whole-ROM equality is checked separately at publication.


## Panel, values and paging continuation

Four further connected extents add 796 matching C bytes. Panel filling at
`0x42408..0x42654` selects either the catalog record's slot array or the
selector's page slot array, using the same full word offsets as the original.
It skips item details for selector 4's heading rows or a byte kind of 255,
draws the name and details, and stages a computed value unless the refreshed
kind is 255 or selector is 13. Opaque text calls may change memory, so the
kind and selector reads remain at their observed uses. The captured price-slot
pointer is a separate real lifetime; the two value branches join before the
number-field call. These ordinary C lifetimes close the first 572/558 attempt
through 588/13, then 588/1 and finally exact equality. No register binding is
used.

For selector 4 the panel draws five quantity captions, advancing the tile
result after each line. Its captured quantity root and explicit byte address
calculation preserve the original addition operands. For a selected heading
row it copies the heading text into the original 32-byte local text region,
appends the suffix and resource 37, stages the selected value byte and draws
both heading and explanatory text. The 44-byte native stack frame includes
twelve outgoing argument bytes. The 32-byte region is a source reconstruction,
not a proof that every unchecked text expansion fits; no guard, extra storage
or gameplay claim is added.

The new overlapping world view has quantities at `+0xE0`, values at `+0xE9`,
a record pointer at `+0xF0` and page records at `+0xF8`. The catalog record has a
count byte at zero and a word slot pointer at four; each page similarly has a
value byte and slot pointer at four. Their compiler layouts are eight bytes,
word aligned. The context from `0x03003A40` contains the record pointer and the
same page prefix at offset eight. These access views overlap the existing
world declaration and do not establish independent allocations or a complete
world object. Slots are four-byte records accessed only through their first
byte, so their local view has byte alignment. Both page declarations cover the
observed selector prefix 0 through 13; complete capacity and pointer-target
validity remain unverified.

The five caption-position records at `0x7FB58` have four-byte stride and byte
X/Y fields. The value-rate prefix at `0x7FB6C` has two unsigned words per selector.
Its fourteen observed records end at the separately addressed suffix `0x7FBDC`.
These are static address/layout findings; no original text or table contents
are embedded in the recovered source. The page-value helper multiplies the
catalog's value word by the page rate. The basic-value helper admits kinds
through 117 except 63, kind 210, and the specific kind/selector combinations
observed in its branches (143 with 3 or 12, 125 with 8, 63 with 0, and 129 with
3). Other cases return zero. Both products use unsigned word arithmetic,
including wrap before the logical shift by sixteen. Catalog kind and selector
ranges remain unchecked.

The next-page predicate accepts and returns bytes. A zero count returns zero;
otherwise it tests the first offset against `(count - 1) & 0xFC`. Its full
forty-byte extent ends at the distinct notice entry `0x4311C`, including the
original zero alignment. It is used by the matching object preparation
and the recovered paging path. The value helpers own `0x428EC..0x42964` and
`0x43074..0x430A4`; their following original confirm entry and already accepted
headings helper are separate extents.

The initializer, step and selection now name the recovered fill provider at
its existing address `0x08042409`. These are exact identifier replacements;
body logic, constants, controls, profiles and extents are unchanged. Current
literal importers and actual accepted providers are reverified with real
changed-source controls. Pinned compiler diagnostics check the new partial
layouts and reject a one-page prefix, wrong field widths or packing and an
incompatible byte argument for the full-word value provider. Strict diagnostic
compilation also rejects an actual missing value-provider declaration. Failed
sources and comparison bytes remain private. The other listed original helpers remain explicit
and receive no new C credit.


## Paging and quantity-caption handoffs

Six connected extents add 516 matching C bytes. The input step calls previous
or next paging, whose byte-return predicate compares the full selected scene
word with the action-row byte. For a basic row the handlers edit page_start;
for other rows they edit row. Previous does nothing at offset zero and otherwise
subtracts four. Next calls the recovered count predicate before adding four.
Both retain the original byte stores and wrap behavior; an externally written
nonzero offset below four is not newly guarded.

The basic-arrow refresher clears slots 11 and 12 for selector 4. Otherwise
slot 11 follows page_start!=0 and slot 12 follows the count predicate. The
page-arrow refresher similarly sets slots 13 and 14 from row!=0 and the
row/value count predicate. These preserve word flag loads and bit-zero changes;
object pointers are assumed valid by the original code. The special selector
path and the predicate handoff remain connected to the accepted object creator.

The quantity-caption refresher draws the same five quantity and position
records as the panel, following a font selection and tile-rectangle clear.
Each draw's returned tile is the next draw's input. The captured byte root,
actual byte-address calculation and five-record coordinate cursor require no
register binding, new traffic or extra storage. The existing input step invokes
this helper after editing the selected quantity. No additional table capacity
or pointer validity is inferred.

The paging handlers own `0x431B8..0x431F4` and `0x431F4..0x43244`. Their row
predicate owns the next 32 bytes through `0x43264`; the page-arrow refresher
owns `0x43264..0x432CC`, including its internal pools and alignment. The
separate original entry at `0x432CC` is outside this batch. Basic-arrow refresh
owns `0x42F60..0x42FE8`, ending at the already recovered shutdown entry; quantity
captions own `0x4300C..0x43074`, ending at the recovered page-value helper.
These full boundaries come from local control flow, pools and adjacent entries,
not from treating the mapped inventory as complete.

All six ordinary C sources match their entire original extents and have genuine
changed-source controls and separate strict diagnostics. The existing step's
previous, next and completion-caption call names change only at their existing
addresses. Current literal importer and actual caller/provider closures are
refreshed with the final headers. The original confirmation handler remains explicit; useful failed reconstructions
and raw comparisons are kept locally. Static routing, compiler equality and
runtime behavior remain separate claims.


## Entry transfer and notice path

The recovered input step calls `scene_catalog_option`, which indexes the active
four-byte entry using the full scene word plus the page-start byte. Kind 255
returns immediately. Kind 63 in selector 0 submits the existing condition
triple. Selector 5 accepts the byte-wrapped interval for kinds 195 through 200
and clears the actual world byte at +43E; other selectors except 13 require a
nonzero recovered basic value. A failed gate draws the recovered notice.
These inferred role names describe the static routing; they do not establish
an item category or gameplay outcome.

For selectors through 12, kind 125 updates relation record 12 by -3, then the
fresh entry kind goes through the value provider and game-value updater. The
heading is rebuilt and cue 5 plays before choosing the selector's destination
list. Higher selectors play cue 1 and use observed list 13. A count/capacity
check precedes the canonical entry-add provider, but the scene's value byte
increments without examining its return. The canonical compact provider then
removes the original entry and the scene count decrements. The original
one-way arrow changes are retained: a failed basic count predicate clears
slot 12 and a successful page predicate sets slot 14. No extra capacity,
underflow, object or input guard is introduced.

The local transfer view reuses the accepted `ConditionActorEntry` and
`ConditionActorEntries` types. Their kind/value1/value2 bytes, count/capacity
bytes and word pointer follow the accepted add and compact consumers. The
world prefix spans through the observed +43E byte, contains fourteen observed
lists at +F8, and has pinned compiler size 1,088 and alignment four. It is an
overlapping partial view at the existing world root, with the list pointer at
+F0. The byte's provisional availability name follows the accepted add
producer, which sets it for kinds 195 through 200, and this consumer clearing
it; complete storage, list contents and pointer validity remain unproved.
Wrong field widths, a one-list prefix and the wrong +43E offset are rejected
by separate compiler layout diagnostics.

The notice drawer captures background control, shows and clears background 1,
loads the existing frame resource and uses measured text width to center a
four-row frame. It then selects the same text control and font, draws the
requested line, restores the existing background control, sets transition
state 3 and plays cue 3. The incoming word is explicitly narrowed to an
unsigned halfword for text lookup. Current mapped calls supply text IDs 292,
293, 295 and 297; matching also supports a halfword formal, so this does not
claim a uniquely recovered historical declaration. The word contract preserves
the observed low-halfword consumption without changing an original caller.

Both ordinary C bodies match complete extents: `0x42BF4..0x42D38` and
`0x4311C..0x431B8`, including their pools and alignment. Real changed-source
controls, strict missing-declaration controls and current accepted literal
importers and actual providers are verified separately. The existing step's
option alias is the sole accepted caller source change, at the same address,
with its constants, body, control and compiler profile retained. The original
confirmation caller remains explicit;
failed source representations and raw comparisons are preserved privately.
Static mapping, compiler equality and runtime behavior remain separate claims.


## Item display refresh

The initializer and selection controller now call the recovered item drawer at
its existing address. Its complete `0x42338..0x42408` extent is 208 bytes,
including internal literal pools and the original two-byte zero tail. The
separate panel provider begins at `0x42408`. The two caller source changes are
exact alias replacements; their constants, controls, types and profiles remain
unchanged. An unused old draw-address binding in the step metadata remains a
same-address compatibility alias, without a caller-body change.

The drawer returns at initial selector 4. Otherwise it visits eight object
slots in reverse order, from slot 9 through slot 2. Each iteration reloads the
selector. Ordinary selectors use the first four basic entries and four page
entries; selector 4, if an opaque callback changes the state during this loop,
uses five basic entries and three page entries. The actual first record pointer
and selected page pointer follow the existing context view, with four-byte
entry strides. The initial offsets are incoming words, and current direct
callers provide page-start and row bytes. Pointer and offset domains remain
unchecked; the observed fourteen-page prefix is not a complete capacity claim.

A kind byte of 255 or a descriptor word of 317 clears object flag bit zero.
Other kinds load the descriptor's full ID word and store its low halfword at
object +0A, call the existing item refresher, then reload the object pointer,
set flag bit zero and select variant 58. The source does not rename the
separate actor ID field at +08. Its two genuine kind-field consumers compile
to the original single byte load before any opaque call. Object-pointer
reloads and the full-word descriptor comparison remain as in the original.

The real page pointer-field address is captured at context +12, with page
stride eight. The helper computes that address before the incoming second
index's byte offset, then reads the actual pointer field and adds the offset.
One short R1 annotation applies to this real offset only. The native value is
defined at `0x4239C`, consumed at `0x423A0` and overwritten by the selected-slot
phase at `0x423A4`; no opaque call occurs in this interval. Removing the sole
annotation gives a 98-byte mismatch. Earlier long R7 parameter constraints
miscompiled values and remain excluded; they are absent from this source.

Pinned compiler diagnostics confirm the existing context size/alignment 120/4,
page and record 8/4, byte-access entry 4/1, descriptor 24/4, and actual pointer
field offsets and strides. The generic `FrameObject` declaration measures
312/4; this drawer directly uses only its +0A halfword and +0C flags word.
Neither that declaration nor byte equality proves the allocation capacity of
any particular object. A mistaken 216-byte generic-size assertion was rejected
and retained privately; no shared object layout was changed to satisfy it.
Wrong entry stride, pointer-field offsets, provider types and actual missing
provider declarations fail separate diagnostics.

The complete current literal importer and real caller/provider closures have
fresh positive and changed-source controls, with strict diagnostics outside
the acceptance profile. Register allocation evidence, failed source shapes and
raw comparisons remain private. The confirmation body
remains an explicit original. These findings establish static routing and compiler
equality; they do not establish complete storage or gameplay behavior.


## Catalog object preparation

The initializer and step controller now call the recovered preparation entry
at the same address. This body owns `0x42654..0x428EC`, all 664 bytes including
its internal pools and original alignment. Its final literal word already ends
on the compiler's four-byte section boundary, so no source alignment directive
is needed. The following basic-value entry remains separate. Only the two
actual caller identifiers and their same-address metadata aliases change;
existing caller controls, profiles and constants remain unchanged.

The ordinary-selector path creates the header and both paging-control pairs,
then tests the accepted page predicate before hiding unavailable arrows. The
selector-four path uses its distinct header and control IDs and clears the two
control objects' display-layer bits. Both preserve the original flags updates,
subtype operands and palette/layer arguments. Pointer returns remain unchecked.
The record and page predicates use fresh state-byte values after the opaque
constructor calls rather than cached initial selection values.

For ordinary selectors, the main loop visits eight object slots, nine through
two, with IDs 46 through 39 and coordinate/palette operands nine through two.
Each iteration reloads the selector. Ordinary selectors divide four basic and
four page entries; selector four, if an earlier opaque call changes that byte,
uses five basic and three page entries. The two source paths keep their actual
record/page pointer reads and adjusted row indices. A kind byte of 255 creates
fallback subtype 229 and clears flag bit zero. Other kinds use the descriptor's
complete word at offset zero as the subtype. There is no additional descriptor
317 guard in this preparation path; that guard belongs to the item drawer.

The selector-four branch first creates five entries with IDs 123 through 127,
subtypes 229 through 233 and variant 11. It then processes four page entries in
reverse order. The native success and empty branches intentionally use different
slot bases: nonempty entries store at row +2, empty entries at row +6. Empty
entries clear flag bit zero. The final two control flags are cleared as in the
original. These accesses preserve the observed behavior without assigning an
unsupported gameplay purpose to the asymmetric slots.

Two ordinary inline accessors express the real data producers. The selected-page
accessor starts with the actual pointer-field address at context +12, forms the
selector stride and row stride separately, reads that pointer field and adds the
row offset. The descriptor accessor accepts the actual selected entry; its
catalog-pointer lifetime begins before its real kind-field consumer. This
recovers the native table-load and kind-copy order. Passing an already captured
kind to that accessor left a four-byte mismatch. Earlier merged base paths and
kind snapshots remain preserved as unmatched source and raw comparison evidence.
No register binding, volatile access, extra read or dummy initializer is used.
The two genuine kind consumers in each selection branch produce the original
single byte load before the descriptor word and constructor call.

The constructor at `0x08027EE4` is the already accepted 240-byte
`frame_create_scene_object` provider; it earns no new credit here. Its canonical
four-word declaration comes from `frame_actor_scene.h`. It preserves all four
incoming words before allocation. The first two words are stored as halfwords
but also select coordinate and animation tables and the special full-word
subtype 267 and IDs 110/111. Those stores do not justify narrowing the API.
The accepted 64-byte allocator requests 320 bytes; the existing generic
`FrameObject` declaration measures 312 bytes with alignment 4. The request and
measured view do not prove complete storage contents, arbitrary pointer
validity or allocation success. The accepted 608-byte callback and connected
position, animation, state, variant and palette providers are rechecked with
current headers. An earlier private assumption that the constructor was still
original was corrected against the live accepted manifest and retained as a
superseded evidence predecessor.

Pinned compiler diagnostics check the four-byte slot stride, eight-byte page
and record strides, fourteen-page observed prefix, 120-byte context, full-word
descriptor ID, actual flags fields and the constructor/variant/predicate API
assignments. The two-bit display layer uses the observed byte +D5 mask;
changing its width fails layout checks and changes the actual preparation
bytes. Omitting the real constructor declaration still gives identical bytes
under the permissive legacy profile, but the separate strict diagnostic rejects
it. This failure case keeps declaration completeness distinct from byte
matching. Normal and strict positives and actual changed-source controls are
fresh, as are the complete current shared-header importer and provider closures.
The confirmation handler remains an explicit original. These results establish
static routing and compiler equality, not complete formats or gameplay behavior.


## Independently bounded panel-mode selector

The [selector at `0x080343EC`](../src/scene/scene_view_draw_panel_mode_unrooted_343ec.c)
owns 148 complete bytes: 108 instruction, 36 literal/switch-table and four
alignment bytes. It uses the existing word background at `0x03001F04` and the
actual rectangle-fill and frame-draw providers. Its unsigned mode mapping is:

| Mode | Clear rectangle `(x, y, width, height)` with tile zero | Draw frame `(x, y, width, height)` |
| --- | --- | --- |
| 0 | `(9, 14, 22, 1)` | `(9, 15, 22, 6)` |
| 1 or 3 | None | `(9, 14, 22, 7)` |
| 2 | `(9, 14, 22, 22)` | `(9, 15, 22, 6)` |
| 4 | `(9, 15, 22, 6)` | None |
| Other | None | None |

The 22-row clear is preserved without a clamp; initialized background state and
backing for every reached span remain conditional. The common height is an
actual input to case four's clear as well as the frame draw. Case two separately
prepares its clear height before the shared frame geometry, matching native
value lifetimes with ordinary C and no register constraint.

Normal and strict full matches and real case-two clear-height controls pass.
Checks compile the actual new definition and each actual provider separately,
with their existing contracts and dependencies. The current graph and bounded
entry-word searches establish no incoming caller or entry pointer. The chosen
one-word mode/void interface and any unused formals remain provisional. This
replaces one 148-byte estimated row and adds no mapped extent or runtime claim.
