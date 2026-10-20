# Remaining reconstruction and closure work

The current gates verify **2,356 C functions / 296,936 C extent bytes**, plus
**4,060 assembly bytes**. C and assembly occupy 300,996 bytes; original slices
still supply 16,476,220 bytes of assets and unconverted code. Whole-ROM equality
is proven; complete source ownership is not. The 20 October goal baseline was
2,334 C functions / 292,784 C bytes and 4,060 assembly bytes. The fixed 319,640 mapped
extent bytes are solely a historical comparison.

Follow this order. The [manifest](../config/build-us-eu.json) and
[inventory](../assets/rom-inventory.json) contain **132 unowned rows / 24,522
estimated bytes**. This finite worklist is not a complete code denominator.
Unverified candidates receive no credit.

| Order | Remaining code | Blocker and next evidence |
| --- | --- | --- |
| 1 | Renderer `0x080023E8` (1,400), finalizer `0x08003248` (348). | Renderer: 25 differing bytes, unresolved frame homes, no distinct supported producer; plain `register` does not change the relevant pseudos at `-O2`. Finalizer: proper-owner 340 / 285 attempt retains an upper-X spill and wrong category/flags/previous-index homes. Native upper X/Y use SP8/SP12; category/flags/previous use SP16/SP20/SP24. R7 binding overwrites a live category through the frame-pointer exception and is invalid. Require a new hypothesis using [bounded failures](BOUNDED_INVENTORY.md) and [runtime limits](RUNTIME_OBSERVATIONS.md). |
| 2 | Connected actor, attachment, save and transition workers. | Prioritize kind 66 (248), weekly `0x0802005C` (108), loader `0x0801B704` (548), settlement `0x0801BA40` (188 / 22), remover `0x080454DC` (192), generic EC consumer and palette worker (400). Resolve twelve bytes at `0x1DB20..0x1DB2C` and unrooted entries. Backing, selector, serialized-index, writable-target and later-writer domains remain open; generic EC delivery and unused formals are provisional. The six single-window, horizontal/vertical slots 6–9 and three rectangle bodies are owned. Of 28 bodies in the observed prefixes, only first-slot-10 `0x08038B90` (228 bytes) remains unowned. Its best candidate remains 228 / 8. The latest emits 228 / 109: its initial constant and shared-step expression match, but coordinate/window homes and the DISPCNT reload remain wrong. Further trials await a distinct supported cause. The frame-loop [window coordinate updater](DISPLAY_WINDOW_MOTION.md) and its driver now match, as do the layer/mask services; the separate `0x48A14` setter remains 68 / 15 with its four-scalar declaration. Selector, table, writer and backing populations remain open. See [actor state](ACTOR_STATE_RECONSTRUCTION.md), [entries](ACTOR_ENTRIES_RECONSTRUCTION.md), [attachments](FRAME_ATTACHMENT_JOBS_42_94.md), [save](SAVE_STREAM.md) and [transitions](TRANSITION_WINDOWS.md). |
| 3 | Copied-RAM resources: ROM `0xB840` (284), `0xB36C` (504-byte ARM body), `0xB564` (320), word-group copier (68). | Sorter retains a 284 / 2 best candidate. Returning its actual final pass changes register preference but leaves the two blocked operands wrong and adds a return move (288 / 33); that return experiment is closed. The tile decoder now emits 504 / 11 against the fixed 504-byte ARM body at RAM `0x030036D0`; its 528-byte copy also includes 24 bytes of the next body. Genuine return/field lifetimes, distance association, the APPEND wrapper and four separate tail calculations are resolved in the private candidate. The four copy-entry and repeat-entry order groups now match through real zero-pair guards and ordinary tail values. Only the parser CMP/distance rotation remains. Integer predicate/discriminator capture fails; no C or API credit is assigned. Aggregate/by-reference drawer attempts remain 348 / 313 and 356 / 321: optimization recreates pointer equivalence and spills. Preserve API contracts; prove RAM execution addresses and copy prefixes separately. Serialized selection, alignment and arena/backing remain open; the 812-byte assembly decoder leaves C workers open. See [RAM map](../config/ram-map-us-eu.json) and [decoder](RESOURCE_BACKGROUND_DECODER.md). |
| 4 | Audio `0x08049968` (124), saved-register adapters and executable patches. | Explain native NOP versus ordinary C store; close caller/stack protocols, incoming transfers, patcher inputs, IRQ targets and later writes. Rebuild every reachable modified code state. Glue and observed shifts do not close those domains. See [audio](AUDIO_RECONSTRUCTION.md). |
| 5 | Serial IRQ `0x0803DC48` (1,616), poll (408), status (124), record provider (200). | IRQ remains unowned. The actual main-flags-owner diagnostic is 1,568 bytes / 1,310 differences; the retained shared-counter candidate is 1,624 / 809. The flags owner dies before its later sentinel/checksum roles, but local allocation and shared SEND tails differ. The ready value dies before SEND operands and supplies no missing dependency. Hold those source axes until a distinct producer is identified. The 596-byte offer refresh matches using its real next-record loop bound. The provider remains 200 / 159. Participant/index, resource, allocation, descriptor and writer domains remain open. See [scene](SCENE_LINK_ENTRY.md) and [serial](SERIAL_HANDSHAKE.md). |
| 6 | Executable inventory alongside rows 1–5. | Resolve 98 call-site plus 21 transfer observations at 112 physical sites, writable callbacks/jump tables and ten code installations (19,188 distinct ROM source bytes). Close the selector domains behind 6,699 unbacked serialized outcomes. Pending-display's 128 selected returns/controls/replays leave writer/index/target populations open, as do collision/audio writer and alias domains. Word `0xE40A40` naming `0x0803E8AF` has a source-backed compressed-map data role; other aliases and alternate incoming execution remain open. See [inventory](WHOLE_ROM_INVENTORY.md). |
| 7 | Reproducibility and publication. | Remove executable instruction bodies from original-ROM slices, resolve material inventory uncertainty and justify assembly exceptions. Reproduce a clean build with pinned tools/local inputs. Pass matching/controls, applicable tool tests, inventory and progress gates; audit contents/history, publish to `main` and keep contribution features disabled. |

