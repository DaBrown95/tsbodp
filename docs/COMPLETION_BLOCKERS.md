# Remaining reconstruction and closure work

The current gates verify **2,474 C functions / 311,372 C extent bytes**, plus
**4,060 assembly bytes**. C and assembly occupy 315,432 bytes; original slices
still supply 16,461,784 bytes of assets and unconverted code. Whole-ROM equality
is proven; complete source ownership is not. The fixed 319,640 mapped extent
bytes are solely a historical comparison, not a complete code denominator.

The [manifest](../config/build-us-eu.json), [inventory](../assets/rom-inventory.json)
and generated [triage](TRIAGE.md) contain **25 unowned rows / 10,246 estimated
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
| Renderer `0x23E8` (1,400), finalizer `0x3248` (348) | Renderer canonical 1,400/21; search 1,400/19 is rejected for an unconsumed address of a hard-register variable. Stack homes and order-load allocation remain. Finalizer's cached lower-coordinate pointer forms recover all seven homes in 28 bytes of local stack but remain 348/206. Existing R7 entry bindings include an emitted semantic failure. See [bounds and coordinate experiments](BOUNDED_INVENTORY.md) and [renderer](FRAME_INPUT.md). |
| Scene-list builder `0xF034` (308) | Canonical 308/4 remains. A real bottom-bound lifetime admits R2 and repairs the initial transfers; an HI pre-fill phase gives 308/6, with only the bottom literal/MOV/ADD order wrong. Inline consumers, first-value width, counter ownership and qualification of the existing count increment do not close it. A compatible word-return provider/byte-consumer contract also reproduces 308/4 while preserving 304 existing bytes and controls. Next evidence must preserve the reload topology while restoring the literal's later materialization. See [compiler context](COMPILER_PILOT.md). |
| Map-collapse `0x495C4` (116), inverse projector `0x48BF8` (88 compared) | Collapse remains 116/3; its earlier offset reload advances the spill rotation before the duration address. The inverse's 88/2 remains unqualified because its local-point stores have no source consumer. Genuine wide affine partials demonstrate a retained R5 save after late high-word deletion, but regroup the arithmetic and remain nonexact. A native-order late addend pair survives, yet its copies remain; binding that real pair to R4 is bypassed by COMBINE. Another owner binding repeats this cause. See [map selection](SCENE_MAP_SELECTION.md) and [projection](FRAME_INPUT.md). |
| Copied ARM map drawer `0xB564` (320) | Map transfer, tile decoder and 284-byte sorter now have source; this drawer and additional copied prefixes remain original. Aggregate/row-cursor forms remain nonexact. See [RAM installations](../config/ram-map-us-eu.json) and [decoder](RESOURCE_BACKGROUND_DECODER.md). |
| Palette `0x11C60` (400), navigation `0x14834` (548), selection `0x1510C` (184) | Native observation and induction boundaries remain unresolved. The selection's R5 column binding disables LOOP's required induction, so another binding grid repeats that cause. See [actor entries](ACTOR_ENTRIES_RECONSTRUCTION.md), [palette menu](SCENE_PALETTE_MENU.md) and [palette lifecycle](DISPLAY_PALETTE_LIFECYCLE.md). |
| Scene objects `0x28234` (160), activity-three workers `0x19640`, `0x19D80`, `0x19EF0` | A real packed-step/X-consumer fork improves the object candidate to 160/71 and preserves one X recurrence with an in-loop Y multiply. Restoring the origin's R4-to-R8 phase changes LOOP's cost decision and loses that shape; hard-R7 recurrence collides with compiler-generated Y state and is disqualified. Activity-three phase homes and full input/writer domains remain open. See [activity three](SCENE_CONTACT_ACTIVITY_THREE.md) and [object interfaces](FRAME_INPUT.md). |
| Text row reader `0x1B300` (140) | Canonical 140/73 remains. Native's scratch/update/store sequence is GCC's high-register `POST_INC` reload fallback. The inherited explicit R8 cursor prevents this operation forming; an ordinary cursor retains LDM/STM and removes the frame, but takes R7 (124/111). A real inline copy-result boundary takes R2 (132/125); the native tile-size phase repairs three other homes without repairing the cursor (124/123). This copy branch is closed. A new source must explain a genuinely ordinary cursor's high home. See [text reconstruction](DISPLAY_TEXT_RECONSTRUCTION.md). |
| Other menu, geometry, text and resource workers | Remaining rows include `0x67E0`, `0xA0A4`, `0x1AA78`, `0x39CF0`, `0x40AB4`, `0x42964`, `0x48A14` and `0x48AF8`. Use triage's current complete extents and owner documents; private type/backing premises and original memory order remain acceptance questions. |
| Serial IRQ `0x3DC48` (1,616) | Preserve the 1,624/809 baseline. Prior owner relaxation loses the R3 handoff and leaves a duplicate high-register carrier. A distinct source-consumption hypothesis is needed. See [serial](SERIAL_HANDSHAKE.md). |
| Audio master worker `0x49968` (124) | Reachable native NOP at `0x499B0` remains unexplained by tested C, compiler, alignment or known code writers. Preserve original-source/build and late-writer questions; no assembly escape. See [audio](AUDIO_RECONSTRUCTION.md). |

The weekly worker `0x2005C` now has a matching source owner. Typed actual load
destinations remove the unwanted PRE caching; qualifying its one existing
secondary-pointer memory read preserves the native R0 load/R2 copy. Qualifying
a local register instead did not do so. This source qualifier does not identify
the original declaration or establish an interrupt writer.

The serial record provider **`0x3D788` is parked** at 200 bytes / one difference.
Preserve its best candidate and both compiler investigations described in
[SERIAL_HANDSHAKE.md](SERIAL_HANDSHAKE.md#remaining-record-provider). Reopen only
when new evidence changes its prospects; initially work on the other 24 rows.

## Executable-inventory obligations

- The twelve bytes at `0x1DB20..0x1DB2C` have no independently established entry
  or data/source owner. A calibrated natural route has no entry/read hit across
  the three mapped ROM aliases; a real callback-table read is the positive
  control. This route-bounded result does not assign a role to the gap.
- Selector domains behind 6,699 unbacked serialized outcomes remain unresolved.
  A checksum or readable adjacent ROM does not establish valid table capacity.
- A controlled pending-row insertion corrupts a callback to `0x04708108`; it
  establishes malformed data, without a natural caller or IRQ-delivery claim.
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

The [secondary preparation](DISPLAY_MENU_RESULTS.md) at `0x3F908` adds one
function / 1,112 C extent bytes: 994 instruction, 112 literal and six alignment
bytes. Normal/strict positives and the actual changed-kind controls pass. Its
fresh source uses indexed entries, native owner reuse, a consumed by-value
caption point and full-word percentage temporaries. Only the actual negative
numerator has a register constraint. The prior weekly and choice gains remain.

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
unique useful attempts and bounded failures. Stay below 5 GB; leave backups and
unrelated files alone.
