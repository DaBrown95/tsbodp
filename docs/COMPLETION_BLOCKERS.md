# Remaining reconstruction and closure work

The current gates verify **2,340 C functions / 294,136 C extent bytes**, plus
**4,060 assembly bytes**. C and assembly occupy 298,196 bytes; original slices
still supply 16,479,020 bytes of assets and unconverted code. Whole-ROM equality
is proven; complete source ownership is not. The starting baseline was
1,735 C functions / 250,064 C bytes and 500 glue bytes. The fixed 319,640 mapped
extent bytes are solely a historical comparison.

Follow this order. The [manifest](../config/build-us-eu.json) and
[inventory](../assets/rom-inventory.json) contain **148 unowned rows / 27,318
estimated bytes**. This finite worklist is not a complete code denominator.
Unverified candidates receive no credit.

| Order | Remaining code | Blocker and next evidence |
| --- | --- | --- |
| 1 | Renderer `0x080023E8` (1,400), finalizer `0x08003248` (348). | Renderer: 25 differing bytes, unresolved frame homes, no distinct supported producer; plain `register` does not change the relevant pseudos at `-O2`. Finalizer: proper-owner 340 / 285 attempt retains an upper-X spill and wrong category/flags/previous-index homes. Native upper X/Y use SP8/SP12; category/flags/previous use SP16/SP20/SP24. R7 binding overwrites a live category through the frame-pointer exception and is invalid. Require a new hypothesis using [bounded failures](BOUNDED_INVENTORY.md) and [runtime limits](RUNTIME_OBSERVATIONS.md). |
| 2 | Connected actor, attachment, save and transition workers. | Prioritize movement `0x08024720` (472 / 14), kind 66 (248), weekly `0x0802005C` (108), loader `0x0801B704` (548), settlement `0x0801BA40` (188 / 22), remover `0x080454DC` (192), variant selector (72), generic EC consumer and palette worker (400). Resolve twelve bytes at `0x1DB20..0x1DB2C` and unrooted entries. Backing, selector, serialized-index, writable-target and later-writer domains remain open; generic EC delivery and unused formals are provisional. The six single-window, horizontal/vertical slots 6–9 and three rectangle bodies are owned. Of 28 bodies in the observed prefixes, only first-slot-10 `0x08038B90` (228 bytes) remains unowned. Its best candidate remains 228 / 8. The latest emits 228 / 109: its initial constant and shared-step expression match, but coordinate/window homes and the DISPCNT reload remain wrong. Further trials await a distinct supported cause. The frame-loop [window coordinate updater](DISPLAY_WINDOW_MOTION.md) and its driver now match, as do the layer/mask services; the separate `0x48A14` setter remains 68 / 15 with its four-scalar declaration. Selector, table, writer and backing populations remain open. See [actor state](ACTOR_STATE_RECONSTRUCTION.md), [entries](ACTOR_ENTRIES_RECONSTRUCTION.md), [attachments](FRAME_ATTACHMENT_JOBS_42_94.md), [save](SAVE_STREAM.md) and [transitions](TRANSITION_WINDOWS.md). |
| 3 | Copied-RAM resources: ROM `0xB840` (284), `0xB36C` (504-byte ARM body), `0xB564` (320), word-group copier (68). | Sorter remains 284 / 2 after R3-sum, Y-first and scheduler tests. The tile decoder now emits 504 / 11 against the fixed 504-byte ARM body at RAM `0x030036D0`; its 528-byte copy also includes 24 bytes of the next body. Genuine return/field lifetimes, distance association, the APPEND wrapper and four separate tail calculations are resolved in the private candidate. The four copy-entry and repeat-entry order groups now match through real zero-pair guards and ordinary tail values. Only the parser CMP/distance rotation remains. Integer predicate/discriminator capture fails; no C or API credit is assigned. Aggregate/by-reference drawer attempts remain 348 / 313 and 356 / 321: optimization recreates pointer equivalence and spills. Preserve API contracts; prove RAM execution addresses and copy prefixes separately. Serialized selection, alignment and arena/backing remain open; the 812-byte assembly decoder leaves C workers open. See [RAM map](../config/ram-map-us-eu.json) and [decoder](RESOURCE_BACKGROUND_DECODER.md). |
| 4 | Audio `0x08049968` (124), saved-register adapters and executable patches. | Explain native NOP versus ordinary C store; close caller/stack protocols, incoming transfers, patcher inputs, IRQ targets and later writes. Rebuild every reachable modified code state. Glue and observed shifts do not close those domains. See [audio](AUDIO_RECONSTRUCTION.md). |
| 5 | Serial IRQ `0x0803DC48` (1,616), poll (408), status (124), record provider (200). | IRQ remains 1,612 after its record-union repair. The 596-byte offer refresh now matches using the real next-record address at the loop bound. A direct union-index copy still leaves the record provider at 200 / 159; a late genuine R3 slot-address binding leaves IRQ at 1,612 unchanged because COMBINE folds it back into the shared base. Participant/index, resource, allocation, descriptor and writer domains remain open. See [scene](SCENE_LINK_ENTRY.md) and [serial](SERIAL_HANDSHAKE.md). |
| 6 | Executable inventory alongside rows 1–5. | Resolve 98 call-site plus 21 transfer observations at 112 physical sites, writable callbacks/jump tables and ten code installations (19,188 distinct ROM source bytes). Close the selector domains behind 6,699 unbacked serialized outcomes. Pending-display's 128 selected returns/controls/replays leave writer/index/target populations open, as do collision/audio writer and alias domains. Weak word `0xE40A40` naming `0x0803E8AF` remains unclassified incoming evidence. See [inventory](WHOLE_ROM_INVENTORY.md). |
| 7 | Reproducibility and publication. | Remove executable instruction bodies from original-ROM slices, resolve material inventory uncertainty and justify assembly exceptions. Reproduce a clean build with pinned tools/local inputs. Pass matching/controls, applicable tool tests, inventory and progress gates; audit contents/history, publish to `main` and keep contribution features disabled. |

