# Remaining reconstruction and closure work

The current gate verifies **1,856 C functions / 258,764 C extent bytes**, plus
**4,000 separate assembly extent bytes**. The starting published baseline was
1,735 / 250,064 C bytes and 500 glue bytes. The build still obtains 16,514,452
bytes of assets and unconverted code from original slices. Whole-ROM equality
is proven; complete source ownership is not. The fixed 319,640 mapped extent
bytes are a historical comparison only.

Follow this dependency order. Accepted ownership comes from the
[manifest](../config/build-us-eu.json) and [inventory](../assets/rom-inventory.json);
untracked candidates and old match-distance receipts receive no credit.

| Order | Remaining work | Required closure evidence |
| --- | --- | --- |
| 1 | Renderer `0x080023E8` (1,400 bytes) and finalizer `0x08003248` (348). | Readable C matching both complete slots with source controls. Renderer stack homes and a variants-pointer reload lack a supported source cause; real inline stores and the live working-word hypothesis failed. Its GCSE-cached rows pseudo has no memory equivalence, so spilling cannot recreate the missing object loads. Finalizer flags/category/previous lifetimes remain unresolved; real point snapshots failed. Its terminal transfer is a saved return. Inspect retained compiler evidence before another trial. |
| 2 | Connected actor producers, attachment workers and writable callbacks. | Close kind 66's 248-byte worker, land placement `0x08024ACC` (68 bytes / six differences), movement `0x08024720` (472 / 14), and remaining attachment bodies. The byte-return ABI and later-result-use hypotheses are disproved; an invented switch arm is unsupported. Exhaust `before_step`, `on_step`, `on_remove` and attachment callback writers/targets. Row 100's EC body remains original. The constructor's interaction scanner and three two-object callbacks now have source ownership; their wider target populations remain open. See [actor state](ACTOR_STATE_RECONSTRUCTION.md) and [attachment paths](FRAME_NEED_TARGET_SELECTION.md). |
| 3 | Copied-RAM ordering, tile decoding and map drawing. | Reconstruct ROM `0xB840` (284-byte sorter), `0xB36C` (provisional 504-byte tile decoder) and `0xB564` (provisional 320-byte map body). The sorter's two-byte difference is register allocation; retain its causal failures. Verify RAM addresses and ROM load offsets independently. Copy lengths include following prefixes. The 812-byte background decoder's justified assembly ownership does not close these C-origin bodies. See [RAM map](../config/ram-map-us-eu.json) and [decoder notes](RESOURCE_BACKGROUND_DECODER.md). |
| 4 | Audio C initializer, extended-play entry and writable-code domains. | Resolve the unexplained NOP versus store at `0x08049968` in ordinary C without suppressing a store. The initial 72-byte interworking interval now has source ownership under the assembly/hardware-glue exceptions. The saved-R5 adapter's unusual caller/stack protocol remains open. Exhaust patcher inputs, incoming transfers and later executable writes; compare every reachable modified state. Observed shifts five/four and replacement-word arrivals are finite evidence. See [audio](AUDIO_RECONSTRUCTION.md). |
| 5 | Remaining startup, runtime and other mapped C bodies. | Replace every executable slice. The 60-byte debugger wrapper at `0x080002B0` has an identified no$gba packet but unresolved outer source/ABI. Other established startup/runtime intervals do not close their transitive graph. Offer confirmation now owns 224 C bytes; its surrounding scene controller and quantity-input paths remain original. Use connected callers and the current map to choose bodies; inspect previous attempts first. |
| 6 | Inventory gaps, indirect domains and later copied/modified code, alongside rows 1-5. | Close 98 unresolved call-site and 21 transfer observations at 112 physical sites. Resolve serialized indices, writable callbacks, IRQ targets, jump tables and decompression destinations across all ten installations (19,188 distinct ROM source bytes). Pending-display count/capacity/alias and arbitrary-callback domains remain open. All twelve selected endpoints of six outside-main Thumb coincidences have data roles; this does not prove execution exclusion. See [inventory](WHOLE_ROM_INVENTORY.md). |
| 7 | Completion and publication proof. | No executable instruction body may come from an original-ROM slice. Resolve material inventory uncertainty, justify every assembly exception and reproduce a clean build with pinned tools/local inputs. Pass matching/control, applicable tool-test, inventory and progress gates; audit content/history and publish to `main` with concise reader instructions and contribution features disabled. |

The [bounded runtime observations](RUNTIME_OBSERVATIONS.md) now reach shared
rendering through normal keys. Across 128 validated calls, selected fields had
no writes or observed nested IRQ entries. A Right press confirmed two real
same-object variant writes outside rendering. This does not justify `volatile`,
explain the reload or close interrupt/writer/gameplay domains. The separate
300-frame boot and byte-identical replay likewise prove selected observations,
not complete target sets. The static census retains `runtime_observations: 0`.

The census qualifies 276,062 physical instruction bytes, including four also
read as data. This is not a complete code denominator or C extent total.
Unclassified bytes remain: 3,252 inside source-owned extents, 10,640 inside
estimated envelopes and 16,433,370 elsewhere. The initial EWRAM image has no
established executable entry; later executable writes remain possible.

Retain one current paired full-build proof and its controls, unique source
attempts and bounded useful failures. Retire obsolete generated payloads and
record their removal under the existing [retention policy](LOCAL_OUTPUT_RETENTION.md).
The last measured allocation was about 3.82 GB, below 5 GB. Historical hash
receipts do not imply payload retention; do not create another archive or touch
backups/unrelated files.
