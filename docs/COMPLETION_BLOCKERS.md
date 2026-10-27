# Remaining reconstruction and closure work

The current gates verify **2,481 C functions / 314,024 C extent bytes**, plus
**4,060 assembly bytes**. C and assembly occupy 318,084 bytes; original slices
still supply 16,459,132 bytes of assets and unconverted code. Whole-ROM equality
is proven; complete source ownership is not. The fixed 319,640 mapped extent
bytes are solely a historical comparison, not a complete code denominator.

The [manifest](../config/build-us-eu.json), [inventory](../assets/rom-inventory.json)
and generated [triage](TRIAGE.md) contain **18 unowned rows / 7,594 estimated
bytes**. The triage records complete candidate comparisons and retained inputs;
none of those candidates receives source credit. Completed paths and their
findings remain in the owner documents and publication history.

## Constraints that determine the next experiments

1. **Source value ownership and compiler transformations.** Several near misses
   differ in allocation after CSE/COMBINE has deleted the source temporary.
   Inspect the actual passes before proposing another binding or pointer form.
   Source interfaces, types and historical toolchain identity remain hypotheses;
   compare complete output with the pinned tools and known matches.
2. **Executable ownership beyond the finite worklist.** The census still has
   97 call-site and 21 transfer observations at 111 physical sites. Observed
   table prefixes, serialized selectors, aliases and writable callbacks do not
   establish complete target populations. Tie inventory/runtime work to a named
   executable gap rather than accumulating unrelated bounds.
3. **Executable copies, changes and exceptions.** Ten known installations cover
   19,188 distinct ROM source bytes, including data. Complete code-writer and
   incoming-target populations remain open. Genuine assembly exceptions need
   original-source or concrete native evidence; an unexplained C mismatch is
   insufficient justification.

## Active source work

