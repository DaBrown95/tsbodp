# Bounded inventory follow-up, 15 October 2026

This is the earlier bounded checkpoint. The subsequent requested
[whole-ROM survey](WHOLE_ROM_INVENTORY.md) supersedes its open audio-kernel and
conservative phase-column annotations; the historical findings below are retained.

This internal pass reviewed 23 scoped sites or boundary facts across three
connected clusters. Existing maps, matching caller receipts and local failed
attempts were inspected first. Original-image control flow and literal loads
support the static findings below; they do not establish runtime reachability,
complete callback populations or recovered C. Raw traces and comparison evidence
remain in ignored local reports.

| Area | Established static evidence | Confidence and remaining uncertainty |
| --- | --- | --- |
| Scene callbacks | Calls at `0x08027E66`, `0x08027E94` and `0x08027ECA` select fields 0, 4 and 8 of the 12-byte rows at `0x0805797C`. Each observed column has 28 entries. | High confidence from fixed-ROM loads, veneers and matching caller source/control pairs. Runtime kind bounds and unconverted-callback argument contracts remain open; the exporter currently retains a conservative union of all columns. |
| Phase 7 | Callback entries are `0x08024E18`, `0x08025038` and `0x0802579C`. The step has a 708-byte CFG envelope, not the 1,892-byte distance to the shutdown callback. Its guarded nine-case table contains local Thumb blocks. | Static envelopes, not compiler-owned sizes. The initializer's 542-byte envelope excludes two following zero bytes; a future full comparison must examine the proposed 544-byte aligned span. Shutdown has 40 instruction bytes and eight literal bytes. |
| Finalizer | The reviewed 348-byte span at `0x08003248` contains 326 reachable instruction bytes, 20 referenced literal bytes and two zero alignment bytes. Pools are `[0x08003278,0x08003280)`, `[0x08003350,0x08003354)` and `[0x0800339C,0x080033A4)`. | High bounded static confidence. This corrects a prior local two-pool note. The terminal register transfer is a saved-return epilogue; no callback or jump table was found. Ordinary matching C remains unresolved. |
| Renderer | The 1,400-byte envelope at `0x080023E8` contains 1,292 instruction bytes, 96 referenced literal bytes and 12 zero alignment bytes. Nine direct calls reach five providers. | Resource and variant pointer selection is data access, not a code-pointer table. Matching C and universal resource/owner contracts remain unresolved. |
| Object callbacks | `before_step`, `on_step` and `on_remove` are writable object fields at offsets `0x98`, `0x88` and `0x8C`, called at `0x08001D2E`, `0x08001D4A` and `0x08000940`. | Matching consumers establish the slots, object argument and ignored results. Target populations remain open. The step consumer reloads flags after the callback. |
| Copied object ordering | The scheduler's fixed ARM target `0x03002900` maps to ROM `0x0800B840`. Its 284-byte copy contains 272 instruction bytes and a 12-byte pool, with no nested callback/table dispatch. | The historical `frame_draw_iwram` key is retained. Object-table ordering/sort is the supported provisional role; exact comparison semantics and matching C remain to be reconstructed. |
| IRQ/audio handoff | Default IRQ slot 3 handles mask `0x10` (Timer 1); slot 5 handles Timer 0. The VBlank audio veneer reaches ARM `0x03001080`, the accepted 220-byte `audio_mix_frame` extent, comprising 204 instruction and 16 literal bytes. | Copy and fixed-target evidence is strong. Writable handlers and the tick callback remain dynamic; the latter is reloaded after channel mixing. |
| Mixer dispatch | The historical `index_load_runtime_address` at `0x03000D08` identifies the target-pointer load. Index byte loads occur at `0x03000CE4` and `0x03000CE8`, followed by the sum at `0x03000CF8`. | No universal index bound or mask was established. Null slots remain explicit, and eight copied-RAM kernel entries still lack proven function extents. Known source targets do not close the runtime target set. |

The generated inventory already records the reviewed renderer, finalizer and
copied-sort instruction/literal counts and the phase-7 step envelope. This pass
adds no safely established entry or mapped extent, so it leaves those outputs
and the verified treemap unchanged. Proposed column-specific target annotations
and corrected historical role labels remain separate from extent or C credit;
they can accompany the next relevant verified source/map batch.

