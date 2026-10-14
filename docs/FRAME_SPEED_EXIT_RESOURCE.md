# Factory slot 13 and condition-row exit state

Two connected matching C extents add 252 bytes. Factory slot 13 gates the
already recovered speed-exit actor constructor using the current world and
shared exit flag. The accepted condition-row controller calls the recovered
scene refresh helper, which clears that same flag and sets three observed
world/position outcomes. Names describe these accesses and remain provisional;
no gameplay run is claimed.

| Function | ROM offset | Full extent |
|---|---:|---:|
| `condition_refresh_scene` | `0x38254` | 176 |
| `frame_create_speed_exit_resource` | `0x38304` | 76 |

Both extents include their complete pools and original internal alignment.
The helper ends exactly at the factory entry; the factory ends at the already
accepted save-world-field reader at `0x38350`. The compiler naturally produces
the complete boundaries, so neither new source needs an assembly alignment
directive. There is no new low-level glue or assembly C credit.

## Factory and shared state

The factory table at `0x4F278`, slot 13 at `0x4F2AC`, contains `0x08038305`.
The new factory uses the existing two-byte `ResourceObjectFactory` contract.
World byte `+42C` must equal 50 and exit flag byte `+42E` must differ from one.
Otherwise it returns null without reading a payload or calling the actor
constructor. On success it obtains the payload, reads signed coordinate
halfwords at four and six and the direction byte at eight, and returns the
existing actor constructor's result.

Observed accesses extend through byte eight; the first four bytes remain
uninterpreted, rather than being named as an unread ID word. The read view is
`packed, aligned(2)`, with compiler size ten and field offsets 4/6/8. It supports
the actual halfword loads without requiring an otherwise unsupported four-byte
alignment. Its rounded size is not a complete serialized-record capacity claim.
The former default-aligned view still produced identical instructions; separate
compiler layout diagnostics reject it. Coordinates multiply signed halfwords
by 65,536, with every possible product fitting a target signed word.

The helper retains the full-word argument consumed by the existing
`condition_select_row` declaration. Rows zero and one do nothing. Higher rows
clear the exit flag, including values outside the three recognized cases. Rows
two, three and four additionally write the following world and fixed-point
position values:

| Row | World byte | X word | Y word |
|---:|---:|---:|---:|
| 2 | 4 | `0x04300000` | `0x02F10000` |
| 3 | 14 | `0x02DF0000` | `0x00FF0000` |
| 4 | 9 | `0x04B10000` | `0x02220000` |

These are observed assignments, not identified map destinations or validated
gameplay states. The existing `FrameActorSpeedGame` view supplies the saved
point at `+424`, world byte at `+42C` and exit flag at `+42E`; its pinned compiler
size/alignment is 1,072/4. No shared game-state layout is changed. An initial
six-byte mismatch came entirely from loading the world root before the row
guard. Starting that real pointer's lifetime inside its consuming branch
recovers the native ordering without extra traffic or register binding.

## Existing actor and collision handoff

The actor constructor at `0x38090` and its tick, paired interaction and transition
callbacks remain the already accepted 604-byte path. They earn no new C credit.
The actor uses subtype/ID 13, payload direction and coordinates, the saved
palette, fixed animation variants and its existing update path. Interaction can
put it in state four; its transition handles the scene result and can set the
exit flag before requesting removal. This is static connected routing, with
pointer validity and gameplay timing unproved.

The copied collision caller supplies both objects in R0/R1 and invokes the
concrete callback at `+CC`. The speed-exit role and function now use its actual
`CollisionCallback(CollisionObject *, CollisionObject *)` contract. Inside the
existing 120-byte callback, explicit `FrameObject *` aliases supply its existing
access views; no function-pointer cast is introduced. The word at `+C8` remains
scratch and the callback pointer stays at `+CC` in the same 208/4 partial role.
The generic actor's separate one-argument interaction view remains provisional
and unchanged.

This interface correction adds zero C bytes. All four accepted importers of
`frame_actor_speed_exit.h` retain identical bytes and their genuine controls.
Compiler assignments check the concrete function, canonical collision callback
and role field in both directions. Restoring either older incompatible type
rejects under strict diagnostics. Provider addresses, callback data, body logic
and existing controls remain unchanged.

## Verification limits

The two new bodies contain no register bindings, volatile accesses, dummy
initializers, output patches or instruction transcription. Fresh full-extent
positives and changed-source controls are retained, along with separate strict
diagnostic profiles. Current accepted callers, providers and the complete
four-function changed-header importer closure are reverified. The declaration
and physical-layout checks remain separate from byte equality.

The compiler diagnostics check 26 layout facts and three new API assignments,
including the halfword-aligned payload, unchanged game-state fields and full-word
scene-refresh argument. Wrong field widths, offsets and callback/factory types
are rejected. Removing the real actor-constructor declaration still matches
the permissive legacy bytes, but strict diagnostics reject it. The callback
correction has four further layout checks and three type assignments with
independent old-type failure cases.

Seventy-two finite initialized factory/helper cases agree with original bytes
and an independent branch model; changed-source controls diverge in 44 cases.
They check all gate outcomes, coordinate extremes, pointer returns, the three
position assignments and unknown full-word row values. The payload fixture is
deliberately two-byte aligned. Higher factory argument bits and wide row values
are ABI-only cases; arbitrary resource indices, table capacity and gameplay
validity are not established. Existing provider effects are abstracted, including
an injected null actor result; their bodies are not exercised by those fixtures.
Five model failure controls reject malformed code or unmapped inputs. Whole-ROM
equality is verified separately at integration and publication.
