# Remaining reconstruction and closure work

The current gate verifies **2,217 C functions / 282,004 C extent bytes**, plus
**4,060 separate assembly extent bytes**. The starting baseline was
1,735 / 250,064 C bytes and 500 glue bytes. Original slices still supply
16,491,152 bytes of assets and unconverted code. Whole-ROM equality is proven;
complete source ownership is not. The fixed 319,640 mapped extent bytes are
solely a historical comparison.

Follow this dependency order. Accepted ownership comes from the
[manifest](../config/build-us-eu.json) and [inventory](../assets/rom-inventory.json).
Untracked candidates and old match-distance receipts receive no credit.
The finite current map still has 272 unowned rows / 39,328 estimated extent
bytes; these are a worklist, not a complete executable-code denominator.

| Order | Remaining work | Closure required / present blocker |
| --- | --- | --- |
| 1 | Renderer `0x080023E8` (1,400 bytes), finalizer `0x08003248` (348). | Match complete C slots and controls. The retained renderer has three required variant reads but unresolved frame/register allocation; the 25-byte near match is still held. A genuine eight-member work record preserves fixed memory but requires a 96-byte frame instead of 88, rejecting that layout explanation. Finalizer geometry and short predicate phases can be reproduced, but global allocation gives category R7 and spills flags immediately to SP16. Native uses category SP16 and a late flags spill to SP20, with a 28-byte rather than 24-byte frame. The scoped entry-pointer change recovers its own R9 role without fixing that cause. Existing point, address and live-value attempts already cover those premises. Inspect retained compiler evidence before another source trial. |
| 2 | Connected actor, attachment and save paths. | Finish kind 66 (248), movement `0x08024720` (472 / 14), weekly/secondary-flag routine `0x0802005C` (108), higher loader `0x0801B704` (548), settlement `0x0801BA40` (188 / 39), selection remover `0x080454DC` (192), the 72-byte variant selector and generic EC consumer. The loader still does not match after its child's layout repair. Classify the twelve bytes at `0x1DB20..0x1DB2C` and identify incoming roots for the unrooted attachment, node-pool, input and scene-nine helpers. Actor backing, indices, path-copy/record domains, later callback writes, save inputs and gameplay populations remain open; see [actor state](ACTOR_STATE_RECONSTRUCTION.md), [attachments](FRAME_NEED_TARGET_SELECTION.md), [attachment jobs](FRAME_ATTACHMENT_JOBS_42_94.md), [node pool](FRAME_NODE_POOL_1DAC4.md), [player state](SCENE_PLAYER_STATE.md), [actor entries](ACTOR_ENTRIES_RECONSTRUCTION.md), [save paths](SAVE_STREAM.md) and [frame/input](FRAME_INPUT.md). Row 4 owns its three callback bodies (580 bytes), while resource backing, selector bounds, later writers and runtime populations remain open; see [scene callbacks](SCENE_RECONSTRUCTION.md#scene-table-row-4-callbacks). Finish the downstream 400-byte palette worker and close serialized transition-index domains; see [window controller](TRANSITION_WINDOWS.md). |
| 3 | Copied-RAM sorter, tile decoder and map drawer. | Match ROM `0xB840` (284 / 2), `0xB36C` (provisional 504) and `0xB564` (320). The drawer's earlier overlapping register bindings remain unqualified. Canonical representation copies remove the local pair. The ordinary unaddressed value-pair candidate still produces 352 bytes against 320, with 302 differing or extra bytes; partial writes keep its combined value live and allocation still requires register moves. It remains held with no C credit. The sorter's R3 sum changes preallocation scheduling; the controlled Y-first, first-scheduler-disabled test also fails (284 / 52). The word-group copier remains 68 / 3; four stored nonempty word groups contain 19 records. The 124-byte resource controller is original. Verify RAM/load addresses and copy prefixes independently. The owned 812-byte assembly decoder does not close these C bodies. See [RAM map](../config/ram-map-us-eu.json) and [decoder](RESOURCE_BACKGROUND_DECODER.md). |
| 4 | Audio initializer, entry protocols and executable writes. | Explain NOP versus store in ordinary C at `0x08049968` (124). Close the saved-R5 adapter's caller/stack protocol, patcher inputs, incoming transfers and later writers; compare every reachable modified code state. The initial 72-byte glue interval and observed converter shifts do not close those domains. See [audio](AUDIO_RECONSTRUCTION.md). |
| 5 | Other startup, runtime and scene bodies. | Finish the 124-byte status reader, serial poll (408 / 91), 200-byte record provider and next-stage IRQ `0x0803DC48` (1,616). The canonical record union removes the IRQ's local-copy stores, but its 1,612-byte candidate still differs; address lifetimes, allocation and tail sharing remain unresolved. Private compiler tracing explains rotating spill-register selection in this IRQ and the 140-byte condition reader; it does not identify matching source. Escaped halfword pointers do not inherit the direct-union aliasing contract. The row-23 scene remains 696 / 64, with phase/input paths open. World-effect controllers (424 and 444) remain original despite ownership of their seven observed callback bodies. Debugger incoming/writer domains and eight preceding zero bytes remain unresolved. See [scene paths](SCENE_LINK_ENTRY.md) and [serial paths](SERIAL_HANDSHAKE.md). |
| 6 | Inventory closure alongside rows 1-5. | Close 98 call-site and 21 transfer observations at 112 physical sites; exhaust serialized indices, writable/IRQ callbacks, jump tables and all ten code installations (19,188 distinct ROM source bytes). The finite 50-root / 105-pack census identifies initial serialized contents but leaves 6,699 unbacked selector outcomes unfollowed; saved-byte and later writer domains remain open. Pending-display, collision and background-callback writer/alias domains remain open. A calibrated pending-display prefix confirms one actual default BL/BX transfer and frequent tile-bitmap alias writes; its output cap stops at 39/128 renderer returns, so it supplies no completed-route or domain closure. Selected outside-main data roles do not establish execution exclusion. See [inventory](WHOLE_ROM_INVENTORY.md). |
| 7 | Final reproducibility and publication. | Obtain no executable instruction body from original-ROM slices; resolve material inventory uncertainty and justify every assembly exception. Reproduce a clean build with pinned tools/local inputs. Pass matching/control, applicable tool-test, inventory and progress gates, audit content/history and publish to `main`. Keep reader instructions concise and contribution features disabled. |

[Runtime observations](RUNTIME_OBSERVATIONS.md) cover 128 renderer calls without
selected-field writes or nested IRQ entries, plus two actual variant writes
outside rendering. They neither justify `volatile` nor close writer/gameplay
populations. Boot/replay evidence is also bounded; the static census retains
`runtime_observations: 0`.

The census qualifies 280,890 physical instruction bytes, including 4 also
read as data; this is no complete denominator. Unclassified bytes remain:
3,730 inside owned extents, 5,104 inside estimated envelopes and 16,432,956
elsewhere. The initial EWRAM image has no established executable entry;
later executable writes remain possible.

Retain one current paired full proof and controls, unique source attempts and
bounded useful failures. Retire obsolete generated payloads with a record under
the existing [retention policy](LOCAL_OUTPUT_RETENTION.md). Measure allocation
after gates and retirement; keep the project below 5 GB. Historical hashes do
not require permanent payload retention. Leave backups and unrelated files alone.
