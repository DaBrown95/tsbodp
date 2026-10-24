# Remaining reconstruction and closure work

The current gates verify **2,459 C functions / 306,648 C extent bytes**, plus
**4,060 assembly bytes**. C and assembly occupy 310,708 bytes; original slices
still supply 16,466,508 bytes of assets and unconverted code. Whole-ROM equality
is proven; complete source ownership is not. The 20 October goal baseline was
2,334 C functions / 292,784 C bytes and 4,060 assembly bytes. The fixed 319,640 mapped
extent bytes are solely a historical comparison.

Follow this order. The [manifest](../config/build-us-eu.json) and
[inventory](../assets/rom-inventory.json) contain **40 unowned rows / 14,970
estimated bytes**. This finite worklist is not a complete code denominator.
Unverified candidates receive no credit.

The [actor scene-counter settlement](FRAME_ATTACHMENT_JOBS_42_94.md#actor-scene-counter-settlement)
now owns 188 further C bytes, including 146 instruction bytes, 40 literal bytes
and two zero alignment bytes. Real input and arithmetic-result lifetimes recover
the native registers; unsigned subtraction defines the insufficient-value path
for every signed input. The canonical counter child preserves all neighboring
fields, and seven updated consumers retain 700 matching bytes. The two actual
callers and pinned-compiler layout are qualified. This removes one existing
188-byte estimate; input, writer and runtime populations remain open.

Three connected choice providers now own 44 further C bytes: the 28-byte
optional-choice check at `0x4432C` and independent eight-byte preparation
bodies at `0x25998` and `0x44C10`. Their equal-result kind switches preserve
the native saved-register/return-address shapes until late jump optimization.
The 41/45, 49 and 82..86 cases are grounded in adjacent selectors/dispatchers;
historical case intent, unused formals and incoming unrooted callers remain
inferred. Normal/strict comparisons, genuine controls and actual definition
interfaces pass. These source gains do not close runtime or inventory domains.

The [connection-start provider](SERIAL_HANDSHAKE.md#connection-start-provider)
now owns its full 100-byte C extent: 82 instruction, 16 literal and two zero
alignment bytes. The canonical eight-byte payload union has an active word
member for its initialized low word; the remaining four representation bytes
are unspecified and unconsumed by event kinds one and two. Its actual handshake
caller and provider interfaces are qualified. This closes one existing
98-byte estimate and classifies two adjacent alignment bytes, without a new
entry or instruction observation. Protocol and wider writer domains stay open.

Four existing choice-clock owners retain all 524 matching bytes after a
source-validity repair: a real clock child, canonical comparison input and
integer address calculation replace incompatible partial storage accesses.
This adds no coverage. The initializer remains unconverted at 168 bytes with
six scheduling differences; private failures receive no source credit.

The [text-sizing routine](DISPLAY_TEXT_RECONSTRUCTION.md#text-object-sizing)
now owns 140 further C bytes, including two zero alignment bytes. Signed
division preserves the native value handoffs and narrowing operations. Its
canonical frame-object payload also repairs the actual text-update caller
and four shared-slot readers without changing their 1,028 matching bytes.
Normal/strict comparisons, genuine controls and actual interfaces pass;
font, string, pool and writer domains remain conditional.

The latest activity-three preparation work adds no C coverage. It now
has measured phase lifetimes and eligibility storage, conditional
table/retry bounds and a coordinate-feasibility proof. Preserving all three
native high-register values still leaves a 536-byte / 492-difference attempt;
frame/value homes and
complete input writers remain open. See [its current findings](SCENE_CONTACT_ACTIVITY_THREE.md#preparation-worker-current-causes-and-input-bounds).
The selected-tile worker has a current private owner/word-read diagnostic but
still fails full comparison; see [the map path](FRAME_INPUT.md).
Both row-six initial maps fit initialized combined data in the calibrated
decoder model. Eight actual animation payloads and their program activation
chain have conditional source/destination bounds; view/actor completion, wider
writer populations and live backing remain open. See [the writer boundary](FRAME_MAP_ANIMATION.md#row-six-writer-domain).
The fixed extra collision-type stream now has a complete 56-byte emulator-service
decode and independent parser comparison. All 26 entries compose to initialized
patterns 143..160 under the existing loading and eight-payload premises; live
DMA, activation, aliases and later writers remain open.
The explicit 128-slot object pool bounds the renderer table only under intact
membership and traversal premises. A saved auxiliary pointer can already name
a child returned to the free list; see [the callback limits](BOUNDED_INVENTORY.md#conditional-renderer-table-bound-21-october-2026).
The separate actor-state allocation supplies a necessary bound of 32..41
for saved IDs above 31. ID 54 exceeds that backing before its
potential presence-bank alias write; this is not a native rejection guard.

| Order | Remaining code | Blocker and next evidence |
| --- | --- | --- |
| 1 | Renderer `0x080023E8` (1,400), finalizer `0x08003248` (348). | Renderer: 25 differing bytes, unresolved frame homes, no distinct supported producer; plain `register` does not change the relevant pseudos at `-O2`. Actual provider/caller audits identify no hidden aggregate-result temporary or interface mismatch. Finalizer: proper-owner 340 / 285 attempt retains an upper-X spill and wrong category/flags/previous-index homes. Native upper X/Y use SP8/SP12; category/flags/previous use SP16/SP20/SP24. R7 binding overwrites a live category through the frame-pointer exception and is invalid. Require a new hypothesis using [bounded failures](BOUNDED_INVENTORY.md) and [runtime limits](RUNTIME_OBSERVATIONS.md). |
| 2 | Connected actor, attachment, save and transition workers. | Prioritize weekly `0x0802005C` (108), loader `0x0801B704` (548), generic EC consumer and palette worker (400). Resolve twelve bytes at `0x1DB20..0x1DB2C` and unrooted entries. Backing, selector, serialized-index, writable-target and later-writer domains remain open; generic EC delivery and unused formals are provisional. The six single-window, horizontal/vertical slots 6–9 and three rectangle bodies are owned. Of 28 bodies in the observed prefixes, only first-slot-10 `0x08038B90` (228 bytes) remains unowned. Its best candidate remains 228 / 8. A shared-step composition emits 228 / 109: its initial constant and shared-step expression match, but coordinate/window homes and the DISPCNT reload remain wrong. Further trials await a distinct supported cause. The frame-loop [window coordinate updater](DISPLAY_WINDOW_MOTION.md) and its driver now match, as do the layer/mask services; the separate `0x48A14` setter remains 68 / 15 with its four-scalar declaration. Selector, table, writer and backing populations remain open. See [actor state](ACTOR_STATE_RECONSTRUCTION.md), [entries](ACTOR_ENTRIES_RECONSTRUCTION.md), [attachments](FRAME_ATTACHMENT_JOBS_42_94.md), [save](SAVE_STREAM.md) and [transitions](TRANSITION_WINDOWS.md). |
| 3 | Copied-RAM resources: ROM `0xB840` (284), `0xB564` (320). | Sorter retains a 284 / 2 best candidate. Its actual final-pass return yields 288 / 33. A real sum bound to R0 yields 284 / 8 by also moving the preceding priority; the native R3 sum binding yields 284 / 28 after earlier scheduling. These measured return and binding lines are closed. The word-group copier at `0x0800B018` now owns all 68 bytes from C, with normal/strict matches and genuine changed-source controls; its actual selected displacement and final payload extent share one ordinary scalar. The tile decoder now owns its complete 504-byte ARM body from C; its 528-byte installation also copies 24 bytes of the following unconverted map drawer. Aggregate/by-reference drawer attempts remain 348 / 313 and 356 / 321: optimization recreates pointer equivalence and spills. Preserve API contracts; prove RAM execution addresses and copy prefixes separately. Serialized selection, alignment and arena/backing remain open; the 812-byte assembly decoder leaves C workers open. See [RAM map](../config/ram-map-us-eu.json) and [decoder](RESOURCE_BACKGROUND_DECODER.md). |
| 4 | Audio `0x08049968` (124), saved-register adapters and executable patches. | The pinned GCC 3.0.2 and assembler path leaves the C store intact; its optimized output, alignment, fixups and veneers do not explain the reachable native NOP. Known startup copies and code writers are disjoint from this site. Original source/build or later-writer evidence is still required; close caller/stack protocols, incoming transfers, patcher inputs and IRQ targets. Rebuild every reachable modified code state. Glue and observed shifts do not close those domains. See [audio](AUDIO_RECONSTRUCTION.md). |
| 5 | Serial IRQ `0x0803DC48` (1,616), status (124), record provider (200). | IRQ remains unowned. The six-global-slot composition is 1,632 / 1,498; a later canonical-owner relaxation is 1,604 / 1,456. The latter naturally allocates its main owner to IP but retains a duplicate R8 carrier and loses the late R3 handoff at COMBINE. Repeated constant-equivalence priority penalties are measured; they supply no missing consumer. A six-handoff proposal was stopped before compilation at the R7 byte-address rule. Preserve the 1,624 / 809 causal baseline; further work needs a distinct source hypothesis rather than another register permutation. The 408-byte transfer-completion poll and 596-byte offer refresh match. The provider remains 200 / 159. Participant/index, resource, allocation, descriptor and writer domains remain open. See [scene](SCENE_LINK_ENTRY.md) and [serial](SERIAL_HANDSHAKE.md). |
| 6 | Executable inventory alongside rows 1–5. | Resolve 98 call-site plus 21 transfer observations at 112 physical sites, writable callbacks/jump tables and ten code installations (19,188 distinct ROM source bytes). Close the selector domains behind 6,699 unbacked serialized outcomes. Pending-display's 128 selected returns leave populations open. A separate [controlled insertion](RUNTIME_OBSERVATIONS.md#controlled-pending-row-copy-and-consumption) now proves a native shift corrupts the default callback to `0x04708108`, which the consumer loads before the fixture stops its indirect call. This is malformed data, without a natural insertion caller or hardware IRQ-delivery claim. Collision/audio writers and aliases remain open. Word `0xE40A40` naming `0x0803E8AF` has a source-backed compressed-map data role; other aliases and alternate incoming execution remain open. See [inventory](WHOLE_ROM_INVENTORY.md). |
| 7 | Reproducibility and publication. | Remove executable instruction bodies from original-ROM slices, resolve material inventory uncertainty and justify assembly exceptions. Reproduce a clean build with pinned tools/local inputs. Pass matching/controls, applicable tool tests, inventory and progress gates; audit contents/history, publish to `main` and keep contribution features disabled. |


Other active dependencies include the [relation-grid delta](SCENE_RELATION_GRID.md)
at `0x40AB4` (692 bytes), [activity-three parent and raster workers](SCENE_CONTACT_ACTIVITY_THREE.md)
and the [record-selection text renderer](SCENE_RECORD_SELECTION_HANDOFFS.md) at
`0x1AA78`. Their local source gains leave these workers unconverted.

The linked-catalog builder at `0x21658` now matches all 356 bytes, including
its three literal pools. The canonical 162-record backing and existing common
scene-owner array make its descending cursors defined under the prepared
pointer/backing premises. Actual native register phases preserve the entry,
owner, table and short address/kind lifetimes. The entry-acceptance handler
now owns 176 C bytes: 162 instruction bytes, twelve literal bytes and two
alignment bytes. Its canonical capacity byte at offset one supplies a short
R0 guard and the actual R6 loop-bound phase; its context-to-record byte cursor
remains ordinary. The [quantity-acceptance handler](SCENE_LINK_CATALOG.md#quantity-acceptance)
at `0x21B18` now owns 132 C bytes: 124 instruction bytes and eight literal bytes,
with no alignment tail. Its short IP entry base, guarded R8 exclusion index and
persistent R4 mask preserve actual consumed phases without an R7 exception.
See the [entry evidence](SCENE_LINK_CATALOG.md#entry-acceptance).
A restored collection record can construct kind 33/34 with
enabled one, but its returned object is discarded by the restore loop and no
catalog owner-slot publication follows from primary-list retention. Natural
record producers, valid existing owners, later writers and runtime populations
remain open. See the [builder evidence](SCENE_LINK_CATALOG.md#builder-and-shared-array-lifetimes).

The renderer's actual current/previous-frame address producers already agree
with native code. Their spill homes remain SP60/SP56 instead of SP68/SP64;
the missing order/counter allocation cause is not a missing byte snapshot or
provider result. The finalizer's two compare-only upper-X temporaries are
matched and hoisted by LOOP. No additional native definition, escape or
consumer supports defeating that transformation. Preserve these closed source
lines until a distinct semantic or original-build fact appears. A bounded
53/64-bit precision model of 368 retained allocation rows changes nine scores
by one but changes no rank or tie. It does not identify the historical host.

The audio patcher's full master-input arithmetic has a conditional set of
1,024 completed converter images from the fixed installation, closed under
serial completed calls without other writers. This bounds stored encodings,
not valid execution or reachable game inputs; intermediate interleavings and
other writers remain open. It does not explain the master worker's native NOP.

The [kind-20 mode inputs](SCENE_CONTACT_MENU.md#conditional-mode-inputs) now have
a fixed resource population: ten factory-ten records across 24 copy occurrences
in the retained 50-root/105-pack census all supply `0..7`. Valid construction,
unchanged fields and an accepted handoff conditionally keep those modes within
the observed eight-row prefix. Reset plus preserved guarded progress writes
conditionally bound option values to `0..4`, fitting the six label halfwords;
arbitrary save imports still supply `0..15`, and other writers remain open.
The [initializer-provider bounds](SAVE_WORLD_INITIALIZATION.md#conditional-initializer-data-writes)
exclude the named condition and prepared actor-reset writes from these values;
live buffer, allocation-history and interfering-writer premises remain open.
The serial route's eight-entry mode prefix is identity, but input byte eight
and minimum packet length have no receiver guard or proven peer-producer bound.
Its local eight-label reply does not close that input population. No C or
runtime credit is added; other requests, writers and aliases remain open.

The [activity-three preparation](SCENE_CONTACT_ACTIVITY_THREE.md#preparation-worker-current-causes-and-input-bounds)
remains 536 / 492 against 544 bytes. The [shared attachment worker](FRAME_ATTACHMENT_JOBS_42_94.md#shared-optional-worker-at-0x28424)
now matches all 788 bytes, including the required pending update. Its real
case-zero owner uses R6 only during that call phase; the sample-field address
uses R4 across its five calls. Ordinary owner field accesses remain available
to common-subexpression elimination. This replaces one 786-byte estimate and
owns two following alignment bytes, without a newly discovered entry.
The [palette selection builder](SCENE_PALETTE_MENU.md#remaining-selection-transitions)
at `0x1510C` remains unconverted. Binding its real column to R5 survives every
intermediate stage, but disqualifies it from LOOP's pseudo-register induction
recognition. The resulting 176 / 163 attempt loses the native incremental X
and slot carriers. This composition is closed; another binding grid is not a
new cause.

The [glyph renderer](DISPLAY_TEXT_RECONSTRUCTION.md#bounded-historical-live-range-splitting-test)
retains 680 / 548 against 692 bytes despite its correct early cursor lifetime
and frame size. Faithful historical live-range splitting produces the predicted
splits but worsens the full result to 760 / 707. Tile, Y and color homes remain
wrong. The text row reader remains 140 / 80, with the tile pointer spilled.
No shared compiler-switch explanation follows.

A [conditional collection invariant](ACTOR_ENTRIES_RECONSTRUCTION.md#conditional-collection-partition-and-remover-bounds)
now bounds the selection remover's draws after reset and valid reserve, clear
and remove histories, with stable stage 2–4 and an unchanged nonzero count
between the empty test and record draw. A zero second read passes `-1` as the
random upper argument, without a second guard. Serialized counts still need
their own prefix bound of 160; checksum validation does not establish it. An
allowed record's existence does not prove retry termination or complete writer coverage.
The remover's 192-byte source match is a separate compiler result; this
invariant does not close writer coverage or add source credit itself.

The [point-to-cell converter](FRAME_INPUT.md) remains 116 / 121 against 128
bytes with its actual two-point work and signed-word division API. Its context
and output allocate to R5/R7 instead of native R7/R8. The inverse projector is
also unowned. Its shared provisional zero/one declaration and canonical
registration alias now agree with the native callers, including in-place
points; the existing 104-byte before-step caller retains its match. That
interface repair adds no C coverage or runtime evidence. The already-owned
216-byte copied map transfer is counted once, separately from the unconverted
320-byte first map drawer and both installation prefixes.

The [controlled tile fixture](RUNTIME_OBSERVATIONS.md#controlled-installed-tile-decoder-fixture)
confirms one original parser order and 128-byte output with controls and replay.
Both row-six maps and eight animation payloads have conditional calibrated
bounds. These finite results leave live backing, later writers, activation,
completion and executable-target populations open; repeating unchanged fixtures
adds no evidence. The selector's setup providers do not guarantee projection
success or initialize its distinct output fields.

The [fixed pattern domain](FRAME_GRID_CELLS.md#conditional-pattern-write-bounds)
now bounds each registration scan to twelve candidate and nine target slots
for the 138 backed patterns in the inspected 149-word prefix. The full byte-index
interpretation also exposes mutable and history-dependent data, so it does not
close valid kind populations or later writers. A concrete zero-coordinate
sentinel example shows why a populated candidate bank can still appear empty.
The [palette count input](SCENE_PALETTE_MENU.md#remaining-selection-transitions)
is now tied to five loaded nibbles, giving `0..15` per row under the completed-load
premises; neither row nor total capacity follows. These are static input bounds,
with no new source extent or runtime credit.

The [scene-zero selector setup](FRAME_GRID_CELLS.md#conditional-scene-zero-selector-inputs)
now has a real actor/owner pattern with successful modeled projection and three
nonzero, initially usable candidates. The actual default-clock schedule permits
that actor. Earlier registration, later occupancy, a natural scene-zero arrival
and the same-live action request remain unproved.

The separate [scene-six terrain observations](RUNTIME_OBSERVATIONS.md#natural-scene-six-terrain-redirection)
bracket two native response-three deflections with exact replay. A longer
Left approach leaves its observation band without reaching the first portal;
it proves no portal absence, later writer closure or scene-zero arrival.

The rectangle handler's new explicit scaled update preserves its producer but loses the separate signed
pack consumer already in initial intermediate output; it remains 224 / 182.
The earlier shared-step 228 / 109 composition already supplies that consumer
fork, so these findings do not authorize repeating its type or binding grid.

The [request frontier](BOUNDED_INVENTORY.md#current-scene-request-frontier-24-october-2026)
is reconciled against current ownership: 72 of 74 direct submission sites and
all 46 recorded default-wrapper entry records are covered. A bounded natural
new-game route follows the initialization store of kind 14 through primary
Start to row 14's begin entry, with cold replay and displaced-watch control.
This closes that selected reachable-input question; complete kind writers,
aliases, saved-state producers and target populations remain open. Source and
map totals are unchanged by that route observation.

The [opening](DISPLAY_WINDOW_MOTION.md#opening-from-center) and
[closing](DISPLAY_WINDOW_MOTION.md#closing-to-center) window helpers at
`0x48724` and `0x487BC` each own 152 C bytes using the existing two-window array
and coordinate subobjects. The opening service qualifies four existing
post-MMIO word reads through their canonical `int` members; it adds no read
or bound and proves no original qualifier, IRQ writer or runtime timing.
The rectangle setter at `0x48A14` remains original. Window lifecycle, coordinate
bounds and complete writer domains remain open.

The [unrooted detachment loop](DISPLAY_NEED_EFFECT_LIFECYCLE.md#unrooted-actor-detachment)
at `0x2F400` now owns 48 bytes from C: 46 instruction bytes and two alignment
bytes. It uses the existing three-record owner and actor-detachment provider.
An actual incoming caller and complete live-backing/writer populations remain
open. Its source-audited instruction observation adds 46 bytes to the census;
this is not a newly discovered entry or a runtime root.

The [unrooted attachment-capacity predicate](DISPLAY_NEED_EFFECT_LIFECYCLE.md#unrooted-attachment-capacity-check)
at `0x461C8` now owns 56 bytes: 54 instruction bytes and two alignment bytes.
Its existing actor and state counters retain their separate APIs and backing
premises. The source audit adds 54 instruction observations, with no new
discovered entry or established incoming/runtime root.

The [unrooted brightness ramp](TRANSITION_WINDOWS.md#unrooted-slow-brightness-ramp)
at `0x39370` owns 60 C extent bytes, comprising 52 instruction and eight literal
bytes. Its actual quotient and destination phases end before each VBlank call.
An incoming caller, historical unused formal and runtime population remain
unproved; the BIOS glue remains separately counted assembly.

The [separate choice-49 leaf](FRAME_ATTACHMENT_JOBS_42_94.md#separate-unrooted-choice-49-leaf)
at `0x25990` adds eight source-audited instruction bytes from a previously
unresolved region. It is outside the original 57-row worklist, so that backlog
does not shrink. An incoming caller and installed callback remain unproved.

The [activity-six primary update](SCENE_CONTACT_ACTIVITY_SIX.md#dispatch-and-primary-update)
now owns all 728 bytes from C: 700 instruction bytes and 28 literal-pool bytes.
Short post-AND byte results preserve the real constant/dataflow phases; the
normalized word and option pointer retain their actual consumers across calls.
Its factory installs the same-address canonical callback. This removes one
existing estimated row and adds no new entry or mapped extent.

The [tile-run decoder](RESOURCE_BACKGROUND_DECODER.md#matching-tile-decoder)
now owns 504 C bytes at ROM `0xB36C`, executing at RAM `0x030036D0`: 126 ARM
instructions, with no literal or alignment tail. Its count/distance/tail
carrier preserves the actual phases and parser order. The canonical tile
callback returns the advanced cursor, consistently declared across the provider,
headers and copy caller; the separate background API is unchanged. This removes
one existing row without adding an instruction observation, entry, mapped extent
or runtime claim. The following map drawer and the extra copied prefix remain
unconverted.

The [selection remover](ACTOR_ENTRIES_RECONSTRUCTION.md#random-selectable-record-removal)
now owns 192 C bytes at `0x454DC`: 172 instruction bytes and 20 literal bytes,
with no alignment tail. Its canonical world view shares the existing collection
pointer, and both maintained callers retain the same target address. Only the
second existing byte-count read is qualified to preserve its native load; no
access or bounds guard is added. The source match leaves collection, stage,
writer and retry-termination premises conditional and adds no runtime claim.

Three [installed constant-result EC bodies](FRAME_ATTACHMENT_JOBS_42_94.md#installed-constant-result-ec-bodies)
at `0x13360`, `0x1A590` and `0x35060` now own eight C instruction bytes each.
Their equal-result switches preserve the pinned compiler's link-register save;
normal/strict positives and changed-case-result controls cover all three slots.
The modeled formals, EC kind delivery and historical case structure remain
inferred. These matches remove three existing rows, with no new entry, mapped
extent or runtime claim. The separate unrooted constant-one entries now match
from C, with their incoming roots and historical unused formals still open.

The instruction census is not a complete code denominator. Its current raw
union is 285,376 bytes; qualified instructions occupy 285,350 bytes and
referenced data 35,932 bytes. Known data totals 22,886 bytes. Source-owned data
and alignment have 2,004 records / 4,034 bytes, with zero locally unclassified
owned bytes. Estimated envelopes still have 336 unclassified bytes, and
16,432,686 bytes remain outside resolved roles. Fifteen authored veneer NOPs
have a separate 30-byte instruction role; two audio fills are implicit code
alignment, without proof against alternate entry. The reachable `0x499B0` NOP
remains a separate source mismatch. The `0xE1EE` interior-entry-shaped value has
a palette-data use, while an executable consumer and prepared-R1 contract
remain unresolved. Material selector, writer, alias and target domains remain
completion blockers.

Completed local paths and their source gains are recorded in the linked owner
documents and publication history. Keep one current paired proof and controls,
unique attempts and bounded useful failures. Retire only verified replaced
payloads under the [retention policy](LOCAL_OUTPUT_RETENTION.md), stay below
5 GB and leave backups and unrelated files alone.
