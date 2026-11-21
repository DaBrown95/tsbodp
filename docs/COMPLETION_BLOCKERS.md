# Remaining reconstruction and closure work

The current gates verify **2,543 C functions / 322,260 C extent bytes**, plus
**4,068 assembly bytes**. Original slices still supply 16,450,888 bytes of assets
and unconverted code. Whole-ROM equality is proven; complete source ownership
is not. The fixed 319,640 bytes remain a historical comparison, not a complete
code denominator.

The [manifest](../config/build-us-eu.json), [inventory](../assets/rom-inventory.json)
and generated [triage](TRIAGE.md) contain **1 unowned row / 124 estimated
bytes**. This finite worklist does not establish that all executable regions
have been discovered. Candidate scores grant no source credit.

## Latest accepted source

The [activity-three row preparation routine](../src/scene/scene_contact_activity_three_prepare_row.c)
at `0x19640` adds **one C function / 544 extent bytes**. It selects a row
subtype, amount, phase and available palette, then retries positions that fall
inside an earlier row's exclusion box. All 544 bytes also match the USA revision 1
function when linked at its own address. Reducing the maximum X coordinate
from 224 to 223 changes one byte. Isolated mGBA calls with the game's own
random-number and position routines reproduced the original in all 525 cases.
The changed source produced a different result in 292 cases.

The [serial interrupt handler](../src/link/link_serial_interrupt.c) at `0x3DC48`
adds **one C function / 1,616 extent bytes**. It exchanges six halfwords per
event record, validates each peer's checksum and swaps the receive buffers on
success. Both failure branches reach the original bookkeeping code. Changing
the retry limit from five to six changes one byte in the full linked extent.

The [object renderer](../src/frame/frame_render_object.c) at `0x23E8` adds
**one C function / 1,400 extent bytes**, including its pools and alignment.
It handles sprite parts, ordered multipart sequences and horizontal strips.
Independent part-index and variant-byte strides preserve the native increment
order, and a constant status cell preserves the native stack allocation with
the pinned compiler. All fields and indices are consumed by the renderer;
there is no instruction assembly or added dummy operation. The full extent,
changed-source control and whole-ROM gates pass. Names and field roles remain
inferred; this adds no runtime observation.

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
| Audio master `0x49968` (124) | The closest C emits a byte store at offset `0x48`. The original executes a NOP. In 512 mGBA calls the candidate issued 512 writes to `0x22000E38`, and the original issued zero. The origin of that instruction remains unresolved. |

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
**952 owned-extent bytes without qualified independent roles**. These include
160 bytes in the unrooted scene-step owner, 12 bytes in the renderer, and 18
bytes of compiler alignment in the serial interrupt handler. The activity row
routine adds two independently unclassified bytes. Current compiler-output
provenance leaves historical intent and alternate entries open.

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