| Connected region | Current obstacle and useful next evidence |
| --- | --- |
| Renderer `0x23E8` (1,400), finalizer `0x3248` (348) | Renderer canonical 1,400/21; search 1,400/19 is rejected for an unconsumed address of a hard-register variable. Stack homes and order-load allocation remain. Fresh by-value points recover the finalizer's high roles without bindings, but initial DI geometry values remain live too long. A real work record instead duplicates the loop header before allocation; whole-bounds/point-return copies add code. Actual point-pointer comparators retain backing, but LOOP hoists extra pointer/value homes and leaves frame32 against native28 (360/313 and 352/258). These are representation/loop constraints, not evidence for an R7 binding. See [bounds and coordinate experiments](BOUNDED_INVENTORY.md) and [renderer](FRAME_INPUT.md). |
| Scene-list builder `0xF034` (308) | Canonical 308/4 remains. A real bottom-bound lifetime admits R2 and repairs the initial transfers; an HI pre-fill phase gives 308/6, with only the bottom literal/MOV/ADD order wrong. Inline consumers, first-value width, counter ownership and qualification of the existing count increment do not close it. A compatible word-return provider/byte-consumer contract also reproduces 308/4 while preserving 304 existing bytes and controls. In the 308/6 candidate, the final reload need excludes R0/R1 and selects R2. Each needs iteration clears `used_spill_regs`, so a transient R2 reservation cannot be assumed to survive later address rematerialization; an actual final need must retain it. See [compiler context](COMPILER_PILOT.md). |
| Map-collapse `0x495C4` (116), inverse projector `0x48BF8` (88 compared) | Collapse remains 116/3; its earlier offset reload advances the spill rotation before the duration address. A scan of 2,276 matched Thumb owners with mapping symbols supplied no peer for its scratch reuse; objects without mappings were excluded. The inverse's 88/2 remains unqualified because its local-point stores have no source consumer. Genuine wide affine partials demonstrate a retained R5 save after late high-word deletion, but regroup the arithmetic and remain nonexact. A native-order late addend pair survives, yet its copies remain; binding that real pair to R4 is bypassed by COMBINE. Another owner binding repeats this cause. See [map selection](SCENE_MAP_SELECTION.md) and [projection](FRAME_INPUT.md). |
| Copied ARM map drawer `0xB564` (320) | A private trial with two field consumers and declared union subobjects retains four pair loads, fresh metadata reads and no local stack allocation, but remains 316/188 over the full 320 bytes. CSE/COMBINE delete the three real IP destination phases; positive-offset scalar stores fail to form the remaining native grouped stores. A different producer/reload graph must retain both load and store shapes. Map transfer, decoder and sorter have source. The two installation tails of 16 and 12 bytes already belong to matching C owners; the decoder's extra 24 bytes remain part of this same drawer gap. See [RAM installations](../config/ram-map-us-eu.json) and [decoder](RESOURCE_BACKGROUND_DECODER.md). |
| Scene objects `0x28234` (160), activity-three preparation `0x19640` (544) | A real packed-step/X-consumer fork improves the object candidate to 160/71 and preserves one X recurrence with an in-loop Y multiply; a shared R2 origin reader recovers the loop loads but swaps high roles, while an explicit preheader lets GCSE hoist Y and create the unwanted second recurrence. Preparation recovers native geometry roles and its two bound-memory reloads, but remains 528/371: the fourth availability flag stays in R7 and displaces output pointers. Its ordinary accepted test already survives; a hard phase-R4 constraint breaks induction optimization. Drawing now has a matching 368-byte source owner: separate incoming/raster Y values and a read-only working-X snapshot recover the native twelve-byte frame; actual consumed native register owners recover the remaining phases. Hard-R7 models remain rejected by emitted behavior. The connected 320-byte raster worker also has source. Full input/writer domains remain open. See [activity three](SCENE_CONTACT_ACTIVITY_THREE.md) and [object interfaces](FRAME_INPUT.md). |
| Relation delta `0x40AB4` (692), catalog confirmation `0x42964` (656) | A genuine body-local history address keeps normal GCSE from hoisting it over the earlier criterion loop; the delta's actual history/request/code setup order now agrees, but field-pointer/byte-carrier allocation remains wrong (692/306). Disabling GCSE breaks the matched neighbor. Confirmation now retains all four outcome stores/two reads; a real R2 success producer prevents late cross-jump merging. Its early request/state/list/record lifetimes and zero producer remain wrong (652/596). These are source/dataflow constraints, not missing constant offsets. |
| Other menu, geometry, text and resource workers | Pending cleanup `0xA0A4` remains 292/2. Its first reload pool is sorted R0/R1/R2; changing admission chronology cannot select native R2 while R0 stays free. A real first-count producer admits R2 but splits the common loop header (308/212), so that formulation is closed. A fresh by-value `0x67E0` sample adds a separate input spill. Selected-tile `0x39CF0` reproduces 392/109 under the canonical API; inner-loop syntax does not explain its reloads. At `0x48A14`, a real SI left reload survives LOOP but is forwarded in second CSE; a later R2 consumer cannot force the native MOV+ASR because the backend permits a distinct shift destination. Its covered copy is deleted by COMBINE. `0x48AF8` also remains open. The 692-byte text renderer now has a matching source owner. |
| Serial IRQ `0x3DC48` (1,616) | Preserve the 1,624/809 baseline. A symbolic MMIO member owner adds reads; scalar indirect accesses restore the read/write sites but derive receive addresses from control and create an extra R9 SEND carrier. These formulations are closed. A genuine owner/consumer fact must preserve the independent native accesses and R3 handoff. See [serial](SERIAL_HANDSHAKE.md). |
| Audio master worker `0x49968` (124) | The recovered original November 2002 SDK has two identical 92-byte master providers with the bad literal and an actual byte store. It establishes lineage without explaining the later reachable NOP at `0x499B0`. A later commercial object/build chain or demonstrated C producer is still needed; no assembly exception follows. See [audio](AUDIO_RECONSTRUCTION.md). |

The weekly worker `0x2005C` now has a matching source owner. Typed actual load
destinations remove the unwanted PRE caching; qualifying its one existing
secondary-pointer memory read preserves the native R0 load/R2 copy. Qualifying
a local register instead did not do so. This source qualifier does not identify
the original declaration or establish an interrupt writer.

The inverse's coordinate-plus-status result retains a third real stack slot
(108/62), while an error-sentinel point removes its return copy but retains the
marker store and sign-test reload (104/59). Those representations do not supply
the native eight-byte coordinate work; their failed sources remain private.

