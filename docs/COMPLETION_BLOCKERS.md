# Remaining reconstruction and closure work

The current gate verifies **2,277 C functions / 288,092 C extent bytes**, plus
**4,060 assembly extent bytes**. The starting baseline was
1,735 / 250,064 C bytes and 500 glue bytes. Original slices still supply
16,485,064 bytes of assets and unconverted code. Whole-ROM equality is proven;
complete source ownership is not. The fixed 319,640 mapped extent bytes are
solely a historical comparison.

Follow this dependency order. The [manifest](../config/build-us-eu.json) and
[inventory](../assets/rom-inventory.json) contain accepted ownership and the full
finite worklist: 212 unowned rows / 33,290 estimated extent bytes. That worklist
is not a complete executable-code denominator. Untracked candidates and old
match-distance receipts receive no credit.

| Order | Remaining code | Current blocker and next required evidence |
| --- | --- | --- |
| 1 | Renderer `0x080023E8` (1,400 bytes), finalizer `0x08003248` (348). | Recover complete matching C and controls. The related 100-byte visibility helper is now C-owned; its incoming/view domains remain open. The renderer's 25-byte near match still has unresolved frame homes; the retained trace supplies no distinct supported source producer. The finalizer's proper public-owner baseline remains 340 bytes. A genuine R0 zero/one result survives all fourteen compiler passes, but its 340 / 285 attempt retains an extra upper-X spill, previous-index R6 and the wrong result destination. Native upper-X/upper-Y use SP8/SP12; category/flags/previous use SP16/SP20/SP24. An R7 coordinate constraint was rejected: the compiler's frame-pointer conflict exception lets it overwrite a live category value. Reusing the entry-flags variable for the later containment result preserves both values but emits the same 340 / 285 code. Existing truth-capture, narrow-type, loop-motion and binding failures must inform a distinct hypothesis before another trial. See [bounded findings](BOUNDED_INVENTORY.md) and [runtime observations](RUNTIME_OBSERVATIONS.md). |
| 2 | Connected actor, attachment and save paths. | The counter-choice bodies at `0x08023238..0x08023498` are C-owned (11 / 608 bytes). Definition rows 76 and 77/78 now have 14 C-owned bodies / 192 bytes, including two separate unrooted predicates. Their backing, selector, writable-target and generic EC delivery domains remain open; unused formals remain provisional. The shared phase-0 empty callback and phase-8 begin/step/end callbacks are C-owned (4 / 16 bytes); the phase-15 menu begin/step/end callbacks are also C-owned (1,636 bytes). Remaining phase targets and incoming-kind domains stay open. Finish movement `0x08024720` (472 / 14), kind 66 (248), weekly routine `0x0802005C` (108), loader `0x0801B704` (548), settlement `0x0801BA40` (held 188 / 22), selection remover `0x080454DC` (192), variant selector (72), generic EC consumer and palette worker (400). Resolve the twelve bytes at `0x1DB20..0x1DB2C` and unrooted helper entries. Close resource/backing, serialized-index and later-writer domains alongside those bodies. See [actor state](ACTOR_STATE_RECONSTRUCTION.md), [actor entries](ACTOR_ENTRIES_RECONSTRUCTION.md), [attachments](FRAME_ATTACHMENT_JOBS_42_94.md), [save paths](SAVE_STREAM.md) and [transitions](TRANSITION_WINDOWS.md). |
| 3 | Copied-RAM resource paths: ROM `0xB840` (284), `0xB36C` (provisional 504), `0xB564` (320) and word-group copier (68). | Sorter remains 284 / 2; R3 sum, Y-first and scheduler explanations are already tested. Defined aggregate-copy and by-reference drawer attempts remain 348 / 313 and 356 / 321: later optimization recreates pointer equivalence and spills. Preserve proper API/ownership contracts; verify RAM execution addresses and actual copy prefixes separately. The 124-byte resource controller at `0x0800AD1C` is now C-owned; serialized selection, input alignment and arena/backing domains remain open. The 812-byte assembly decoder does not close these C bodies. See [RAM map](../config/ram-map-us-eu.json) and [decoder](RESOURCE_BACKGROUND_DECODER.md). |
| 4 | Audio initializer `0x08049968` (124), saved-register adapters and executable patch paths. | Explain the native NOP versus ordinary C store. Close caller/stack protocols, incoming transfers, patcher inputs, IRQ targets and later writes; rebuild every reachable modified code state. The initial 72-byte glue and observed converter shifts do not close these domains. See [audio](AUDIO_RECONSTRUCTION.md). |
| 5 | Serial IRQ `0x0803DC48` (1,616), serial poll (408), status reader (124), record provider (200) and refresh `0x080045D0` (596). | The 404-byte scene builder at `0x08003D74` is now C-owned; participant/index, resource and allocation domains remain open. IRQ remains 1,612 bytes after its record-union repair. The refresh's latest proper-owner attempt uses ordinary variables and differs in nine of 596 bytes. Its native frame, register homes, calls and literals agree; LOOP processes a late cost offset before the record pointer, reversing both initialization and increment pairs. Capturing the shared cost destination corrects both pairs but retains a scalar index and regresses to 588 / 377; no matching credit is assigned. Row 23's lifecycle, both offer controllers and seven observed effects are C-owned; their descriptor/index/writer domains remain open. See [scene paths](SCENE_LINK_ENTRY.md) and [serial paths](SERIAL_HANDSHAKE.md). |
| 6 | Executable inventory alongside rows 1–5. | Resolve 98 call-site and 21 transfer observations at 112 physical sites, writable callbacks, jump tables and all ten code installations (19,188 distinct ROM source bytes). The serialized census still leaves 6,699 unbacked selector outcomes unfollowed. Pending-display now completes 128 selected returns, with 128 guard checks, thirteen controls, seven reporter negatives, byte-identical cold replay and displaced-state agreement. Its observed index-zero/default transfer does not close arbitrary writer, index or target domains; collision and audio writer/alias domains also remain open. The weak `0xE40A40` word naming `0x0803E8AF` remains unclassified incoming evidence despite the separately qualified menu alignment. See [inventory](WHOLE_ROM_INVENTORY.md). |
| 7 | Final reproducibility and publication. | Remove executable instruction bodies from all original-ROM slices, resolve material inventory uncertainty and justify every assembly exception. Reproduce a clean build with pinned tools/local inputs. Pass matching/control, applicable tool-test, inventory and progress gates; audit contents/history and publish to `main` with contribution features disabled. |

The generated [inventory](../assets/rom-inventory.json) records qualified
physical instructions, data and unresolved bytes separately; its instruction
union is not a complete denominator. Unclassified owned/envelope bytes,
authored NOP instructions and unresolved audio NOP tails still require closure.
Source-emitted data roles cannot suppress execution evidence or exclude an
alternate entry.
The initial EWRAM image has no established executable entry; later executable
writes remain possible. Finite runtime observations do not close populations.

Retain one current paired full proof and controls, unique source attempts and
bounded useful failures. Retire obsolete generated payloads under the existing
[retention policy](LOCAL_OUTPUT_RETENTION.md), then measure allocation and keep
the project below 5 GB. Historical hashes do not require permanent payload
retention. Leave backups and unrelated files alone.