The [relation-grid refresh and getters](SCENE_RELATION_GRID.md) own 144 C
extent bytes; their two callers remain exact. Its relation display owns another
160 bytes with a consistent full-word percentage-provider contract. The
[offer refresh](SCENE_LINK_ENTRY.md) owns 596 bytes with its canonical 24-byte
record owner. The [activity-zero initializer](SCENE_CONTACT_ACTIVITY_ZERO.md)
owns 452 bytes using the existing item, player, option and collision owners;
its movement worker now matches separately. These six source additions cover
1,352 bytes: 1,170 instruction, 172 literal and ten alignment bytes.
The former weak entry at `0x0800480E`
lies inside the matching refresh extent and receives no separate credit.
Sixteen previously unmapped trailing pool bytes are now owned; this is not
newly discovered executable code.

The six remaining [kind-68 attachment bodies](FRAME_ATTACHMENT_JOBS_42_94.md#observed-row-117-and-kind-68)
add 392 C bytes: 344 instruction and 48 literal bytes. They complete ownership
of the observed local 504-byte span together with two existing owners. The
settlement provider, generic EC delivery and callback populations remain open.

Three [activity-three line services](SCENE_CONTACT_ACTIVITY_THREE.md) add 580
C bytes: 542 instruction, 36 literal and two natural alignment bytes. The
existing slot owner gains its native point fields without changing layout.
The former pixel estimate omitted those two data bytes; no new executable code
is claimed. Parent drawing, rasterization and input/writer domains remain open.

The [record-selection initializer](SCENE_RECORD_SELECTION_HANDOFFS.md#initializer-continuation)
adds 544 C bytes: 462 instruction, 76 literal and six alignment bytes. It
reuses the canonical four-slot save and scene owners. Its matched extent
includes two trailing data bytes absent from the old estimate; this discovers
no new executable code. The text renderer remains unconverted.

The [dimension-prefixed background-map writer](DISPLAY_RECONSTRUCTION.md#dimension-prefixed-background-map-writer)
adds 640 C bytes: 634 instruction, four literal and two alignment bytes. Its
five actual callers remain exact with their canonical owners and separate
compilation contexts. The native affine pair consumption and partial-halfword
backing requirements are explicit; neither complete input domains nor gameplay
are claimed. The copied-RAM map drawer remains unconverted.

The [activity-zero movement worker](SCENE_CONTACT_ACTIVITY_ZERO.md#movement-worker)
adds 472 C bytes: 430 instruction, 36 literal and six alignment bytes. Its
existing states two, three and eight use a complete early dispatch before the
handler bodies, preserving the native tree without added cases. Canonical actor,
scene, option and vector interfaces remain consistent. Input/backing domains,
signed vector arithmetic and complete gameplay remain conditional.

The [variant configuration selector](ACTOR_ROUTE_SEARCH.md#variant-lifecycle-leaves-and-selector)
adds 72 C bytes: 68 instruction and four literal bytes. Its entry, loop and
address lifetimes now reproduce the complete native body with the existing
canonical owners. Eight actual connected definitions pass normal/strict checks
and their real source controls; the controller also gains its missing canonical
provider include. The six matching kinds define the supported source domain;
adjacent data does not establish a seventh variant or close writer/backing inputs.

The [map tile reader](DISPLAY_MENU_PAGES.md#hint-resource-and-map-read) and
[view interpolation setter](SCENE_CONTACT_MENU.md) add two C functions / 48
extent bytes: 44 instruction and four literal bytes. They retain their actual
caller interfaces and existing owners. The reader's row-address lifetime and
the setter's byte index now match; their actual callers and connected view
consumers pass normal/strict checks and real source controls. The motion table
and arbitrary map backing/input populations remain open.

The already-owned need-state allocator's callback cursor now uses actual
target addresses instead of pointer-array arithmetic across separate members.
Its full 248 bytes remain exact; it adds no source credit or generic EC consumer.
The route-search table's corrected 134 rows / 16,216 bytes include four already
owned entries and add no global credit.

The [independently bounded background-dimensions reader](DISPLAY_MAP_RECONSTRUCTION.md#independently-bounded-background-dimensions)
adds 52 C extent bytes: 42 instruction, eight literal and two compiler alignment
bytes. It uses the canonical whole background owner and preserves two actual
control observations around the first output store. Its incoming roots and
historical signature remain provisional; no table-data ownership, new executable
discovery or runtime coverage is claimed.

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
