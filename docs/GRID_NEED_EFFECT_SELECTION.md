# Grid selection, interaction and scene actor schedule

This connected batch reconstructs twelve ordinary C functions covering 1,060
bytes. Full extents, literal pools and alignment are compared at their original
ROM addresses, with changed-source controls for every function. The names and
partial types describe observed accesses and calls; they do not establish
runtime or gameplay behaviour.

| Address | Bytes | Function |
| --- | ---: | --- |
| `0x0803C598` | 112 | `frame_step_local_need_effect_selection` |
| `0x0803C958` | 200 | `frame_grid_selection_interact` |
| `0x0803CA20` | 76 | `frame_grid_selection_mark_attachments` |
| `0x0802E068` | 80 | `frame_need_effect_begin_choices` |
| `0x0802E0F0` | 84 | `frame_need_effect_cycle_mode` |
| `0x0802EC04` | 20 | `frame_need_effect_mark_attachment_running` |
| `0x0802CB0C` | 252 | `frame_refresh_scene_actor_schedule` |
| `0x0802CD90` | 44 | `frame_reset_scene_actor_schedule` |
| `0x0802CDBC` | 28 | `frame_actor_note_spawn` |
| `0x0802CDD8` | 28 | `frame_actor_note_remove` |
| `0x0802CDF4` | 12 | `frame_set_scene_actor_eligibility` |
| `0x0802CE00` | 124 | `frame_scene_actor_find_exit` |

The primary scene step calls the local-selection coordinator. It clears the
selected object at `0x03002170`, captures the local actor from a 12-byte row of
`g_input_config`, advances the clock from an eight-byte record at `0x0807F4B0`,
resets the need-step mode, updates actor routes and the actor schedule, updates
need 7, then calls selection, interaction and attachment marking in that order.
The explicit address calculation captures the observed row stride without
claiming a complete input-state layout or a bound on the time-step selector.

The 720-byte controller at `0x0803C688` remains unconverted. A retained private
candidate has its complete 720-byte extent but still differs from the original;
it contributes no coverage. Its static calls connect the published occupancy,
candidate membership and coordinate helpers with the selected-row predicate,
selector display and these interaction consumers. The separate 356-byte target
selector and 88-byte inverse transform also remain explicit unconverted targets.

## Input and attachment handoff

The interaction function requires a selected object, actor state 16, a variant
other than 52 or 53, a zero tick word in the player's 56-byte transition row and
a zero game-state byte at `+0x42E`. Pressed bit 1 begins choices; only a successful
result clears input and stops the actor at its current position. Pressed bit
`0x100` cycles the selected object's mode when the observed world predicate
returns 1, and chooses animation cue 16 on success or cue 3 otherwise. The three
original cue calls remain distinct. A named word mask before the AND preserves
the original mask lifetime without register bindings.

Choice activation accesses an owner pointer at object `+0x64`, writes the
participating actor at `+0x68` and sets phase byte `+0x81` to 1. It calls the
owner's check callback at `+0xE4` and the existing choice builder, requiring a
byte result of 1 from both, then sets actor state 0 and variant 7. The callback's
complete target set is unresolved. Its original Thumb indirect-call veneer is
an external dependency, not new C or assembly coverage.

Mode cycling rejects subtype 82, increments and narrows the current mode byte
at owner-state `+0x5F`, resets values above 5 to zero and retains the original
changed-value guard. It acquires the palette slot from the established
24-byte-stride actor palette table. No extra actor-id or mode guard is added.

Pressed bit 2 visits the actor's two attachment pointers at `+0x138/+0x13C`.
For a nonnull owner, the accepted lookup locates the attachment record and the
new 20-byte wrapper sets its running byte at `+0x0C` to 1. Two slots are observed
in this caller; this does not establish a global bound on every attachment view.

## Actor schedule and presence storage

The reset function clears 24 bytes at `0x03001E10`, sets the signed timer at
`0x03001E28` to 300 and enables the byte at `0x03001E2C`. Its original scene-load
caller now uses the canonical reset name. The resource command's old
`resource_prepare_display` alias names the byte enable setter; its two other
parameters still activate resource groups. The setter stores only the low byte.
Several incoming widths compile to the same 12 bytes, so its retained byte
formal reflects the known command caller rather than unique ABI proof.

The constructor/removal handoff writes presence `[id - 18]` to 1 or 0 when the
full word id is greater than 17. There is no upper-id check in either function.
Their previously provisional halfword formals are corrected to full words:
word-formal C matches all 28 bytes, while byte and halfword formals emit extra
incoming narrowing and fail. The existing constructor/removal callers load
halfword ids; their current source bytes and actual controls are reverified.
A 24-byte reset and a bounded scheduler scan do not establish a bound for these
unchecked writers.

When enabled, the scheduler decrements the signed timer and acts only when it
becomes -1. It scans byte ids 18 through 41, skips id 31 when condition `(4,4,2)`
is complete, and compares the accepted time/world eligibility result with
presence. A no-longer-allowed actor found as object id 7 and matching subtype is
marked `0x800000` and given the selected marker position as its destination.
A newly allowed actor is created at the first id-15/subtype-0 marker when a
palette slot is available. The scheduler stops after a handled removal or spawn
and resets the timer to 300; a completed unchanged scan resets it too.

The marker helper collects at most five id-15/subtype-0 objects through the
accepted finder. With a nonzero count, it keeps the strictly smallest unsigned
point-distance below `0x27100000`, starting with selected index zero, and copies
the selected position as a complete `FramePoint`. Thus all distances above the
initial threshold still choose marker zero. The inferred exit-marker name comes
from its sole inspected caller assigning an actor's departing destination; the
marker role and coordinate units are not runtime-proven.

The whole `FramePoint` destination copy is causal compiler evidence: replacing
it with separate x/y writes changes register lifetimes and fails matching.
An early no-markers return similarly preserves the original helper branch and
pool layout. Both functions use ordinary C without register constraints.

## Verification limits and next boundary

All twelve functions have real source edits that reject exact matching. Shared
prototype and alias consumers are recompiled with their individual controls,
including the existing scene initializer, resource command and actor lifecycle
callers. Necessary zero tail alignment is explicit; no instruction bodies,
output repairs, masks or copied tables are embedded in these sources.

Raw originals, full comparison bytes, compiler assembly, failed width, aggregate
and control-flow attempts and accepted-source negative controls remain in ignored
local reports. Static map connectivity, exact compiler bytes and runtime behaviour
are separate claims. The next useful closure is the central selection controller,
its inverse-coordinate dependency and the original selector's target-choice loop.