The serial record provider **`0x3D788` is parked** at 200 bytes / one difference.
Preserve its best candidate and both compiler investigations described in
[SERIAL_HANDSHAKE.md](SERIAL_HANDSHAKE.md#remaining-record-provider). Reopen only
when new evidence changes its prospects; work on the other eighteen rows.

## Executable-inventory obligations

- The twelve bytes at `0x1DB20..0x1DB2C` have no independently established entry
  or data/source owner. A calibrated natural route has no entry/read hit across
  the three mapped ROM aliases; a real callback-table read is the positive
  control. This route-bounded result does not assign a role to the gap.
- Selector domains behind 6,699 unbacked serialized outcomes remain unresolved.
  A checksum or readable adjacent ROM does not establish valid table capacity.
- A controlled pending-row insertion corrupts a callback to `0x04708108`; it
  establishes malformed data, without a natural caller or IRQ-delivery claim.
- [Selected animation families](WHOLE_ROM_INVENTORY.md#selected-sequence-backing-and-count-bounds)
  now have complete declared-frame/count checks. The simple-actor selector has
  a native seven-column bound for all U8 animations. These conditional data
  bounds do not close mutable pointers, callback effects or aliases. The menu
  preserves appearance 0..11 at the exact need-effect byte; save decoding still
  admits 12..15 without semantic validation.
- Origin index four selects both installed map callback words. The native
  setter and updater can write those words; a post-provider fixture captures
  the resulting zero target at `0x39BE2`. Whole-caller reachability is unproven.
  Native checks of the inspected producer chain bound the published count to
  zero through four; diagnostic five returns before publication. Known slot
  writers give zero through three or 255. Excluding view four requires that
  every fresh count preserve this domain across providers, callbacks, IRQ work
  and other aliases; complete writer/target populations remain open.
- The immediate audio volume selector has ten validated targets; its later
  saved-byte consumer and shared dispatch table remain open. Collision/audio
  writers, aliases and executable modifications still need ownership evidence.
- The `0xE1EE` interior-entry-shaped value has a palette-data role but no proven
  executable consumer/prepared-R1 contract. Other code-looking data and copied
  prefixes retain explicit uncertainty.

The [whole-ROM inventory](WHOLE_ROM_INVENTORY.md), [bounded findings](BOUNDED_INVENTORY.md)
and [runtime observations](RUNTIME_OBSERVATIONS.md) record evidence and limits.
The current census separately counts instructions, data, alignment, estimated
extents and unresolved bytes. Source matches establish no new runtime execution.

## Latest accepted gain and final gate

The [palette block worker](DISPLAY_PALETTE_LIFECYCLE.md#block-interpolation) at
`0x11C60` adds one function / 400 C extent bytes. Two-byte input value owners
retain the native current word and late target spill; ordinary flag reads
preserve the remaining prefix. Normal/strict positives, actual controls and
the full matching/progress gate cover all bytes, including pools and alignment.
No register bindings or new runtime/domain claims are introduced.

The [text row reader](DISPLAY_TEXT_RECONSTRUCTION.md) at `0x1B300` adds one
function / 140 C extent bytes. Bounded halfword masks and narrowing the actual
condition after its AND preserve the native copies and reload order. The
ordinary high cursor retains native postincrement behavior; no forced R8
cursor, extra observation or output patch is used.

The [event drawing owner](SCENE_CONTACT_ACTIVITY_THREE.md) at `0x19D80` adds
one function / 368 C extent bytes, including its literal pools and alignment.
The original failed-attachment path remains documented as a bug. This closes
one known source row; it does not close the scene's input or writer domains.

The [navigation owner](SCENE_PALETTE_MENU.md#navigation-and-selection-transfer)
at `0x14834` adds one function / 548 C extent bytes: 512 instruction, 32 literal
and four alignment bytes. The matched sibling's input-loop pattern, actual
transfer-owner lifetimes and explicit no-op row fourteen recover the complete
native body. Normal/strict positives and real rejection-cue controls pass with
six connected callers/providers/siblings. The prior selection-builder,
secondary, weekly and choice gains remain.

The canonical action-work view now exposes the native halfword variation
producer and existing low-byte consumer in one two-byte union at actor+0x66.
The action remains at+0x64 and cue handle at+0x68. Nine existing functions retain
852 bytes under normal/strict compilation with controls; the full importer
closure is verified in the current build. Catalog confirmation itself remains
unconverted and receives no credit from this owner repair.

Eight previously unclassified bytes inside two existing C owners now have
compiler-emitted alignment roles, supported by their exact objects, linked
mappings and directives. This adds no source or instruction credit and does
not exclude alternate incoming execution. No bytes inside current source/glue
extents remain unclassified; unowned regions and target populations remain open. Triage now excludes an explicitly
rejected search source while retaining its complete comparison and raw history.

Completion still requires every executable region to have a matching source
owner, justified genuine assembly exceptions, resolved material inventory gaps,
and a clean reproducible byte-identical build with final documentation on
`main`. Preserve fixed references and changed-source controls, run applicable
tests and `make progress`, audit staged contents/outgoing history, then publish.
Keep contribution features disabled. Retire verified replaced outputs under the
[retention policy](LOCAL_OUTPUT_RETENTION.md), keeping one current paired proof,
unique useful attempts and bounded failures. Leave backups and unrelated files
alone.
