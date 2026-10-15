# Record-selection update and actions

The published milestone-123 batch contains six connected C replacements and
1,136 bytes. Milestone 124 adds four functions and 804 bytes,
bringing this connected group to ten functions and 1,940 bytes. All extents
include their literal pools, dispatch data and alignment. Names describe
observed behaviour and remain provisional.

Milestone 124 adds four matching C functions and 804 C bytes after the full-ROM,
changed-source and importer gates. Source coverage is 1,688 functions and
238,632 C bytes, with 500 separately counted glue bytes.

| ROM offset | Function | Bytes | Source batch |
| --- | --- | ---: | --- |
| `0x25038` | Nine-state update | 708 | 123 |
| `0x252FC` | Confirm selected slot | 180 | 123 |
| `0x253B0` | Set phase handoff | 244 | 124 |
| `0x254A4` | Set slot phase handoff | 204 | 124 |
| `0x25570` | Draw record panel | 308 | 124 |
| `0x2579C` | Shut down record selection | 48 | 124 |
| `0x257CC` | Change selected slot | 68 | 123 |
| `0x25810` | Cancel selection | 24 | 123 |
| `0x25828` | Create four scene objects | 76 | 123 |
| `0x25874` | Draw a confirmation choice | 80 | 123 |

The update connects input, object handoffs, confirmation text, palette jobs,
audio cues and save-header/slot commits. A bounded nine-entry table supplies
its switch targets. Countdown paths preserve unsigned wrap: zero decrements
to `UINT_MAX` before the transition test.

## State and interface evidence

The original initializer at `0x24E18` allocates sixteen zeroed bytes. The first
word is the return phase; the next two four-byte groups hold observed occupied
and enabled flags. The last four bytes retain unknown names. The update and
handoffs use allocation byte 13. This view applies to the scene allocation,
not every use of the shared resource-pointer global. The initializer remains
unconverted and earns no source credit.

The existing 24-byte `SceneRequest` owns scene, parameter, phase and timer words
at offsets 8, 12, 16 and 20. The 52-byte input owner supplies its local-player
byte at offset 49. Slot changes first call the horizontal helper using the
nonlocal pressed table, then reread the player and consume the low byte of the
separate local pressed table. Those distinct producers remain explicit.

Confirming a load stores the save slot, suspends audio, reads the slot, resumes
audio and tests the low byte of validation. Selection is reloaded after calls.
Mode-one confirmation uses the scene allocation's enabled and occupied flags.
The two recovered handoffs preserve byte direction and word phase arguments;
they are not interchangeable with the original initializer.

The [handoff and panel note](SCENE_RECORD_SELECTION_HANDOFFS.md) records the
canonical map-pointer, saved-clock and frame-motion owners. Four existing
bodies, totaling 696 bytes, need only field-path repairs. Those repairs add no
C functions or bytes. The same complete point tag is extracted to a guarded
header; no alternate `FrameObject` or saved-record owner is introduced.

## Matching evidence and limits

All four new bodies have fresh public normal and strict positives at their
original addresses, plus genuine changed-source controls in both profiles.
The same four roles were run for each repaired existing body: 32 roles in all.
Every positive matches its complete fixed-ROM span. Each control changes an
actual candidate byte, and all 32 candidates equal their retained private or
earlier proofs. Commands, dependencies, snapshots, ELF ownership, differences
and failed attempts are retained locally. No output patch, fixed-register
variable, embedded instruction body or added low-level glue is used.

The first batch's update initially had its correct 708-byte extent with 24
differences. Real cached-player and input-array producers resolved those
mismatches. Its choice drawer keeps tile and pixel coordinates live across
text lookup. The new handoff similarly preserves point/index and departure-X
producer order. The panel's conditional palette initializer consumes its
actual enabled-byte test before choosing the default colour.

The separate interface checks compile the complete definitions of twenty
accepted direct callees and the assigned object callback, totaling 2,292 bytes.
Exact caller declarations remain compatible; 21 deliberate wrong declarations
are rejected by the target compiler. All four new bodies also match with exact
map, clock, timer and callback type checks. Four same-layout wrong-type cases
reject without relying on a changed physical size.

Finite evidence remains the historical 708-byte update qualification, not a
new semantic qualification of the 804-byte batch. It uses 871 initialized
fixtures across three seeds and six separate sequences, with twenty chosen
service abstractions. The original Thumb extent, statement model and host
surrogate of the actual source agree under their shared assumptions. These
models are corroboration, not independent oracles. The changed final request
diverges in 24 executions; nineteen execution guards and ten evidence-corruption
controls pass. Converted helper interiors are not silently included.

Defined connected inputs require initialized live owners, player indices 0–3,
valid object/save slots, representable signed arithmetic and the stated provider
contracts. Original background-map and text-render services remain boundaries.
Shutdown's transition kind 12 still selects an original-ROM callback. The new
static and compiler proofs do not establish those bodies, all provider effects,
hardware behaviour or complete phase-seven gameplay.

The [whole-ROM survey](WHOLE_ROM_INVENTORY.md) keeps mapping, instruction evidence
and source coverage separate. Its fixed historical comparison remains 319,640
mapped extent bytes; a complete game-code denominator remains open.
