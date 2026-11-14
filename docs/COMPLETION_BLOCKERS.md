# Remaining reconstruction and closure work

The current gates verify **2,540 C functions / 318,700 C extent bytes**, plus
**4,068 assembly bytes**. Original slices still supply 16,454,448 bytes of assets
and unconverted code. Whole-ROM equality is proven; complete source ownership
is not. The fixed 319,640 bytes remain a historical comparison, not a complete
code denominator.

The [manifest](../config/build-us-eu.json), [inventory](../assets/rom-inventory.json)
and generated [triage](TRIAGE.md) contain **4 unowned rows / 3,684 estimated
bytes**. This finite worklist does not establish that all executable regions
have been discovered. Candidate scores grant no source credit.

## Latest accepted source

The [map-selection collapse handler](../src/scene/scene_map_selection_collapse_details.c)
at `0x495C4` adds **one C function / 116 extent bytes**, including its pool.
It starts the detail-panel scroll, releases the palette block, updates object
flags and reports when the scroll has finished. A wide field-offset temporary
preserves the native R2 lifetime with the pinned compiler; its low word forms
the scroll-duration address. The complete extent and changed-source control
pass the pilot, full-ROM and progress gates. Names and UI roles remain
inferred; this adds no runtime observation.

The [serial record provider](../src/link/link_prepare_serial_records.c) at
`0x3D788` previously added 200 C bytes. Its wide address temporary preserves
the native R0-to-R4 transfer; only the low 32 bits form the pointer.

The earlier [scene-object step builder](../src/frame/frame_create_scene_objects_at_steps_unrooted_28234.c)
at `0x28234` still has provisional incoming execution evidence and a provisional
six-formal interface. Its `cfg_root: false` owner supplies no new incoming
entry, rooted instruction/data qualification, runtime observation or callback-
domain closure. Its 160 bytes remain independently role-unclassified.

The [selected-map tile loader](../src/frame/frame_load_selected_map_tiles.c)
previously added 392 C bytes; the [copied ARM map drawer](FRAME_MAP_STAGING.md)
added 320; the [finalizer](FRAME_OBJECT_FINALIZATION.md) added 348;
the [inverse projection owners](GRID_INVERSE_RECONSTRUCTION.md) added 216.
Copy extents remain separately accounted.

## Remaining source work

| Region | Consequential obstacle |
| --- | --- |
| Renderer `0x23E8` (1,400) | Recover the remaining real stack homes and comparison lifetimes. Native input and partial-word ownership have improved complete candidates; exhausted binding and address-only families stay parked. |
| Activity preparation `0x19640` (544) | Preserve geometry roles and bound reloads while recovering the native availability and output-pointer allocation. |
| Serial IRQ `0x3DC48` (1,616) | The latest private candidate has the correct size and 353 differing bytes. Preserve native receive/readiness lifetimes while resolving loop and shared-tail allocation. No C credit. |
| Audio master `0x49968` (124) | Two bytes remain unexplained around a reachable native NOP. Original SDK lineage does not justify an assembly exception. |

Further compiler or tool work needs a concrete unfinished consumer and a
falsifiable experiment. A worse complete candidate is useful when it reveals
a native lifetime or changes the next experiment; it earns zero recovered C.
Useful failed source families remain private with consolidated findings.

## Executable ownership and semantic uncertainty

The census retains **97 callback and 21 dispatch observations at 111 physical
sites**. Observed table prefixes do not prove complete target populations.
Unqualified serialized selectors, callback writers, aliases and executable
installations can still conceal unowned executable code. The finite rooted
instruction account has no unowned instruction bytes outside the remaining
worklist; it does not establish an executable denominator.

The audio effect path is a concrete open ownership question. Its native byte
selector does not enforce the observed 51-record prefix. A finite capture of
766 potential field locations recovers only existing source owners where
exact entries are qualified. Effects 106/107 also produce unqualified ROM-window
operands, including `0x08ED0975`. Their source words have independent numeric
data uses; that does not exclude alternate callback interpretation. No actual
selecting module/state, complete effect domain or new executable entry has
been established. Resolve the reaching selector domain before seeding bodies
from these words. A named pre-jingle caller now has a conditional native
producer/effect-domain proof. Its actual text backing and intervening callback/
writer preservation remain open; this establishes no new entry. These audio
diagnostics add **zero source or ownership closures**.

Within existing source extents, historical formals, field names and event
meanings are semantic uncertainties. Unknown code/data/padding roles and
alternate entries require a separate ownership assessment. The census retains
**920 owned-extent bytes without qualified independent roles**: the previous
760 bytes plus the new unrooted scene-step owner's 160 bytes. Current compiler-
output provenance does not establish historical intent
or exclude alternate entries. Neither category becomes closed merely because
the containing source extent matches.

Known copies cover 19,188 distinct ROM source bytes, including data. Writer and
incoming-target populations remain open. The twelve bytes at `0x1DB20..0x1DB2C`
still have no independently established entry or source/data owner. Other
serialized, palette, scene and saved-state obligations remain in the
[whole-ROM inventory](WHOLE_ROM_INVENTORY.md), [bounded findings](BOUNDED_INVENTORY.md)
and [runtime observations](RUNTIME_OBSERVATIONS.md). Matching source establishes
no new runtime execution.

## Completion gate

Finish when every executable region has a matching source owner, genuine
assembly exceptions are justified, material inventory gaps are resolved, and
a clean reproducible byte-identical build and final documentation are on
`main`. Keep references fixed, changed-source controls, source ownership,
mapped extents and runtime evidence separate. Run applicable tests and
`make progress`; audit staged contents and outgoing history before publishing.
Keep contribution features disabled. Follow the [retention policy](LOCAL_OUTPUT_RETENTION.md):
retain one current paired full proof, unique useful attempts and bounded
failures, then retire obsolete outputs. The reconstruction remains incomplete.
