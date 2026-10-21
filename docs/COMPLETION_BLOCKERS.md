# Remaining reconstruction and closure work

The current gates verify **2,410 C functions / 300,820 C extent bytes**, plus
**4,060 assembly bytes**. C and assembly occupy 304,880 bytes; original slices
still supply 16,472,336 bytes of assets and unconverted code. Whole-ROM equality
is proven; complete source ownership is not. The 20 October goal baseline was
2,334 C functions / 292,784 C bytes and 4,060 assembly bytes. The fixed 319,640 mapped
extent bytes are solely a historical comparison.

Follow this order. The [manifest](../config/build-us-eu.json) and
[inventory](../assets/rom-inventory.json) contain **85 unowned rows / 20,712
estimated bytes**. This finite worklist is not a complete code denominator.
Unverified candidates receive no credit.

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

The latest [activity callbacks and unrooted neighbour](FRAME_ATTACHMENT_JOBS_42_94.md#activity-descriptor-callbacks-and-unrooted-neighbour)
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

Keep one current paired proof and controls, unique attempts and bounded useful
failures. Retire obsolete payloads under the existing
[retention policy](LOCAL_OUTPUT_RETENTION.md), keep the project below 5 GB and
leave backups and unrelated files alone.
