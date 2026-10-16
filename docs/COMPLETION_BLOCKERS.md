# Remaining reconstruction and closure work

The current gate verifies **2,162 C functions / 277,580 C extent bytes**, plus
**4,060 separate assembly extent bytes**. The starting baseline was
1,735 / 250,064 C bytes and 500 glue bytes. Original slices still supply
16,495,576 bytes of assets and unconverted code. Whole-ROM equality is proven;
complete source ownership is not. The fixed 319,640 mapped extent bytes are
solely a historical comparison.

Follow this dependency order. Accepted ownership comes from the
[manifest](../config/build-us-eu.json) and [inventory](../assets/rom-inventory.json).
Untracked candidates and old match-distance receipts receive no credit.

| Order | Remaining work | Closure required / present blocker |
| --- | --- | --- |
| 1 | Renderer `0x080023E8` (1,400 bytes), finalizer `0x08003248` (348). | Readable C matching both complete slots, with controls. Renderer needs native frame/register allocation together with three variant reads; the retained indexed-record producer preserves those reads but is 1,396 bytes / 682 differences. Real stores/live-word trials failed. The two-counter declaration hoist already exists and still differs by 25 bytes; its first two stack homes are frame-byte pointers. Finalizer native stack placement remains unexplained: candidate flags/category snapshots already survive swaps, and its previous-index producer already crosses the backedge. Point snapshots failed; native accesses supply no address-taking producer. Four genuine value constraints give 348 / 304 with a 24-byte frame; a real previous-index capture removes repeated decrements but still has 24 rather than 28 stack bytes. Inspect retained compiler evidence before another trial. |
| 2 | Connected actor and attachment lifecycles. | Finish kind 66 (248), movement `0x08024720` (472 / 14), and remaining modules. Land placement now owns 68 C bytes with genuine compiler constraints; the header family owns its complete 1,212-byte local interval. Of 48 observed-prefix EC8 leaves, 44 have source; one path remains private, while an owned zero-only writer and two no-write selectors supply no grounded cases. Private rows 117 and 85 depend on settlement `0x0801BA40` (188); its candidate already has the native counter-address producer but still mismatches. Inlining the actual clamp/UI helper also leaves 39 differences: first CSE merges its late pointer into the existing world root. Row 85 also needs its selector/EC and selection remover `0x080454DC` (192). Three variant lifecycle leaves now own 12 bytes, but their 72-byte selector remains unmatched and the generic EC consumer is unidentified. Exhaust writable callbacks. See [actor state](ACTOR_STATE_RECONSTRUCTION.md) and [attachments](FRAME_NEED_TARGET_SELECTION.md). |
| 3 | Copied-RAM sorter, tile decoder and map drawer. | Match ROM `0xB840` (284), `0xB36C` (provisional 504) and `0xB564` (320: 316 instruction bytes plus four literal bytes). The constrained sort diagnostic remains two bytes different; its source/register cause is unresolved. The drawer's refreshed 308-byte failure has overlapping row-count/copy-value register bindings and supplies no semantic qualification. Its width reread survives first CSE but is reused by GCSE; prior saved-next-row and reread trials also fail. Verify RAM/load addresses separately: copy lengths include following prefixes. The owned 812-byte assembly decoder does not close these C-origin bodies. See [RAM map](../config/ram-map-us-eu.json) and [decoder](RESOURCE_BACKGROUND_DECODER.md). |
| 4 | Audio initializer, unusual entry protocols and executable writes. | Explain the NOP versus store at `0x08049968` in ordinary C. The saved-R5 adapter's caller/stack protocol remains open despite ownership of the initial 72-byte glue interval. Exhaust patcher inputs, incoming transfers and later writes; compare every reachable modified state. Observed converter shifts five/four remain conditional evidence. See [audio](AUDIO_RECONSTRUCTION.md). |
| 5 | Other startup, runtime and scene bodies. | The five-body status-scene interval `0x0801BD18..0x0801C47C` now owns 1,892 C bytes. Finish its separate 124-byte status reader, 408-byte serial poll and statically rooted next-stage IRQ `0x0803DC48` (1,616). A truthful IRQ representation-copy recipe creates stack stores absent natively. The poll's corrected clock-before-timestamp observation repairs ten bytes but leaves 408 / 91; first-loop hoisting remains. The row-23 scene step is 696 / 64, with its offer loop now exact but phase/input paths unmatched. Debugger glue ownership leaves eight preceding zero bytes and incoming/writer domains unresolved. World-effect callbacks `0x080052EC` (252) and `0x080054D0` (180), their controller and quantity-input paths remain original. First-CSE widened-load reuse explains missing rereads; disabling it still mismatches and introduces rejected data. See [scene paths](SCENE_LINK_ENTRY.md) and [serial paths](SERIAL_HANDSHAKE.md). |
| 6 | Inventory closure alongside rows 1-5. | Close 98 unresolved call-site and 21 transfer observations at 112 physical sites. Exhaust serialized indices, writable/IRQ callbacks, jump tables, decompression destinations and all ten code installations (19,188 distinct ROM source bytes). Pending-display and computed collision count/header/alias domains remain open. Startup DMA establishes a pre-install zero writer for the background decoder callback; later writers and re-entry remain open. Selected outside-main endpoints have data roles, which does not establish execution exclusion. See [inventory](WHOLE_ROM_INVENTORY.md). |
| 7 | Final reproducibility and publication. | Obtain no executable instruction body from original-ROM slices; resolve material inventory uncertainty and justify every assembly exception. Reproduce a clean build with pinned tools/local inputs. Pass matching/control, applicable tool-test, inventory and progress gates, audit content/history and publish to `main`. Keep reader instructions concise and contribution features disabled. |

[Runtime observations](RUNTIME_OBSERVATIONS.md) cover 128 renderer calls without
selected-field writes or nested IRQ entries, plus two actual variant writes
outside rendering. They neither justify `volatile` nor close writer/gameplay
populations. Boot/replay evidence is also bounded; the static census retains
`runtime_observations: 0`.

The census qualifies 279,646 physical instruction bytes, including four also
read as data; this is no complete denominator. Unclassified bytes remain:
3,654 inside owned extents, 6,442 inside estimated envelopes and 16,433,010
elsewhere. The initial EWRAM image has no established executable entry;
later executable writes remain possible.

Retain one current paired full proof and controls, unique source attempts and
bounded useful failures. Retire obsolete generated payloads with a record under
the existing [retention policy](LOCAL_OUTPUT_RETENTION.md). Measure allocation
after gates and retirement; keep the project below 5 GB. Historical hashes do
not require permanent payload retention. Leave backups and unrelated files alone.
