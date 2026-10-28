# Remaining reconstruction and closure work

The current gates verify **2,484 C functions / 315,664 C extent bytes**, plus
**4,060 assembly bytes**. C and assembly occupy 319,724 bytes; original slices
still supply 16,457,492 bytes of assets and unconverted code. Whole-ROM equality
is proven; complete source ownership is not. The fixed 319,640 mapped extent
bytes are solely a historical comparison, not a complete code denominator.

The [manifest](../config/build-us-eu.json), [inventory](../assets/rom-inventory.json)
and generated [triage](TRIAGE.md) contain **15 unowned rows / 5,956 estimated
bytes**. The triage records complete candidate comparisons and retained inputs;
none of those candidates receives source credit. Completed paths and their
findings remain in the owner documents and publication history.

Pending-action cleanup at `0xA0A4` now has a complete 292-byte C owner. An
ordinary 0/1 result and the canonical byte-return interface recover the native
spill and root-address load without a private header override. Its 290-byte
function includes 16 literal bytes; the last two extent bytes are explicit
source alignment. See [frame input](FRAME_INPUT.md).

The scanner's entry extents total 325,672 bytes. The progress source overlay
totals 325,680 bytes because it also includes eight already-owned IRQ literal
data bytes at `0x2A0`; those bytes are already counted within assembly glue.
These mapping totals remain separate from source coverage and executable totals.

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
| Renderer `0x23E8` (1,400), finalizer `0x3248` (348) | Renderer canonical 1,400/15: the real early counter, R6/R8 recurrences and independent roots recover native counter/index/OAM homes. Five other homes and the R3/R4 comparison scratch remain. The unconsumed-register-address search source remains rejected. Finalizer canonical 336/187 remains; scalar-pointer consumers recover guarded lower-X and one native seven-home frame, but indexed/four-pointer compositions replace it with nonnative carriers or a duplicated upper-X spill. These bounded families are parked. See [renderer](FRAME_INPUT.md) and [bounds](BOUNDED_INVENTORY.md). |
| Scene-list builder `0xF034` (308) | Canonical 308/4 remains. A real bottom-bound lifetime admits R2 and repairs the initial transfers; an HI pre-fill phase gives 308/6, with only the bottom literal/MOV/ADD order wrong. Inline consumers, first-value width, counter ownership and qualification of the existing count increment do not close it. A compatible word-return provider/byte-consumer contract also reproduces 308/4 while preserving 304 existing bytes and controls. In the 308/6 candidate, the final reload need excludes R0/R1 and selects R2. Each needs iteration clears `used_spill_regs`, so a transient R2 reservation cannot be assumed to survive later address rematerialization; an actual final need must retain it. See [compiler context](COMPILER_PILOT.md). |
| Map-collapse `0x495C4` (116), inverse projector `0x48BF8` (88 compared) | Preferred complete results remain 116/3 and qualified 88/6. Collapse's genuine true-arm owner preserves the R2 constant but loses native address/base continuity. Inverse origin subobject pointers reproduce 88/6; a real early sum changes allocation without restoring the native save/context roles. The old unconsumed-local 88/2 stays unqualified; no narrowing or nonalias premise follows from the two actual callers. See [map selection](SCENE_MAP_SELECTION.md) and [projection](FRAME_INPUT.md). |
| Copied ARM map drawer `0xB564` (320) | Canonical 320/116 remains. A distinct actual header/address-word graph reaches 324/189 and preserves three native source writebacks, but conservative pair liveness excludes the native payload registers; counter composition adds a frame. These families are parked. Map transfer, decoder, sorter and both installation tails already have source. See [RAM installations](../config/ram-map-us-eu.json) and [decoder](RESOURCE_BACKGROUND_DECODER.md). |
| Scene objects `0x28234` (160), activity-three preparation `0x19640` (544) | A real packed-step/X-consumer fork improves the object candidate to 160/71 and preserves one X recurrence with an in-loop Y multiply; a shared R2 origin reader recovers the loop loads but swaps high roles, while an explicit preheader lets GCSE hoist Y and create the unwanted second recurrence. Preparation recovers native geometry roles and its two bound-memory reloads, but remains 528/371: the fourth availability flag stays in R7 and displaces output pointers. Its ordinary accepted test already survives; a hard phase-R4 constraint breaks induction optimization. Drawing now has a matching 368-byte source owner: separate incoming/raster Y values and a read-only working-X snapshot recover the native twelve-byte frame; actual consumed native register owners recover the remaining phases. Hard-R7 models remain rejected by emitted behavior. The connected 320-byte raster worker also has source. Full input/writer domains remain open. See [activity three](SCENE_CONTACT_ACTIVITY_THREE.md) and [object interfaces](FRAME_INPUT.md). |
| Other menu, geometry, text and resource workers | Point `0x67E0` remains 152/92; a genuine two-SI interface gives 144/106 with native entry stores but nonnative PRE-promoted address owners. Selected-tile `0x39CF0` remains 392/109 under the canonical API. At `0x48A14`, the late copy is removed by COMBINE and the backend permits independent shift registers; wide/accepted-witness routes supply no transferable consumer. `0x48AF8` remains open. The 692-byte text renderer has a matching source owner. |
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
when new evidence changes its prospects; work on the remaining non-provider rows.

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
- The immediate audio volume selector has ten validated targets. The later
  [saved-byte call's first-hop operands](WHOLE_ROM_INVENTORY.md#saved-volume-first-hop-operands)
  now require only six existing game-code owners; six other operands lie outside
  game ROM and work RAM. Saved-state/table validity and subsequent execution
  remain open, as do collision/audio writers, aliases and executable changes.
- The `0xE1EE` interior-entry-shaped value has a palette-data role but no proven
  executable consumer/prepared-R1 contract. Other code-looking data and copied
  prefixes retain explicit uncertainty.

The [whole-ROM inventory](WHOLE_ROM_INVENTORY.md), [bounded findings](BOUNDED_INVENTORY.md)
and [runtime observations](RUNTIME_OBSERVATIONS.md) record evidence and limits.
The current census separately counts instructions, data, alignment, estimated
extents and unresolved bytes. Source matches establish no new runtime execution.

## Latest accepted gain and final gate

[Catalog confirmation](../src/scene/scene_catalog_confirm_original.c) at
`0x42964` adds one function / 656 C extent bytes: 574 instruction, 72 literal
and ten alignment bytes. Real scalar definitions bound partial word-owner
lifetimes; the inline entry/kind helper retains the native ordinal transfer
without extra calls or a kind stack slot. Each field is assigned before its
own read; no whole uninitialized record is read. All complete source controls,
the full-ROM comparison and the progress gate pass. This closes one source
row and adds no runtime, callback-domain or assembly-exception credit.

The canonical action-work view now exposes the native halfword variation
producer and existing low-byte consumer in one two-byte union at actor+0x66.
The action remains at+0x64 and cue handle at+0x68. Nine existing functions retain
852 bytes under normal/strict compilation with controls; the full importer
closure is verified in the current build. Catalog confirmation now uses this
action-work view; no new input-domain or runtime claim follows from its match.

All bytes inside current source/glue extents now have instruction, referenced
data or explicit compiler-emitted roles. Catalog confirmation's five two-byte
zero-alignment regions are already included in its 656-byte extent and add no
source or instruction credit. Source-object mappings and directives support
these data roles; they do not exclude every alternate incoming execution.
Unowned regions and target populations remain open. Triage excludes the rejected
search source while retaining its complete comparison and raw history.

Completion still requires every executable region to have a matching source
owner, justified genuine assembly exceptions, resolved material inventory gaps,
and a clean reproducible byte-identical build with final documentation on
`main`. Preserve fixed references and changed-source controls, run applicable
tests and `make progress`, audit staged contents/outgoing history, then publish.
Keep contribution features disabled. Retire verified replaced outputs under the
[retention policy](LOCAL_OUTPUT_RETENTION.md), keeping one current paired proof,
unique useful attempts and bounded failures. Leave backups and unrelated files
alone.