The published baseline remains 1,678 matching C functions and 236,692 C bytes,
with 500 bytes of separately counted ARM/Thumb glue. The fixed historical
comparison is 319,640 mapped extent bytes; it is not a complete game-code
denominator. Whole-ROM equality, static mapping and runtime behavior remain
separate claims.

The pass ends here. Connected reconstruction resumes with the copied object
ordering routine and the phase-7 callback path, alongside the held ordinary-C
renderer/finalizer work. Exhaustive inventory is not a prerequisite.

## Object visibility helper at `0x080011B8`

The 100-byte helper returns one when `forced_visible` is exactly one. Otherwise it obtains the selected view origin, converts the object's position through the existing point provider, and tests inclusive bounds: X from origin minus 100 through origin plus 340, and Y from origin minus 100 through origin plus 260. The proposed interface is `int(FrameObject *, FrameU8)`; the actual provider definitions and ARM32 point/object layouts pass separate type and offset checks.

The complete native span matches under ordinary and strict compilation. The matching C keeps the real margin value in R6 and the cached origin X in R4 after the provider calls, with each upper-bound subtotal carried in R0. Those GNU register variables describe actual values and overlapping lifetimes; they contain no instruction bodies. The final two commutative operand orders also matter to the emitted Thumb ADD encodings. A changed margin is rejected in both profiles. These results establish one matching source spelling, not the original source or uniquely determined compiler choices.

The non-forced path still requires a valid view-origin entry and representable signed coordinate arithmetic. Type/layout checks do not establish every provider access's effective-type legality, incoming-call coverage or runtime behavior. The full matching and progress gates cover this source. The renderer, finalizer and view-index domains remain open.

## Conditional renderer table bound, 21 October 2026

The runtime installer explicitly creates 128 slots of 320 bytes in one
allocation. The free-list root at `0x030015BC` is the queue's `+4` field;
retain/restore move the existing primary-list roots without creating more
slots. With distinct live pool members, an acyclic stable traversal, count
initially zero and one finalization per eligible node, the collected count is
at most 128. The final permitted table append ends at `0x030028FF`; append 129
would overwrite the copied sorter's first instruction at `0x03002900`.
This bound comes from the explicit pool producer and its stated membership
premises. The public object-table declaration remains unsized.

Removal calls `on_remove` before tombstoning or unlinking the object. The three
currently backed constructor assignments install actor, scene-effect and
need-effect removal callbacks. None directly removes the same owner again.
With its state and auxiliary pointers present, the need-effect callback releases
a separate state node and calls the auxiliary state setter. A live indicator
child later handles that state by requesting removal. Pointer presence alone
does not establish this live-child premise: head-first bulk cleanup can return
the child to the free list before its parent uses the saved pointer. The child
was pushed ahead of the parent, and its removal does not clear the parent's
field. The setter then writes only the slot's state/pending bytes, leaving its
list links unchanged. No intervening reuse is established by this route.
This bounded audit does not exhaust writable
callback provenance, before-step/step effects or generic aliases. Distinct pool
membership and complete writer populations remain requirements for unconditional
table safety. No renderer/finalizer match or new mapped extent follows.

The actor-presence bank has a separate conditional bound. In the retained
50-root / 105-pack serialized population, all 463 distinct factory-seven actor
payloads use IDs 6..41. IDs 18..41 address the bank's 24 bytes; lower IDs skip
the store. An unchecked ID 54 would instead address the low byte of the
need-effect free-list root. Its constructor has an independently established
backing failure before that store. The saved world `+0x740` byte is copied without semantic
range validation, and its later eligibility test does not validate actor IDs.
Reset 42 is skipped; the named default-interaction route from valid actors
restores 18..41. Other saved/menu producers, constructor resource backing and
later subtype or payload writers remain open. A possible numeric alias alone
does not establish a valid write to the other pool.

Startup requests ten 44-byte actor-need states; the allocator rounds the
440-byte request to 448. For a saved byte ID above 31, the actual constructor calls
the initializer that writes eight words at `44 * (ID - 32) + [0,32)` relative to
that allocation. IDs 32..41 have the necessary state backing. ID 54 instead
writes offsets 968..999, outside even the rounded allocation. The inspected
maintained routes neither enlarge nor replace this allocation; restart requests
440 bytes again. This bound assumes a successful allocation and preservation
of its pointer and backing.