The [relation-grid refresh and getters](SCENE_RELATION_GRID.md) own 144 C
extent bytes; their two callers remain exact. Its relation display owns another
160 bytes with a consistent full-word percentage-provider contract. The
[offer refresh](SCENE_LINK_ENTRY.md) owns 596 bytes with its canonical 24-byte
record owner. The [activity-zero initializer](SCENE_CONTACT_ACTIVITY_ZERO.md)
owns 452 bytes using the existing item, player, option and collision owners;
its movement worker remains unconverted. These six source additions cover
1,352 bytes: 1,170 instruction, 172 literal and ten alignment bytes.
The former weak entry at `0x0800480E`
lies inside the matching refresh extent and receives no separate credit.
Sixteen previously unmapped trailing pool bytes are now owned; this is not
newly discovered executable code.

The thirteen [independently bounded attachment checks](UNROOTED_ATTACHMENT_CHECKS.md)
now own their complete extents; their incoming roots remain open.
The seven [optional-route callbacks and workers](OPTIONAL_ROUTES_12_23_60.md)
also match. Their shared sound field preserves the canonical owner layout;
the unrooted neighboring word at `0x1A44C..0x1A450` remains an inventory question.

Executable inventory remains incomplete. It separates instructions, data and
unresolved bytes; its instruction union is not complete. Unclassified owned/envelope bytes,
authored NOPs and audio NOP tails need closure. Data roles cannot suppress execution or alternate entries. The
initial EWRAM image has no established executable entry; later writes remain
possible. Finite observations do not close populations.

Keep one current paired proof and controls, unique attempts and bounded useful
failures. Retire obsolete payloads under the existing
[retention policy](LOCAL_OUTPUT_RETENTION.md); measure allocation and stay below
5 GB. Hashes do not require permanent payloads. Leave backups/unrelated files alone.
