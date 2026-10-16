# Remaining reconstruction and closure work

Current accepted ownership is 1,743 verified C functions and 250,244 extent
bytes, with 2,384 assembly extent bytes counted separately. The starting
published baseline was 1,735 functions, 250,064 C bytes and 500 glue bytes.
The matching build still uses original slices for 16,524,588 bytes, including
assets and unconverted code. Whole-ROM equality is established; complete source
ownership is not. The 319,640 mapped extent bytes remain only a historical comparison.
Use the current [build manifest](../config/build-us-eu.json) and
[ROM inventory](../assets/rom-inventory.json) for accepted ownership; untracked
source candidates and old private match-distance receipts add no credit.

Work in this dependency order; update each row when its stated closure evidence
is obtained rather than appending another milestone history.

| Order | Remaining connected work | Evidence needed to close it |
| --- | --- | --- |
| 1 | Renderer `0x080023E8` and finalizer `0x08003248`, with their shared object, bounds and OAM consumers. | Ordinary readable C matching the entire 1,400- and 348-byte slots, including pools/alignment, with changed-source controls. The retained renderer frontier concerns eight stack homes and a reload register. The finalizer's predicate/result lifetime and direct geometry-rejection edges remain unresolved. Its terminal register transfer is a saved return, not a hidden callback. Inspect the retained compiler intermediates and causal failures before testing another source form. |
| 2 | Actor/resource paths that produce renderer inputs and writable object callbacks; remaining attachment workers including kind 66. | Close one producer-to-consumer path at a time, preserve observed field access widths and callback reloads, and compile all affected shared-header users. Exhaust assignments to `before_step`, `on_step` and `on_remove`; matching their consumers does not close their target populations. See [actor state](ACTOR_STATE_RECONSTRUCTION.md), [attachment paths](FRAME_NEED_TARGET_SELECTION.md) and [display](DISPLAY_RECONSTRUCTION.md). |
| 3 | Copied-RAM ordering, custom resource decoders and map drawing. | Reconstruct the unconverted copies at ROM `0xB840` (284-byte ordering), `0xB36C` (provisional 504-byte decoder family), `0x2EC` (provisional 812-byte decoder family), and `0xB564` (provisional 320-byte map body). The sorter's retained two-byte mismatch is register allocation: sum and priority-layer pseudos coalesce to `r4`, where the original adds into `r3` at `+0x80` and uses it at `+0x8C`. Forcing the sum, separating layer lifetimes, changing the natural Y definition and respelling the score failed; inspect the retained `reports/current-goal/sort-cause/` compiler evidence before another hypothesis. Verify at RAM execution addresses and original load offsets. Copy lengths include following prefixes and do not prove function boundaries. The collision dispatcher, tile allocator and map-transfer body already have C ownership; do not repeat those matches. See [RAM map](../config/ram-map-us-eu.json) and [BIOS handoffs](RESOURCE_BIOS_HANDOFFS.md). |
| 4 | Audio master-volume C initializer, patcher input domain and remaining copied ARM/Thumb transfers. | The 1,604-byte mixer block and 140-byte Timer-1 IRQ have justified source assembly, exact controls and 1,712 instruction bytes plus 32 data bytes. Four initialization/shutdown wrappers contribute 120 C bytes. The known master-volume callers select patch shifts five and four; this does not close all possible incoming transfers. Resolve the unexplained no-op versus store in ordinary C at `0x08049968` without suppressing a store. Close the reconstructed patcher's caller input range and all possible writable-code states, then compare every reachable modified state. Source ownership of the patcher does not establish its runtime domain. See [audio](AUDIO_RECONSTRUCTION.md) and [copied kernels](WHOLE_ROM_INVENTORY.md#copied-code-and-audio-kernels). |
| 5 | Remaining startup, runtime and all other mapped executable bodies. | Replace every executable slice with a C definition or a justified hardware/assembly-origin exception. The [140-byte hardware startup source](STARTUP_RECONSTRUCTION.md) accounts for entry/reset/copy assembly, 98 instruction bytes and 42 data/alignment bytes, with exact individual and joint-link proofs and controls. The ordinary game entry remains unconverted C work. Track exact ROM ownership and RAM aliases, including mixed dispatcher-copy tails. A candidate envelope or familiar prologue does not establish a C/assembly boundary. |
| 6 | Indirect target, writable-code and unresolved-region closure, alongside rows 1-5. | The current inventory has 98 unresolved call-site observations and 22 unresolved transfer observations, 113 distinct physical sites. Close incoming register domains, serialized table indices and all callback/IRQ writers; record table bounds separately from observed prefixes. Account for all ten installations (19,188 distinct ROM source bytes), later executable writes, decompression destinations and self-modified states. Investigate the six remaining outside-main Thumb coincidences and unresolved banks using references/formats and targeted runtime tracing. There are currently zero recorded runtime observations. Execution of a target does not prove a complete target set. |
| 7 | Completion proof and publication. | No executable instruction body may come from an original-ROM slice. Resolve material inventory uncertainty, audit every assembly exception, and reproduce a clean build from pinned tools and local inputs. Run all matching/control, tool-test, inventory and progress gates; audit tracked content and outgoing history; publish to `main` with concise reproducible reader instructions and contribution features disabled. |

The current census qualifies 270,656 physical instruction bytes, including four
also read as data; these are static instruction observations, not a full code
denominator or C extent total. Its 3,080 unclassified source-owned bytes,
16,130 unclassified estimated-envelope bytes and 16,433,786 other unresolved
ROM bytes still require role evidence. Original assets and proven
non-executable data may remain extracted locally. The initial EWRAM image has
no established executable entry; later executable writes remain possible.

The current verified proof and its controls remain intact. The measured project
allocation after retiring ten obsolete proof directories on 16 October was
3,364,384,768 bytes, below the 5 GB limit. All distinct inputs remain in the
current proof, committed history or retained private attempts. Follow
[local output retention](LOCAL_OUTPUT_RETENTION.md); preserve unique source
attempts and bounded useful failures, and retire duplicate generated outputs
without another archive. Old hash receipts do not imply their payload survives.