The saved route skips 42, while byte values 43..255 remain unchecked and exceed
that state backing. These are invalid or unbacked constructor outcomes, not
additional actor definitions or executable discoveries. No native guard proves
they cannot reach the later presence store. ID 54's unchecked palette expression
also produces `0x00022000` from ROM word `0x0805A608`; no owned game-palette
backing is established for it. If the palette frame remains zero after reset,
that word supplies the transfer source. Readable adjacent
ROM data does not establish a longer resource table. IDs at most 31 avoid this
state indexing, but still need valid resources, direction, object/palette
capacity and lifetimes; in-range state backing alone does not prove success.

## Current scene-request frontier, 24 October 2026

The retained 74 direct call sites to `resource_submit_scene` now have 72 sites
covered by 49 current C owners. Entry acceptance at `0x219CC` owns two existing
kind-15 sites; quantity acceptance adds the kind-15 site at `0x21B86`. The two
remaining sites are both in `0x42964`: `0x429E4` passes literal kind 23 and
`0x42B22` passes kind 1. The 46 recorded default-wrapper entry records are all
covered by 43 distinct owners; interior records account for the duplicates. The former
unowned `0x23578` entry is now the 212-byte row-24 selection step, with literal
kind 11. This frontier reconciliation uses the current source and paired proof;
it adds no call-site scan, code discovery or source credit itself.

Variable-kind routes still depend on the writable primary-selection byte,
previous request kind and link-menu selector word. The
[natural request-byte trace](RUNTIME_OBSERVATIONS.md#natural-request-byte-route-23-october-2026)
connects the initialization store of 14 at `0x0300408F` to primary Start and
row 14's begin entry. It does not close all aliases, writers, saved-state
producers or the complete scene-kind population.

## Finalizer coordinate-value experiment, 24 October 2026

A real inline containment predicate taking eight cached coordinate values
recovers the native locations of all seven local words: own lower X/Y at
SP0/SP4, own upper X/Y at SP8/SP12, category at SP16, saved flags at SP20 and
previous index at SP24. The four reads of the other object's bounds retain
their source order and canonical `FrameObject` fields. No R7 binding is used.

The complete candidate is 352 bytes with 229 differences against the fixed
348-byte reference, including the four extra bytes. It still spills the other
object's upper X at SP28, expanding the local frame to 32 bytes instead of the
native 28. Other coordinate allocation and control-flow differences remain;
the region receives no C credit.

Three follow-ups also fail full comparison: four by-value coordinate pairs
produce 368 bytes / 283 differences; early-failure predicate returns produce
352 / 230; combining containment and flag-priority units produces 360 / 264.
Moving only the pure separation calculation after containment produces
352 / 241 and a 36-byte frame. It frees the other upper X into R9 during
containment, but introduces two extra copies of own upper Y at SP28/SP32.
The existing game-memory reads stay in their original order.

These initial ten experiments retain complete outputs and use the current
compiler profile. The value-unit form supplies the baseline for the later
follow-ups below; every acceptance still requires the entire original extent and
changed-source controls. These stack observations add no runtime, table-bound
or complete-source claim.

A later six-case follow-up passes one cached own lower coordinate to containment
as a `const int *` pointing to its initialized automatic subobject. The lower-Y
form produces 348 bytes / 206 differences; lower X produces 348 / 208. Both
recover the native 28-byte frame and all seven homes at SP0..SP24, with no extra
stack slot. They add no game-memory reads: all four other-object coordinates
are still captured in their original order. Passing the complete named 16-byte
local by pointer instead collapses to the earlier 340 / 285 output; passing
only the lower `FramePoint` by pointer produces 340 / 249 with a 24-byte frame
and the previous index in ordinary compiler-allocated R7.

An entry-value variant with explicit R7 bindings produces 344 / 297 but is
rejected on emitted semantics: flags come from an uninitialized stack slot and
category from the stack address. Removing only those two bindings corrects
both faults, but remains nonmatching at 344 / 288. The cached-local forms retain
the existing object/table backing, index and lifetime premises; source and
emitted-code review does not establish runtime behavior. All six remain
nonexact and add no accepted source or coverage.
