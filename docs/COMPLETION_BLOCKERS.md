# Remaining reconstruction and closure work

The current gates verify **2,433 C functions / 302,092 C extent bytes**, plus
**4,060 assembly bytes**. C and assembly occupy 306,152 bytes; original slices
still supply 16,471,064 bytes of assets and unconverted code. Whole-ROM equality
is proven; complete source ownership is not. The 20 October goal baseline was
2,334 C functions / 292,784 C bytes and 4,060 assembly bytes. The fixed 319,640 mapped
extent bytes are solely a historical comparison.

Follow this order. The [manifest](../config/build-us-eu.json) and
[inventory](../assets/rom-inventory.json) contain **65 unowned rows / 19,508
estimated bytes**. This finite worklist is not a complete code denominator.
Unverified candidates receive no credit.

The latest hard-target work adds no C coverage. Activity-three preparation now
has measured phase lifetimes and eligibility storage, conditional
table/retry bounds and a coordinate-feasibility proof; frame/value homes and
complete input writers remain open. See [its current findings](SCENE_CONTACT_ACTIVITY_THREE.md#preparation-worker-current-causes-and-input-bounds).
The selected-tile worker has a current private owner/word-read diagnostic but
still fails full comparison; see [the map path](FRAME_INPUT.md).
The explicit 128-slot object pool bounds the renderer table only under intact
membership and traversal premises. A saved auxiliary pointer can already name
a child returned to the free list; see [the callback limits](BOUNDED_INVENTORY.md#conditional-renderer-table-bound-21-october-2026).

| Order | Remaining code | Blocker and next evidence |
| --- | --- | --- |
| 1 | Renderer `0x080023E8` (1,400), finalizer `0x08003248` (348). | Renderer: 25 differing bytes, unresolved frame homes, no distinct supported producer; plain `register` does not change the relevant pseudos at `-O2`. Actual provider/caller audits identify no hidden aggregate-result temporary or interface mismatch. Finalizer: proper-owner 340 / 285 attempt retains an upper-X spill and wrong category/flags/previous-index homes. Native upper X/Y use SP8/SP12; category/flags/previous use SP16/SP20/SP24. R7 binding overwrites a live category through the frame-pointer exception and is invalid. Require a new hypothesis using [bounded failures](BOUNDED_INVENTORY.md) and [runtime limits](RUNTIME_OBSERVATIONS.md). |
| 2 | Connected actor, attachment, save and transition workers. | Prioritize the activity-six primary update (728), weekly `0x0802005C` (108), loader `0x0801B704` (548), settlement `0x0801BA40` (188 / 22), remover `0x080454DC` (192), generic EC consumer and palette worker (400). Resolve twelve bytes at `0x1DB20..0x1DB2C` and unrooted entries. Backing, selector, serialized-index, writable-target and later-writer domains remain open; generic EC delivery and unused formals are provisional. The six single-window, horizontal/vertical slots 6–9 and three rectangle bodies are owned. Of 28 bodies in the observed prefixes, only first-slot-10 `0x08038B90` (228 bytes) remains unowned. Its best candidate remains 228 / 8. The latest emits 228 / 109: its initial constant and shared-step expression match, but coordinate/window homes and the DISPCNT reload remain wrong. Further trials await a distinct supported cause. The frame-loop [window coordinate updater](DISPLAY_WINDOW_MOTION.md) and its driver now match, as do the layer/mask services; the separate `0x48A14` setter remains 68 / 15 with its four-scalar declaration. Selector, table, writer and backing populations remain open. See [actor state](ACTOR_STATE_RECONSTRUCTION.md), [entries](ACTOR_ENTRIES_RECONSTRUCTION.md), [attachments](FRAME_ATTACHMENT_JOBS_42_94.md), [save](SAVE_STREAM.md) and [transitions](TRANSITION_WINDOWS.md). |
| 3 | Copied-RAM resources: ROM `0xB840` (284), `0xB36C` (504-byte ARM body), `0xB564` (320), word-group copier (68). | Sorter retains a 284 / 2 best candidate. Its actual final-pass return yields 288 / 33. A real sum bound to R0 yields 284 / 8 by also moving the preceding priority; the native R3 sum binding yields 284 / 28 after earlier scheduling. These measured return and binding lines are closed. The tile decoder now emits 504 / 11 against the fixed 504-byte ARM body at RAM `0x030036D0`; its 528-byte copy also includes 24 bytes of the next body. Genuine return/field lifetimes, distance association, the APPEND wrapper and four separate tail calculations are resolved in the private candidate. The four copy-entry and repeat-entry order groups now match through real zero-pair guards and ordinary tail values. Only the parser CMP/distance rotation remains. Integer predicate/discriminator capture fails; no C or API credit is assigned. Aggregate/by-reference drawer attempts remain 348 / 313 and 356 / 321: optimization recreates pointer equivalence and spills. Preserve API contracts; prove RAM execution addresses and copy prefixes separately. Serialized selection, alignment and arena/backing remain open; the 812-byte assembly decoder leaves C workers open. See [RAM map](../config/ram-map-us-eu.json) and [decoder](RESOURCE_BACKGROUND_DECODER.md). |
| 4 | Audio `0x08049968` (124), saved-register adapters and executable patches. | The pinned GCC 3.0.2 and assembler path leaves the C store intact; its optimized output, alignment, fixups and veneers do not explain the reachable native NOP. Known startup copies and code writers are disjoint from this site. Original source/build or later-writer evidence is still required; close caller/stack protocols, incoming transfers, patcher inputs and IRQ targets. Rebuild every reachable modified code state. Glue and observed shifts do not close those domains. See [audio](AUDIO_RECONSTRUCTION.md). |
| 5 | Serial IRQ `0x0803DC48` (1,616), poll (408), status (124), record provider (200). | IRQ remains unowned. The latest six-global-slot composition is 1,632 bytes / 1,498 differences. All six fast signed loads and protected incoming-flags, SEND and late-R3 phases work, but new high-register saves and host/retry tail sharing remain. The native E226 shared join is already present; this composition line is closed. Preserve the 1,624 / 809 causal baseline; further trials require a distinct supported producer. The 596-byte offer refresh matches. The provider remains 200 / 159. Participant/index, resource, allocation, descriptor and writer domains remain open. See [scene](SCENE_LINK_ENTRY.md) and [serial](SERIAL_HANDSHAKE.md). |
| 6 | Executable inventory alongside rows 1–5. | Resolve 98 call-site plus 21 transfer observations at 112 physical sites, writable callbacks/jump tables and ten code installations (19,188 distinct ROM source bytes). Close the selector domains behind 6,699 unbacked serialized outcomes. Pending-display's 128 selected returns/controls/replays leave writer/index/target populations open, as do collision/audio writer and alias domains. Word `0xE40A40` naming `0x0803E8AF` has a source-backed compressed-map data role; other aliases and alternate incoming execution remain open. See [inventory](WHOLE_ROM_INVENTORY.md). |
| 7 | Reproducibility and publication. | Remove executable instruction bodies from original-ROM slices, resolve material inventory uncertainty and justify assembly exceptions. Reproduce a clean build with pinned tools/local inputs. Pass matching/controls, applicable tool tests, inventory and progress gates; audit contents/history, publish to `main` and keep contribution features disabled. |


Other active dependencies include the [relation-grid delta](SCENE_RELATION_GRID.md)
at `0x40AB4` (692 bytes), [activity-three parent and raster workers](SCENE_CONTACT_ACTIVITY_THREE.md)
and the [record-selection text renderer](SCENE_RECORD_SELECTION_HANDOFFS.md) at
`0x1AA78`. Their local source gains leave these workers unconverted.

The [installed serial-slot callback](SCENE_CONTACT_MENU.md#installed-serial-slot-callback)
adds four C extent bytes: two existing candidate bytes now qualified as
instructions and two newly mapped zero-alignment bytes. The raw and qualified
instruction census each gain two bytes; no new instruction extent is mapped. All fourteen C functions / 2,072 bytes at
`0x1C9B8..0x1D1D0` are source-owned. The actual installer and driver establish
its object-pointer callback route; wider writers, live objects, asynchronous
IRQ/protocol inputs and gameplay remain conditional. Six alignment annotations
now identify twelve source-owned bytes as data, including ten already owned
before this callback; they add no separate C or instruction credit.

The [activity callbacks and unrooted neighbour](FRAME_ATTACHMENT_JOBS_42_94.md#activity-descriptor-callbacks-and-unrooted-neighbour)
add four C functions / 180 extent bytes: 36 instruction, four literal, 136
switch-table and four alignment bytes. All seven nonnull targets shared by
observed rows 5–7 are source-owned (664 bytes), within twelve contiguous C
functions / 1,888 bytes at `0x432CC..0x43A2C`. Three old rows covered 172
estimated bytes. The separate unrooted return-100 leaf adds four newly identified
instruction bytes; the other four newly mapped bytes are alignment. Its incoming
roots and historical unused formals remain open. Generic EC delivery and the
wider selector, writer, backing and gameplay populations remain unresolved.

All seven nonnull [row-two descriptor targets](FRAME_ATTACHMENT_JOBS_42_94.md#row-two-descriptor-callbacks)
are also source-owned (628 bytes), within eight contiguous C functions / 728
bytes at `0x28738..0x28A10`. Its `0x28424` child remains original. The faithful
private candidate is 788 / 42, with differences confined to R5/R6 instruction
fields. The required pending-update operation increases the owner reference
count from 15 to 16, crossing the allocator's priority threshold and reversing
owner/job homes. Removing the operation would be incorrect. Further trials
need a distinct actual source, lifetime, interface or build fact.

The [controlled installed tile-decoder fixture](RUNTIME_OBSERVATIONS.md#controlled-installed-tile-decoder-fixture)
confirms the original parser order and 128-byte VRAM output for the fixed
phase-25 sprite input, with controls and replay. The suspended-event context
leaves broader writers open. The row-six map selections choose only codec-six
chunks; repeating that search or the unchanged frame-one fixture adds no new
evidence. The copied tile parser's source mismatch remains.

Four unconverted extents include their bounded trailing alignment: `0x219CC`
(176), `0x3B75C` (356), `0x3F908` (1,112) and `0x42964` (656). These eight data
bytes add no C or instruction credit. The last two retain four and eight
unclassified internal bytes respectively.

Executable inventory remains incomplete. Its instruction union is not a full
code denominator. Unclassified owned/envelope bytes, authored NOPs and audio
NOP tails need closure; data roles cannot suppress alternate execution. The
initial EWRAM image has no established executable entry, and later writes remain
possible. Finite observations do not close populations. Completed local source
paths and their conditional domains are recorded in the linked owner documents;
whole-ROM equality does not establish complete source ownership or gameplay.

Five further alignment annotations classify ten already source-owned bytes as
data. Matching emitted directives, object and linked data symbols, and native
branches or returns establish these roles. Owned unclassified bytes now total
34: fifteen authored NOPs and two audio tails remain explicit. C, instruction,
mapped extent and unfinished-source counts do not change; alternate entry and
complete executable inventory remain open.


Eight ordinary C helpers add 404 extent bytes: two background-buffer operations,
four view-position/dimensions helpers and two unrooted interaction bodies. Seven
existing rows account for 376 bytes of the backlog reduction. The separate
`0xEA68` getter adds 28 newly mapped bytes: 22 instructions, four literal and two
alignment bytes. Across all eight bodies, 372 instruction bytes are newly
qualified; 350 were already inside estimated mapped extents. Full extents,
normal/strict checks and genuine source controls pass. Incoming callers, unused
formals, valid input/backing populations and gameplay remain provisional. See
[backgrounds](DISPLAY_MAP_RECONSTRUCTION.md#independently-bounded-background-buffer-lifetime),
[views](VIEW_EFFECTS_RECONSTRUCTION.md#additional-position-and-dimensions-helpers)
and [interactions](FRAME_COLLISION_RESPONSE.md#nearby-unrooted-interaction-bodies).

Keep one current paired proof and controls, unique attempts and bounded useful
failures. Retire obsolete payloads under the existing
[retention policy](LOCAL_OUTPUT_RETENTION.md), keep the project below 5 GB and
leave backups and unrelated files alone.

Three independently bounded source bodies add 356 C extent bytes: the
[collider-overlap predicate](FRAME_COLLISION_RESPONSE.md#unrooted-collider-overlap-predicate),
[two-object stop/timer](ACTOR_STATE_RECONSTRUCTION.md#independently-bounded-two-object-stop-and-timer)
and [display flags query](DISPLAY_MAP_RECONSTRUCTION.md#independently-bounded-display-control-flags-query).
Their normal/strict matches and genuine controls preserve the existing owners
and provider contexts. The former three rows totalled 344 estimated bytes;
twelve newly mapped bytes comprise two instruction bytes, four literal bytes
and six alignment bytes. The possible `0xE1EE` interior entry is covered by the
full `0xE1EC` source. Its sole pointer-looking word has a
[bounded palette data use](WHOLE_ROM_INVENTORY.md#palette-word-resembling-an-interior-entry),
but an executable consumer and prepared-R1 contract remain unresolved in the
unchanged manifest metadata. Its disappearing weak row is physical coverage,
not an incoming-contract resolution. The known backlog is still not a complete
code denominator; these source additions establish no gameplay or interior-entry
execution.


Five independently bounded helpers add 300 C extent bytes: the
[pending-flag clearer](SEARCH_COST_AND_DAILY_CLOCK.md#independently-bounded-pending-flag-clearer),
[panel-mode selector](SCENE_CATALOG.md#independently-bounded-panel-mode-selector)
and [three VBlank-status helpers](DISPLAY_MAP_RECONSTRUCTION.md#independently-bounded-vblank-status-polling).
They replace five existing rows of the same total extent: 230 instruction,
64 literal/switch-table and six alignment bytes. Full normal/strict comparisons,
genuine source controls and actual interface/dependency checks pass. Incoming
roots and broader input, backing, writer and gameplay domains remain open;
no mapped extent is added. The separate unrooted stepped scene-object creator
at `0x28234` remains original: its first faithful candidate is 168 / 116 against
160 native bytes. The compiler reduces both coordinate products where native
reduces only X; no actual Y reload, escape or provider dependency supports a
further trial. The main dependency-ordered blockers above remain unresolved.


The [additional text helpers](DISPLAY_TEXT_RECONSTRUCTION.md#additional-unrooted-text-helpers)
add three C bodies / 60 extent bytes. One existing 36-byte row is replaced;
two unrooted leaves add 24 newly mapped bytes: twelve instruction, eight literal
and four alignment bytes. All three incoming-use populations remain open.
The same work repairs the text-field owner: decoded resource `0x25` contains
`@1`, whose raw selector addresses field zero directly. The old `0x03000E20`
"bank" is a biased constant for the canonical `0x03001A60` bank. Five existing
reader contexts retain 1,016 identical bytes using integer selector subtraction
before indexing. Broader selector, backing, recursion and writer domains remain
conditional. See the [shared-bank evidence](DISPLAY_TEXT_RECONSTRUCTION.md#staging-fields-and-expansion-consumers).

Finalizer source still has two one-definition, compare-only upper-X loads that
LOOP can pair and hoist. An actual additional definition, spanning consumer or
dependency is needed to defeat that measured eligibility; adding one solely
to force storage would not be supported. The serial R8/SEND/event audit supplies
no missing consumer, and the drawer's captured equivalent addresses remain
unchanged by the inspected writers. The text row reader's current calibration
reproduces 140 / 80: R8 is preserved, while the incoming tile pointer receives
a four-byte spill frame. No source variant or shared compiler-switch explanation
follows from those findings.


The [unrooted transient/view coordinator](SCENE_REQUEST_HANDOFF.md#unrooted-transient-and-view-coordinator)
at `0x27DF0` adds one ordinary C body / 48 extent bytes: 44 instruction bytes and
four literal bytes. It steps transient effects, then passes each byte index to
the existing view updater, reloading the shared count after every call. It
replaces one estimated row without adding mapped extent; incoming roots and
complete count/backing/writer domains remain open.

The canonical glyph-renderer diagnostic retains the actual word buffer,
font/state types and provider interfaces. It reproduces 684 / 559; argument
values survive earlier passes, and GREG/reload assigns the differing stack
homes. A native-sized frame alone does not resolve that mismatch. The window
setter consumes all four coordinate inputs; its actual caller discards the result. The
inspected collection-count writer chains do not establish an IRQ alias that
would justify volatile reads in the held removal helper. These findings add
no source credit or gameplay evidence.

The [unrooted point-equality helper](VIEW_EFFECTS_RECONSTRUCTION.md#independently-bounded-point-equality-helper)
and [direction-step helper](VIEW_EFFECTS_RECONSTRUCTION.md#independently-bounded-direction-step-helper)
at `0x273FC` and `0x274E4` add two ordinary C bodies / 100 extent bytes:
98 instruction bytes and two linker zero-alignment bytes. They compare the
canonical two-word points and select/store a signed-byte direction step with
the native byte-wrap cases. Two existing rows / 98 estimated bytes are
replaced; only the two alignment bytes are newly mapped. Incoming callers,
original typedefs and complete input/backing populations remain open. This
local gain leaves the priority blockers above unresolved.
