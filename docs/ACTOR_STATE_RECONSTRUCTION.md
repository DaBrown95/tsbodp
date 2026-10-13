# Actor state dispatch and connected handoffs

This batch reconstructs 116 C functions spanning 20,792 verified bytes. The
names describe static accesses and call relationships; selector-derived handler
names deliberately preserve uncertainty about gameplay roles. Each complete
extent, including pools and zero alignment, matches its fixed ROM address. Real
source mutations fail the same comparison. This is source reconstruction evidence;
no runtime or gameplay test is claimed here.

| ROM offset | C function | Verified bytes |
| --- | --- | ---: |
| `0x3BB28` | `frame_grid_neighbor` | 88 |
| `0x3BB80` | `frame_grid_cell_data_pointer` | 36 |
| `0x2E56C` | `frame_actor_owner_cell_count` | 128 |
| `0x6874` | `frame_actor_state_46` | 468 |
| `0x9E40` | `frame_actor_state_31_32_33` | 364 |
| `0xA030` | `frame_find_pending_action` | 116 |
| `0xA1C8` | `frame_actor_show_action_failure` | 144 |
| `0x2E0B8` | `frame_actor_use_target` | 56 |
| `0x8CFC` | `frame_actor_route_to_target` | 124 |
| `0x166C` | `frame_attach_actor` | 76 |
| `0x16B8` | `frame_detach_actor` | 36 |
| `0x1A64` | `frame_count_actor_attachments` | 40 |
| `0x5B00` | `frame_actor_state_17` | 160 |
| `0x8504` | `frame_actor_state_39` | 188 |
| `0x2EE78` | `frame_finish_actor_attachment` | 64 |
| `0x2E41C` | `frame_actor_attachment_status` | 176 |
| `0x38090` | `frame_create_speed_exit_actor` | 216 |
| `0x3845C` | `frame_speed_exit_tick` | 32 |
| `0x3847C` | `frame_speed_exit_interact` | 120 |
| `0x38168` | `frame_speed_exit_transition` | 236 |
| `0x97D8` | `frame_actor_state_27` | 1,116 |
| `0x9C34` | `frame_actor_acceleration_velocity` | 316 |
| `0x9D70` | `frame_actor_play_speed_cue` | 44 |
| `0x9D9C` | `frame_actor_set_speed_cue` | 84 |
| `0x1C48` | `frame_set_actor_turn_direction` | 32 |
| `0x8050` | `frame_actor_state_28` | 56 |
| `0x2C618` | `frame_spawn_counter_effect` | 152 |
| `0x3054C` | `frame_create_transient_effect` | 152 |
| `0x31038` | `frame_destroy_transient_effect` | 36 |
| `0x24D50` | `frame_pool_allocate_08024d50` | 52 |
| `0x24D84` | `frame_pool_release` | 28 |
| `0x24DA0` | `frame_pool_pop` | 32 |
| `0x24DC0` | `frame_pool_push` | 24 |
| `0x24DD8` | `frame_pool_remove` | 44 |
| `0x85C0` | `frame_actor_state_8` | 256 |
| `0x86C0` | `frame_actor_state_9` | 368 |
| `0x66F4` | `frame_actor_terrain_step` | 236 |
| `0x8B30` | `frame_actor_follow_target` | 188 |
| `0x5CA4` | `frame_actor_state_16` | 1,420 |
| `0x7F88` | `frame_actor_input_velocity` | 116 |
| `0x1BC8C` | `frame_reduce_actor_scene_counter` | 68 |
| `0x1BCEC` | `frame_add_actor_scene_counter_rate` | 44 |
| `0x269F4` | `frame_world_in_idle_exclusion_set` | 168 |
| `0x3C608` | `frame_set_actor_need_step_mode` | 12 |
| `0x302AC` | `frame_get_actor_palette_slot` | 8 |
| `0x3840C` | `frame_cycle_idle_actor_palette` | 80 |
| `0x8464` | `frame_actor_state_13` | 160 |
| `0x7D7C` | `frame_actor_step_wait_phase` | 68 |
| `0x8D78` | `frame_actor_face_destination` | 52 |
| `0x8DAC` | `frame_set_actor_destination` | 16 |
| `0x1B4A4` | `frame_create_actor_effect` | 288 |
| `0x1B5C4` | `frame_actor_effect_tick` | 108 |
| `0x8088` | `frame_actor_state_43` | 96 |
| `0x7C0C` | `frame_actor_state_47` | 264 |
| `0x7900` | `frame_actor_state_42` | 780 |
| `0x6A48` | `frame_actor_state_19` | 292 |
| `0x8294` | `frame_find_actor_action` | 40 |
| `0x8228` | `frame_note_actor_action` | 108 |
| `0x1BC1C` | `frame_add_game_value` | 76 |
| `0x3D0E8` | `frame_advance_parameter_level` | 136 |
| `0x7584` | `frame_actor_state_41` | 892 |
| `0x41424` | `audio_play_sequence_notification` | 72 |
| `0x6B6C` | `frame_actor_state_22` | 628 |
| `0x8158` | `frame_note_interaction_condition` | 108 |
| `0x5804` | `frame_run_actor_state` | 468 |
| `0x7FFC` | `frame_actor_state_23` | 84 |
| `0x80E8` | `frame_actor_state_25` | 112 |
| `0x81C4` | `frame_actor_state_40` | 100 |
| `0x8364` | `frame_actor_state_7` | 256 |
| `0x6DE0` | `frame_actor_state_26` | 320 |
| `0x1C28` | `frame_set_actor_direction` | 32 |
| `0xAF60` | `resource_group_point_count` | 24 |
| `0xAF78` | `resource_read_group_point` | 48 |
| `0x7030` | `frame_actor_state_34` | 176 |
| `0x5BA0` | `frame_actor_state_24` | 260 |
| `0x6230` | `frame_actor_state_35` | 1,220 |
| `0x8994` | `frame_actor_choose_walk_direction` | 412 |
| `0x8BEC` | `frame_actor_direction_available` | 232 |
| `0x188C` | `frame_direction_toward` | 60 |
| `0x273A0` | `frame_add_points` | 24 |
| `0x273DC` | `frame_point_to_integer` | 16 |
| `0x273EC` | `frame_point_to_fixed` | 16 |
| `0x1BD4` | `frame_clear_animation_pending` | 12 |
| `0x7480` | `frame_actor_state_45` | 260 |
| `0x3A614` | `frame_find_scene_target` | 52 |
| `0x370D0` | `frame_begin_actor_route` | 228 |
| `0x37464` | `frame_cancel_actor_route` | 52 |
| `0x37498` | `frame_route_enable_destination` | 60 |
| `0x374D4` | `frame_route_set_limit` | 60 |
| `0x37510` | `frame_release_actor_route` | 88 |
| `0x1A08` | `frame_direction_to_destination` | 92 |
| `0x37028` | `frame_update_actor_routes` | 168 |
| `0x371B4` | `frame_steer_actor_route` | 156 |
| `0x37250` | `frame_find_actor_route` | 292 |
| `0x37374` | `frame_follow_actor_route` | 208 |
| `0x37444` | `frame_reset_actor_routes` | 32 |
| `0x37568` | `frame_finish_actor_route` | 28 |
| `0x3C0D8` | `frame_grid_search_status` | 20 |
| `0x1C68` | `frame_enable_object_flags` | 8 |
| `0x1C70` | `frame_disable_object_flags` | 8 |
| `0x59D8` | `frame_actor_state_37` | 144 |
| `0x5A68` | `frame_actor_state_38` | 152 |
| `0x1BC74` | `frame_advance_actor_scene_counter` | 24 |
| `0x34B8C` | `frame_activate_actor_scene_request` | 44 |
| `0x27EE4` | `frame_create_scene_object` | 240 |
| `0x1128` | `frame_allocate_scene_object` | 64 |
| `0x8830` | `frame_actor_state_44` | 356 |
| `0x27FD4` | `frame_scene_object_tick` | 608 |
| `0x3400` | `frame_step_position_move` | 160 |
| `0x34A0` | `frame_begin_position_move` | 56 |
| `0x4533C` | `frame_set_centered_integer_position` | 28 |
| `0x14B0` | `frame_set_velocity` | 8 |
| `0x70E0` | `frame_actor_state_36` | 928 |
| `0x2B9A0` | `frame_actor_need_value` | 8 |
| `0x3D1F4` | `frame_read_signed_parameter` | 12 |
| `0x2B3D4` | `frame_actor_refresh_terrain` | 92 |

## Dispatch evidence

The published actor tick and resource-driven actor callback call `0x5804`. The
callee switches on the actor byte at `+0x4D`, bounds it by 47 and uses a 48-entry
word table at `0x5820`. The table resolves all transfers; states 31, 32 and 33
share one callee. The other direct calls identify 28 further callee entries.
State 1 clears flags bit 0 and sets `0x82`. States 0, 2–6, 10–12, 14–15, 18,
20–21 and 29–30 perform no action; values above 47 also return.

The no-op case 0 remains explicit in C: removing it makes the compiler build a
47-entry table with a subtract-one index. The retained failed candidate differs
in the dispatcher prefix/table. State 37 and state 38 call handlers without an
actor argument; inspection of both callees confirms they access global game
state and do not consume the incoming actor. Their scene handoff bodies now match; the broader scene request and
pool and broader scene request paths remain partly unconverted.

The C case order follows the observed block layout. It does not contain original
instructions or table bytes. The only assembly directive emits zero tail
alignment, as in other accepted Thumb functions.

## Connected behavior and data views

State 23 requests animation 5, sets the `+0x4E` substate to 19, and waits for
flags `0x400000` before requesting animation 1 and restoring the actor's default
state. State 25 waits for the same completion bit, requests animation 90 and
cue 161, then moves the first view's actor to state 37 and plays cue 27. Before
completion, frame byte `+0xDB == 15` triggers cue 78. These call the already
reconstructed animation and game-audio paths.

State 40 stores the cue-46 sample handle at `+0x68`, requests animation 68, and
starts a signed 60-frame countdown at `+0x58`. When decrement reaches -1, it
stops that handle, requests animation 69 and selects state 47. The integer
sample handle agrees with the canonical game-audio stop-sample API.

States 7 and 26 read waypoint-group/index bytes at `+0x64/+0x65`. Resource data
is reached through the pointer at `0x03002EE0`: a halfword offset table begins
at data `+2`; each selected group has a byte count and records beginning at
`+4`, with stride eight. Records begin with two signed halfword coordinates.
The coordinate reader returns a two-word point by value. Its hidden aggregate
return pointer explains both caller argument placement and the callee preserving
R0 through its return sequence. A void output-pointer trial differed at that
return sequence and is retained.

The waypoint handlers shift the returned coordinates left by 16 and pass the
point to the route initializer at `0x370D0`. A result word at actor
`+0x54` records route status; the unsigned branch in state 34 establishes its
unsigned view. The timer at `+0x58` is signed and expires at -1. A byte at `+0x66`
sets wait duration in units of 30 frames. The names in `FrameActorStateWork`
apply to these selectors; other actor overlays reuse these addresses.

State 7 chooses a waypoint different from the previous index, starts a route
with argument 3 and cycles through walking/waiting substates. State 26 starts
with route argument 0, waits and then asks the unconverted `0x6F20` selector for
a need-related target/action; the selected action is attempted by `0x2E0B8`.
State 34 obtains the first primary-list object with ID 15 as a scene target
from `0x3A614`, starts a route and branches on
route results 1/2/3 before advancing into state 43. These names are provisional;
there is no claim that the route and target subsystems are fully reconstructed.

State 24 alternates walking and waiting, choosing directions through `0x8994`
and an eight-direction table at `0x52880`. Its signed timer uses 90- and
300-frame periods. The halfword at `+0xAC` also redirects walking into waiting;
`contact` is a provisional name for this field. At wait expiry it attempts the
same need target/action handoff as state 26, or resumes wandering.

State 35 has a 62-entry table at `0x6250`, indexed by substate minus two. Its
eight active selectors are 2, 7, 25, 41, 45, 61, 62 and 63. Other entries share
the return block. It initializes a random waiting period, tries a destination
route when flags `0x800000` permit, and makes probabilistic interaction attempts
based on subtype, world ID and a game-state byte at `+0x0A`. Coordinate bounds
select two world-specific stationary animations. If no action succeeds, it
chooses between a need target and renewed wandering. Movement result, animation
completion, contact halfword and timer then drive its remaining substates.
The game-state byte is called `clock` only provisionally; its real temporal or
quest meaning is not established. The canonical game-state global is reused
through a bounded overlay, and the published main actor layout is unchanged.

The movement-direction chooser reads actor `+0xC4` as a cell argument and uses
the shared registration/context pointer at `0x03004330`. It first tests two
successive neighboring cells, requiring classification bit 2 and no bits from
mask `0x3D`; its second pass tests one neighbor. It advances direction by two
and wraps values above eight, remembering the initial direction to bound each
loop. The actor-specific availability check at `0x8BEC` determines success.
The chooser keeps both fallback directions and returns a byte success value.
These call shapes and tests support its name more closely than the earlier
need-selector context alias `frame_actor_need_bit2_effect`; helper and bit
meanings remain provisional. It is natural C without fixed register variables.

The direction setter narrows its input to one byte, compares/stores `+0x12`
and sets pending-update bit `0x10` only when direction changes. It connects
these route handlers to the accepted animation/direction refresh path.

The two waypoint resource readers use fixed C register variables for the byte
offset and offset-table address. These constrain compiler allocation; the
expressions remain typed pointer/record operations, and no instruction body is
embedded. Their first natural C candidates and subsequent raw mismatches remain
local. The full extent and changed-source controls verify these constraints.

The availability check first predicts the actor's next position using its speed
and selected direction. It probes that position with three successive direction
vectors of length `0x40000`, converts the resulting point to integer coordinates
and asks the shared grid context for a cell. A changed low-halfword cell identifier
must have classification bit 2 and no occupancy bits in `0x3D`. The upper halfword
is retained as unknown, and these bit meanings remain provisional. Two fixed C
register variables constrain the loaded cell identifiers to R0/R2 before applying
a local `0xFFFF` mask. The complete 232-byte proof includes both mask loads, its
literal pool and zero tail alignment; a plain integer-cell trial, short-field and
bitfield variants, and failed allocation trials remain local. The bindings are
compiler constraints and do not establish runtime behavior.

`frame_direction_toward` converts two actors' fixed-point positions to signed
integer points and passes their difference to the accepted eight-direction
classifier. The conversion helpers read signed high halfwords or shift integer
coordinates left by 16. `frame_add_points` adds both coordinates. State 45 makes
two actors face each other and stops their motion, then coordinates animations
40/43, completion flags, cues 228/229, and a 90-frame countdown before selecting
state 37. The repeated motion-stop calls remain explicit because they are present
in the original control flow; their broader gameplay reason is uncertain.

The route handoff uses three 280-byte jobs at `0x03005A30`, with its active count
byte at `0x03005A20`. Each job stores its actor, destination, two delta words,
a status-word pointer, a word mode and saved flags mask `0x10240`. Its final bytes
at `+0x114..+0x117` store a limit, style, destination-use flag and an unknown byte.
The route path occupies `+0x20..+0x10F` as 30 two-word integer points; a
path-index byte follows at `+0x110`, with three unspecified bytes after it. Beginning a route
chooses the first free job, initializes those fields, enables actor flag
`0x1000000`, sets the caller's status to 2 and increments the count. It returns
zero when all three slots are occupied. The fourth parameter is a full word and
the fifth is narrowed to an unsigned byte; all published constant-argument
callers still match after this prototype refinement. The limit setter also
narrows its input to a byte. Both setters stop after their first matching actor.
Cancel checks all slots; release clears the route flag, reapplies the saved flag
mask, resets the status word, clears all 280 job bytes and decrements the count.
The eight-entry mode table at `0x08D71FE4` resolves the indirect transfer in
`frame_update_actor_routes`: modes 0/5 call path search, 2/3/4 steering, 6 path
following and 1 final positioning; mode 7 has no callback. Each descriptor also
provides a next-mode word. The update loop processes occupied slots, releases
jobs when the caller status leaves 2/3, and writes callback results back through
the status pointer. Its observed actor-flags-bit-2 branch releases a job and
then continues reading its cleared status pointer. That branch remains explicit
in C; static matching does not prove whether it can occur during gameplay.

The destination-direction helper compares each coordinate against destination
plus/minus speed tolerance, returning one of eight directions or 8 for arrival.
Steering handles arrival/style, contact and descriptor-driven next mode, then
updates the actor's direction/velocity and records its previous position. Path
search clears actor flag `0x10000`, converts start/destination points to packed
grid cells, and calls the still-unconverted grid search at `0x3BCF4`. The search
status accessor reads byte `+0x199` of the shared state at `0x03001FD0`; its return
is a full word even though that storage is one byte. Different search results
select path following, arrival handling or descriptor fallback. A flag at job
`+0x117` records one status-2 destination fallback and alters later completion
reporting; its broader route meaning is provisional.

Path following advances the path index when a point is reached. The first pair
of zero coordinates terminates the path; style 1 selects another steering mode,
and other styles return completion. Contact returns status 3. Final positioning
sets the actor to the original destination and stops motion. Reset clears the
active count and all three jobs. The flag helpers are semantic OR/AND updates
called by beginning, searching and releasing routes. The core grid search and
reverse-order path extraction at `0x3C08C` remain unconverted; bounded candidate
proofs do not make those algorithms reconstructed.

State 37 reads the global timer at game state `+0x74C`. Values above -2 submit
scene request 37 with mode byte 0. Otherwise, stage word `+0x440` selects request
28 or 36, sets ready byte `+0x750`, and sets mode byte 1 or 2. The latter branch
increments the halfword counter at `+0x744` by 20. All branches reset the actor
needs block at game state `+0xB0` through the already reconstructed need reset.
State 38 either submits request 37 with a 360-frame timer or creates a scene
object with ID 193, subtype 244, palette 15 and layer 0. The variant byte at
`+0x749` selects result halfword 304/305 at `0x030059F0`. A bounded record view
for that halfword matches the original compiler allocation; a scalar halfword
view emitted an extra move. This supports a field view, while the full record's
extent and broader result meaning remain uncertain.

The scene request at `0x03005A00` has an active byte at `+4` and an object pointer
at `+8`. Activation sets that byte, sets object flag `0x200000`, clears flag 1,
and calls scene stage 2. The factory allocates a 320-byte object, sets its ID,
subtype, flags, display layer/palette and callback, and positions it using an
8-byte signed-coordinate descriptor at `0x08057ACC`. It selects a 16-byte
animation record from `0x08058154`; subtype 267 instead loads a palette and
optionally installs special command streams for IDs 110/111. The allocation
wrapper calls the still-unconverted pool operation at `0x24D50`, initializes
ID and display-index halfwords to `0xFFFF`, and fills the list tail if empty.
The pool operation, descriptor arrays and command streams remain explicit
original regions; reconstructing the factory does not establish the pool
algorithm or asset contents.

The scene object's callback handles outer states 14 and 8. State 14 bounds
its substate by 58 and uses a 59-entry table at `0x28004`: substate 0 sets the
first descriptor position, 58 sets the second, 56/57 move between those positions,
and 3 advances a pending move. All other table slots return. The explicit empty
C cases retain that table's range and compiler form; the source contains neither
original table words nor instruction bodies. State 8 sets substate 11 when its
current substate is zero. Subtype 315 uses a centered integer position that
subtracts half the display width at `+0xD8`; other subtypes use fixed-point
coordinates directly. The move setup stores destination words at `+0x38/+0x3C`
and narrows duration to the halfword at `+0x5E`.

Move stepping decrements that halfword, computes absolute coordinate differences
and signed byte directions, and either snaps both coordinates when each remaining
difference is below one integer pixel or divides the differences by the remaining
timer through the unconverted BIOS division veneer. It sets the resulting
velocity; a separate accepted setter writes the two velocity words. No new
zero-duration guard is invented. The original path can pass zero to the division
veneer, and matching alone does not establish whether callers avoid that state.
The six decoded bytes of the setter have two original zero tail bytes before
the next entry; the source emits explicit zero alignment for the full 8-byte
extent. The callback and these helpers are ordinary C except for that alignment.

State 44 uses the selected local view's actor and fixed-point distance to switch
between proximity movement and timed random turns. Entry/exit distances are
halfwords at `+0x6A`/`+0x68`; turn/wait bounds are at `+0x6C`/`+0x6E`. Entering
substate 4 saves and doubles speed, plays cue 179 and chooses a random direction.
Leaving it restores speed and switches to substate 7. Substates 3/7 alternate
on an unsigned halfword countdown reaching `0xFFFF`. Two short-lived distance
results use C register bindings to retain the original allocation; these emit
no instruction bodies and are compiler constraints, not runtime evidence.
Numeric handler names retain uncertainty about the gameplay entity involved.

State 36 joins the first view's actor with two value checks before dispatching
substates 2 through 44 through a 43-entry table at `0x712C`. Its work at `+0x58`
contains a signed countdown, followed by cue-count and cue-timer halfwords at
`+0x5C/+0x5E`. It chooses waiting or walking, turns toward the view actor, reacts
to contact and coordinates paired animations 40–43. One branch activates
condition triple `(3,4,2)` through the accepted condition path. Audio cues 227,
228 and 229 follow the observed cue counter and animation completions. The final
wait can select state 37 on the view actor, closing the scene handoff reached
by states 25 and 45. Repeated motion-stop calls and zeroing both cue fields are
retained as observed; no gameplay purpose is asserted beyond these static steps.

The probe block at `0x030039E8` aliases game state `+0x98`. The generic signed
reader at `0x3D1F4` returns a sign-extended byte at `index*4+3`. State 36 compares
that return as an unsigned word against 5, preserving the original unsigned
branch even for a negative byte. Its need check uses the unsigned reader at
`0x2B9A0`, which reads the high byte of the accepted need values with 24 fractional
bits. The signed parameter block's broader domain is unspecified. Both reader
functions use integer-address accumulation to retain the original addition
register; they contain no embedded instructions.

Terrain refresh converts the actor's next-position coordinates to signed integer
components, then calls the still-unconverted `0x2ABB0` classifier using a two-word
point by value. That inferred point prototype matches the caller; the two scalar
prototype candidate differs in its first address-register allocation. The
classifier result is stored at actor byte `+0x85`. Class 1 enables flags bit
`0x4000`, and other classes clear it; the accepted velocity refresh runs only
when that bit changes. The velocity builder already uses this bit to select its
restricted direction table. Specific terrain labels and the classifier's packed
edge records remain provisional and unconverted.

State 22 connects the accepted input direction and pressed-key arrays to a need
effect interaction. Its selector-specific work stores the effect object at
`+0x64`, a mode byte at `+0x68` and an option index at `+0x6C`. Substate 0
requests animation 49, optionally constructs the effect from a four-byte option
record, enables its flags and hands it to the unconverted interaction controller.
Substate 18 cancels on key bit 2 or empty-need mask `0x25`; key bit 1 confirms.
The confirm path calls the accepted world-condition helper, records selected
worlds for IDs 195 through 200, and uses the word at `+0x0C` in a 24-byte action
definition to select animation 67 / substate 74. Direction selection enters
substate 11 until the input returns to direction 8. All completion paths reset
the outer state to 16; the normal completion requests animation 1 / substate 2.

The option list pointer at game state `+0xF0` aliases local need state
`0x03003A00 + 0x40`; its record pointer is at list `+4`. The selected-world byte
is at local need state `+0x38C`. These are bounded overlays of observed accesses,
not claims about the full owning structures. A word-width player local preserves
the original narrowed input handoff, and sharing the option-record pointer local
between initialization and confirmation preserves the original register choice.
The complete 628-byte match uses ordinary C without register constraints.

`frame_note_interaction_condition` only acts in worlds 16 and 17: action IDs 30,
49, 4, 63 and 54 activate triples `(0,2,0)` through `(0,2,4)`, while ID 109
activates `(1,1,2)`. This name follows the observed condition updates. The
interaction begin/cancel/confirm/step/select/idle bodies at `0x2F4EC` through
`0x2F8FC` remain unconverted and retain address-based provisional names.

State 19 connects timed or animation-complete actions to need adjustment and
scene notification. Its twelve-byte action descriptors at `0x0804EDA0` contain
a word ID, a duration halfword, animation/substate bytes and two need-adjustment
bytes. The lookup checks 36 records and returns a signed byte index or `-1`;
the caller deliberately narrows that result to an unsigned byte, with no added
missing-ID guard. Work fields are a countdown at `+0x58`, action ID/variation at
`+0x64/+0x66` and a sample handle at `+0x68`. Action 170 offsets the descriptor
index by the variation byte. Substates 59 and 60 apply the descriptor's need
adjustment until countdown or animation completion; completion stops the saved
sample and returns to outer state 16 / substate 2. Descriptor index 21 also
writes scene-result ID `0x1639` and activates the accepted scene request.

The action notification narrows its ID to a halfword. ID 209 adds 5,000 to the
signed word at game state `+4`; its helper clamps that word to 0 through 999,999,
marks bit 2 in the selected local view's 56-byte display flags and returns the
stored value. Its gameplay unit remains provisional. IDs 211 through 216 map
to parameter indices 5, 0, 1, 3, 4 and 2 in the probe block. Parameter advancement
adds `0x01000000` only when the old unsigned high byte is at most 9. A signed
high-byte increase resets the lower 24 bits and calls the already-published
`condition_finish_actor_context` with context base `0x03003960`, then prepares
text notification ID `0x123`. Width and height measurements place its byte
coordinates at scene request `+1/+2` before display stage 2 and sequence 56.
The context overlaps game state `+0x10` and its counters overlap the probe
block at `+0x98`; these views do not establish complete allocation extents.

`audio_play_sequence_notification` gates playback on the nonzero sequences
volume byte, sets bit `0x80` in the volatile audio-control byte at `+6`, reads
the sequence pointer at descriptor offset 0 and parameter byte at offset 5,
starts it with mode argument 4 and synchronizes the game audio state. The mode's
precise playback meaning remains uncertain. A C register binding for the
32-bit descriptor parameter retains the original temporary register; this is
a compiler constraint and contains no instruction assembly. The full 72-byte
extent and a changed mode argument pass their positive/rejection comparisons.

State 41 uses the first view's actor and a full 65-entry substate table. It
connects wandering and accepted route outcomes to terrain refresh, paired
animations 70 and 93–95, the view actor's indicator and an outer-state-47 handoff.
An expired waiting phase selects a new walk direction even after switching back
to substate 7; the shared random-delay tail establishes this otherwise easy-to-
miss call. All no-op table entries remain explicit. Its call to state 46 now
joins the matching relation/facing/audio handoff below; no paired-animation gameplay behaviour is
claimed from the compiler match.

State 42 connects attachment coordinates, input-driven movement and view-effect
coordination. Substates 65 and 66 stop motion, set facing directions 1 and 3,
and use attachment 0 to align or offset the actor's fixed-point position.
Substate 67 stores attachment-adjusted integer coordinates in halfwords
`+0x68/+0x6A`; byte `+0x6C` marks a one-shot alignment and creation of an
attached effect through `frame_create_actor_effect` at `0x1B4A4`. The factory's
observed arguments are `(actor, 200, 3, 1)`; its result enters outer state 5
and receives the actor position. The precise effect role remains provisional.
A countdown cycles at 19 and triggers animation cue 30.

Movement uses the player's direction and current-key bit 2, with speed factors
1.1 and 0.6 before the accepted velocity constructor. Animation 55 is requested
in both moving and stationary phases. Substate 68 checks the shared forty-byte
view-effect record's mode at `+0x24`; mode 1 suppresses a new movement phase.
Both phases call the accepted empty-need handler and adjust need index 50 by 1.
The existing identical `ResourceViewEffect` type now lives in guarded
`resource_view_effects.h`, shared with the command and view-motion sources.
Six existing consumers recompiled exactly and rejected their real source
controls after that type extraction.

The 780-byte handler preserves the original literal pool and complete extent.
A C register binding for the flags temporary retains the original `r4`
allocation in one movement branch; it is a compiler constraint without any
instruction assembly. Natural declarations, shared temporaries and alternate
lifetimes left six differing register bytes in the best unconstrained candidate.
Its raw comparisons remain local. Sharing the direction-input byte between
substates and assigning the velocity output pointer after the view-mode load
also preserve observed scheduling. Changing the cue-cycle threshold from 19 to
20 rejects the same full-byte comparison. These are compiler and static-access
claims; the attachment/effect behaviour has not been tested at runtime.

The attached-effect constructor allocates object kind 28 and rejects effect kind
10 or allocation failure. It obtains an attachment world position, falling back
to the owner position when that reader does not return 1. It clears callback
`+0x98`, copies owner word `+0xA4` minus 1 to result `+0xA4/+0x9C`, and copies
owner word `+0xA8` plus 1 to result `+0xA8/+0xA0`. These four words follow the
finalizer's provisional spatial-bounds view; their units and full owning
structure remain uncertain. The constructor stores the owner at `+0x64`, a
completion-mode byte at `+0x6C`, initializes flags `0x40011` and state 0, and
loads a sixteen-byte variant resource and palette slot selected by effect kind.
The resource, palette and cue tables remain external original data. It copies
the owner's OAM layer, sets sharing flag `0x20` for kinds 1 through 4, and starts
a cue only when the table value is at most 229, saving the returned sample handle
at `+0x68`. Values other than 10 receive no added bounds guard.

The installed lifecycle callback enters state 1 on the effect's animation
completion when mode is 1, or on owner flag 2 for other modes. State 5 also waits
for the effect's animation-completion flag. State 1 marks effect flag 2 and
stops its saved sample. The constructor and callback match all 288 and 108 bytes
with ordinary C, and mutations to initial flags and completion mode reject.
An explicit switch for effect kinds 1 through 4 preserves the original two
bounds comparisons and register allocation; a combined range expression in an
otherwise equivalent candidate produced a shorter, nonmatching extent.

State 43 completes a second direct caller of the same effect constructor.
Substate 0 stops motion, faces direction 4, requests animation 1 and creates
attachment 200 / effect kind 5 / completion mode 1. It enters substate 72 with
countdown 16; countdown `-1` marks outer state 1. Its complete 96-byte extent,
including zero tail alignment, matches ordinary C and rejects a changed timer.
If the attachment reader rejects index 200, the constructor falls back to the
owner position; it receives no fabricated special handling in this source.

State 47 closes the paired-actor handoff from state 41. Substates 46 through
48, 51 and 73 stop motion and wait for animation completion, clear the pending
animation flag, then create actor kind 1 facing direction 4 at position offsets
`(+15,-25)` in sixteen-bit fixed-point units. It copies the owner's upper and
lower word pairs at `+0xA4` and `+0x9C`, subtracts 10 from each copied y word,
and clears callback `+0x98`. Substate 69 creates the same actor after completion
without those bounds copies. Both paths request animation 89 and enter outer
state 25 / substate 0 on the new actor. The constructor result receives no added
null guard. The complete 264-byte ordinary-C match includes both literal words
and rejects an upper-y adjustment changed to 11. An explicit no-op range 0
through 45 records the scanned default behaviour and preserves the original
sparse switch; omitting no-op cases produced a nonmatching jump table.

State 16 connects input movement, the view-effect mode, timed animations,
needs, world-condition checks and scene handoffs. Signed tick bytes at game
state `+0x741/+0x742` trigger counter reduction above 10 and counter addition
above 4, then reset. Reduction truncates `counter - counter * 0.1` through a
signed integer conversion before storing the halfword at `+0x744`; addition
uses a halfword rate table at `0x08D70D58` indexed by stage word `+0x440`.
The counter's gameplay unit remains provisional. A first compound-assignment
candidate selected a different unsigned soft-float conversion and failed to
link under the supported helper set; its source and compiler artifacts remain
local. The accepted expression reproduces the observed signed conversion.

The handler's 75-entry substate table spans selectors 1 through 75, with every
other entry leading to the default exit. Substates 2 and 3 use direction input,
the accepted velocity constructor and current-key bit 2. The connected input
velocity helper applies speed factor 1.8 and animation 4 while that bit is set;
otherwise it uses integer speed and animation 6. View-effect mode 1 prevents a
new movement phase. Substates 7, 8 and 32 through 39 use halfword countdowns;
8 initializes movement flag `0x20` and halfwords 6 and 15. Substates 23 and 74
wait for animation completion, with 74 also adjusting need index 55. Substate
5 submits the current world to the scene handoff unless game flag `0x20` is
set, and clears actor flag `0x10`. It reloads actor flags after the scene call,
but retains the original flags when that call is skipped, preserving the
observed aliasing behaviour.

Substates 52 and 53 compare need words 5 and 2 against `100 << 24`; these accesses
use game state `+0xB0`, which aliases the local need state at `0x03003A00`.
Substate 52 combines an excluded-world predicate, world IDs 6, 28, 37 and 36,
completed condition group `(1,3)` and a random 1-through-100 result at most 50
before handing the first view's actor to outer state 38. The predicate returns
1 for worlds 16, 17, 18, 21, 23, 24, 25, 39, 40, 46, 47 and 48; its name follows
this caller's exclusion role, not a proven geographic or gameplay category.
The alternative plays cue 121 or 122 and enters substate 23. The incomplete
need paths adjust indices 44 and 45, and 53 writes need-step mode 1 to the byte
at `0x0300216C`. The byte's wider effects remain unconverted. Substate 75 waits
for countdown `-1` or key bit 2; only timeout without that input cycles the
first subtype-13 object in the primary list through OAM palette slots 1 to 6,
records the palette at game state `+0x42D` and acquires it. The getter reads the
high nibble of OAM byte `+0xD5`.

The full 1,420-byte handler and its seven dependencies match ordinary C.
Separate event-selection and direction-input locals preserve original register
lifetimes; there are no fixed-register bindings or instruction bodies in this
batch. Controls change a tick threshold, speed factor, counter rate and lookup,
world-set member, mode arithmetic, OAM field and subtype selection.

State 13 uses an integer point at object `+0x64/+0x68` to initialize its fixed-
point destination and enters movement substate 3. Its direction helper calls
the accepted by-value destination-direction calculation with object speed,
retains the current facing when that returns direction 8, always updates
facing and reports completion. Completion restores the default outer state,
substate 2, saved direction byte `+0x70`, flags word `+0x6C`, and activates the
object/program groups at `+0x71/+0x72`. Actor ID 0 also stops and requests
animation 1; while still moving it refreshes velocity. Other substates share
the accepted wait-phase helper: 7 and 11 count down to `-1` before returning to
substate 3, 5 marks outer state 1 and 8 is an explicit no-op. The four complete
extents add 296 ordinary-C bytes and reject changed animation, countdown,
destination direction and fixed-point shift controls.

## Distance movement and terrain handoff

States 8 and 9 add 624 bytes of complete, matching C. State 8 reads its target
pointer at `+0x68`, wait byte at `+0x77` and range byte at `+0x7A`. A missing
target enters substate 7. With a target, it computes the fixed-point distance,
shifts it by 16, follows outside the configured range and waits inside it.
Distance above 220 with flag `0x1000` clear tests the target position shifted
85 integer units along Y against the camera-margin predicate. Only a successful
predicate copies that complete position to the actor. Substates 7 and 13 have
separate zero and `-1` countdown rules. Aggregate position copies preserve the
original field evaluation and remove duplicate component lifetimes.

State 9 reads the selected view's actor and has distinct halfword enter and
leave ranges at `+0x6A` and `+0x68`. Entering substate 9 saves the actor speed at
`+0x64`, doubles it, selects direction 0 through 7 and starts a random countdown.
Leaving that range restores the saved speed. Substates 3 and 7 alternate timed
movement and wait phases; substate 5 responds to animation completion by marking
outer state 1 and clearing flag `0x10`. A shared full-word distance local matches
both comparisons in ordinary C; no fixed-register binding is used in either
handler. These inferred roles do not establish the in-game identity of the states.

The connected 236-byte terrain step computes direction/speed velocity, adds the
actor position and shifts to integer coordinates. Its eight direction cases
adjust the sample using signed bound bytes `+0xBD/+0xBE/+0xBF` before querying
`frame_map_terrain_at` and masking its result to six bits. A semantic inline
point-field copy expresses the by-value aggregate handoff. The query's return
prototype is refined to a word from its un-narrowed result and this mask; the
callee itself remains unconverted. The accepted refresh caller still stores
the result to a byte and was reverified with its changed-terrain control.

The connected 188-byte follower first tries the direct target direction. Terrain
values 0, 1 and 36 pass. Other values select one of two directions per facing
from the original byte table at `0x08052888`, then try its alternate if blocked.
Two blocked alternatives enter substate 7 with timer 10; a passable alternative
enters substate 13 with timer 20. Two C argument variables constrained to `r1`
preserve the original ordering of register moves at those calls; these are
compiler constraints, with no instruction statements or byte bodies. The table
and the larger terrain query remain explicit original data/code. Camera predicate
`0x67E0` has an inspected 148-byte extent and a retained near-match, so it receives
no source credit. Full comparisons and changed distance, saved-speed, terrain-mask
and timer controls pass for all four accepted extents.

## Transient effects and shared intrusive allocation

State 28 reads a signed delta byte at `+0x64` and the indicator pointer at
`+0x90`. Initial substate 0 invokes the counter-effect producer, then marks outer
state 16 and substate 2. Negative deltas create kind 6 from definition `(0,6)` and
play cue 81; positive deltas create kind 1 from `(0,7)` and play cue 82; zero
creates nothing. Cue playback follows the factory call even when allocation
returns null. Successful effects retain the owner, copy its position shifted
60 integer units along Y and initialize the observed flags, timing and phase
fields. Offset and phase names describe these producer accesses; their wider
rendering interpretation remains provisional.

The separate effect family allocates 72-byte records. Its factory accepts byte
kind, group and index, checks the halfword count at `0x03001EE6` against 13,
increments the count and tracks its maximum at `0x03001EE8`. Definition records
at `0x030058A0` have a 40-byte stride and eight entries per group; each supplies
a resource pointer, frame-data address at `+4` and halfword index at `+0x24`.
The count bound and allocation call are reproduced exactly; a consistent pool
state remains an assumption of the original caller, not a new runtime claim.
The destructor releases the node and decrements the count.

Five shared helpers close that allocation path. Allocation returns null for an
empty free head; otherwise it pops the first node, clears the requested byte
extent and pushes the node onto the active head. Release removes from the active
head and pushes to the free head. Pop, push and removal update the intrusive
`next/previous` pointers at offsets 0 and 4 and handle empty heads and missing
neighbors as observed. They only require that shared prefix of the larger
`FrameObject` type; the `FrameObjectList` tail is untouched. The pre-existing
scene allocator uses the same canonical allocation alias and was reverified
with its changed-size control after consolidating the header declaration.
All nine new functions, 576 bytes including alignment, match ordinary C and
reject changed zero fill, release destination, list link, count, effect rate,
position offset and state controls. No instruction or fixed-register glue is
used in this family.

## Controlled speed, turning and effect coordination

State 27 and four connected functions add 1,592 bytes. The 1,116-byte handler
reads a view slot from actor byte `+0x13` and uses its forty-byte view record's
mode to suppress input. Initial substate 0 requests animation 86, selects
substate 2 and sets part 2's draw order to 3. Flag `0x20000000` selects the
sixteen-direction movement path; initialization doubles the facing only when
that flag was clear. Resume byte game state `+0x42F` retains controlled speed
and the prior cue mode. The new transient effect uses definition `(0,2)`, stores
the actor as owner and receives phase, flags, dimensions and a direction mapped
through the already named table at `0x08052858`. These observations do not
identify the in-game object or activity.

Substate 2 accepts the canonical sixteen-direction input rotation helper and
enters substate 3 when view mode permits. Substate 3 coordinates key bits 1 and
2, speed, facing countdown, cue restarts and the effect's direction and dimensions.
It can create an exit actor at `0x38090`, restore eight-direction facing and
animation 1, record the position and world byte, stop its sample and transfer a
bounded twenty-byte callback/spatial view at `+0x98`. The exit constructor and its connected callback/result path are now reconstructed
as described below. The switch table proves substate 7 re-enters substate 3, while 4,
5 and 6 are explicit no-ops. Two C input-argument variables constrained to `r0`
preserve the original order of argument moves; the typed effect-slot local
matches naturally. Pools, table entries and the complete extent are compared,
not substituted or masked.

The 316-byte velocity helper uses the selected view's key bit 1 to accelerate
by `0x3333` to a maximum `0x80000`; reaching the cap applies need adjustment 34.
Without that key it subtracts `0x6666` above `0x6665`, otherwise stops. A halfword
at actor `+0xAC` blocks motion and stops the current cue. Cue IDs 74, 75 and 76
track the observed speed phases and consult the canonical sample-active wrapper.
The two cue helpers preserve a second stop call in the default mode and store
the requested mode after stopping or replacing the handle. They then feed the
accepted velocity constructor and animation 86. The separate setter at `0x1C48`
has the same thirty-byte body and two-byte alignment as the published setter at
`0x1C28`: it changes facing only when needed and marks pending update bit `0x10`.
The byte-identical separate function is reconstructed at its own address.

All five complete extents and changed cue, acceleration, restart threshold and
update-bit controls pass. The accepted rotation helper `0x1F364`, part-order
setter `0x156C` and direction table are reused under their existing canonical
names; the private exploratory duplicate of the rotation helper receives no
new credit. The audio sample-active wrapper is owned and verified separately.

## Controlled-speed exit callbacks and scene results

Four ordinary-C functions close the exit branch of state 27, adding 604 bytes:
constructor `0x38090` (216), per-frame callback `0x3845C` (32), interaction callback
`0x3847C` (120) and result transition `0x38168` (236). Each full extent, including
literal pools and zero alignment, passes an independent changed-source control.

The constructor allocates actor kind 13, assigns its position and facing, selects
a sixteen-byte animation record through byte table `0x0804F1B0`, installs both
callbacks and enters outer state 0 / substate 7. It clears the graphics-mode and
double-tile bits, acquires the palette selected at game state `+0x42D`, sets flags
`0x10040255`, refreshes its layer and sets the horizontal flip bit for facing
values above 4. The allocation result is used without a null check, preserving
the caller's original pool assumption. The callback at `+0xCC` receives two
object arguments; the new bounded callback overlay records this signature without
changing the broader actor view's still-provisional callback types.

The interaction accepts an exit object in outer state 0 and an interacting actor
in state 16. It separately requires interacting actor ID 0 and pressed-key bit 1
for the actor in the selected local view. The source reads the low byte of the
canonical halfword pressed-input table at `0x03004228`, matching the original byte
load. This evidence identifies input handling here; an address alias used in
older scene setup remains a separate interpretation. Success clears input,
selects outer state 4 / substate 0 and saves the interacting actor at `+0x64`.
The per-frame callback always refreshes the layer and calls the result transition
only in outer state 4.

Substate 0 clears the request's active byte and bytes 1 and 2, initializes a
four-byte result view from `0x08D72024`, requests scene stage 2 and enters substate
55. Result word `scene-argument base +0x0C` selects the next step: zero restores
the saved actor to outer state 27, copies facing, sets game byte `+0x42E` and
marks the exit object with flag 2; one faces the saved actor toward the exit,
requests animation 28 / substate 75 and sets its timer to 90; minus one resets
the exit object. Other result values leave it waiting. The game identity and
meaning of this activity remain inferred rather than established by gameplay.
Controls alter factory flags, the callback state test, interacting actor ID and
the return timer. All four reject with one differing byte.

## Actor attachments, target callbacks and completion

Seven ordinary-C functions add 740 bytes and connect handlers 17 and 39. The
registrar `0x166C` fills the first free pointer among the two slots at object
`+0x138/+0x13C`. It switches outer state to 17 and marks pending bit 1 only when
the state differed. A full pair returns zero. Removal `0x16B8` clears the first
matching pointer, and the byte counter `0x1A64` counts non-null slots. These
fields are a bounded overlapping view rather than a claim that all actor kinds
share one complete structure. A semantic inline state setter and explicit
32-bit base/index arithmetic reproduce the compiler's loop lifetimes without
fixed-register constraints. Earlier differently grouped loops remain local.

Handler 17 polls each non-null attachment through `0x2E41C`; returns 2 and 0
remove that slot. With no attachments and outer state other than 23, it requests
animation 1, restores the default outer state, selects substate 2 and snaps the
next-position coordinates through the canonical grid-center helper. The fixed
and integer conversion calls and the ignored grid helper result are retained.
Handler 39 waits for route status 2, cancels failed status 3 and processes status
1 through the action-target selector. The target's owner pointer at `+0x64`
provides callbacks at owner `+0xE4` and `+0xF0`, returning bytes; the second receives
the actor's mode byte at `+0x6A`. Accepted callbacks register the owner attachment
and select substate 41; rejection selects 19, which restores the default state.
The compiled calls use the existing register-call veneers explicitly declared in
metadata. Possible callback targets remain unresolved static transfers.

The status helper's owner view contains three twenty-four-byte records at `+0x0C`.
Each record names an actor pointer, timer `+8`, running byte `+0x0C` and status
word `+0x10`. Status 2 clears running and returns 1; status 3 clears running,
finishes the actor and returns 2; status 1 cancels its route and returns 1. Other
values invoke the full-word callback at owner `+0xF4`. A return of 0 or 2 clears
the matching record's actor and sets its timer to 94. The initial search's null
result is dereferenced without a guard in the original path, so a matching owner
record is an original caller invariant, not a new safety or runtime claim.
Completion `0x2EE78` selects outer state 23 / substate 0 for actor ID 0, otherwise
its default outer state / substate 7, then cancels the route.

Full extents include the original zero alignment. Real controls change the new
outer state, removed pointer, count increment, state-17 exception, state-39
substate, primary actor ID and record timer. All reject; their differing-byte
counts are 2, 9, 1, 1, 1, 1 and 1 respectively. The entry/record roles and callback
names describe these static handoffs; their gameplay meaning is still provisional.

## Queued choices and routes for states 31/32/33

The combined handler at `0x9E40` and four connected helpers add 804 ordinary-C
bytes. Substate 2 consumes pending choices using the category byte selected by
actor ID. Accepted owner callbacks enter the target route and set actor byte
`+0x64`; actor ID 4 also requests cue 51. A failed choice scan calls the still
unconverted world-choice cleanup routine, marks that byte when cleanup succeeds
and shows a failure request only when it remains zero. Actor subtype 4 finds
object ID 5 / subtype 50, performs the retained integer conversion and attempts
a route to its position; successful routes enter substate 71, and failed or
finished routes enter outer state 43 / substate 0. Other subtypes apply the
negative penalty from the six-word row indexed by game stage and actor ID,
request cue 5 and enter outer state 34 / substate 0. Substate 7 re-enters 2.

The 116-byte lookup walks the next pointers at list-head base `0x03005868`,
caching the next node before inspecting the action byte at `+0x5C`. Category 1
accepts codes 12 or 27; category 2 accepts 45; category 3 accepts 22. A match
writes the action as a word, clears its pending byte and returns the target
pointer at node `+0x54`. No match returns zero. The larger cleanup at `0xA0A4`
also touches serialized world records, but remains an explicit unconverted
extent; its best failed candidate and raw comparisons receive no C credit.

The previously canonical `frame_actor_use_target` alias is retained at `0x2E0B8`:
its first argument is the choice target and its second is the actor. It accepts
only owner callback `+0xE4` return byte 1, then calls the new route helper at
`0x8CFC` with actor first. That helper requests a target cell through `0x3B75C`,
converts the cell to a point and then to fixed coordinates, starts the route,
selects substate 3 / outer state 39, requests animation 6 and saves the action
byte at `+0x6A`. The route-start result is intentionally ignored, matching the
original handoff. The target-cell search remains a separate unconverted boundary.
The failure helper assigns request IDs 502, 503, 501 or 500 by subtype, creates
scene object 193 with definitions 263–265 for subtypes 0, 2 and 3 and activates
the scene request. Subtype 4 assigns ID 501 without creating a new object.

All five complete extents and pools match current headers. Real controls change
cue 51, accepted action code 45, failure request ID 503, callback acceptance value
1 and routed substate 3; their differing-byte counts are 1, 1, 17, 1 and 1.
The category labels, target search roles and failure names describe static code
relationships rather than established gameplay identities.

## Target-cell count and bounded grid lookup

The accepted route-to-target helper calls the still-unconverted selector at
`0x3B75C`. That selector calls these two matching dependencies. The owner counter
uses the word at owner `+8` to select a descriptor from `0x08062B24`. For modes
other than one and four, a non-null descriptor supplies a five-by-five byte
array after a two-byte prefix; the result counts bytes equal to the requested
mode. The prefix's meaning and the descriptor table's full extent remain unknown.

Modes four and one instead count contiguous nonzero low halfwords in twelve
words at owner `+0x74` and ten words at `+0xA4`, respectively. The selector reads
the first slice as candidate cells and compares coordinates against the second
slice when its restriction argument is set. The C view uses one contiguous
22-word array so the counter's twelve-word offset stays inside that array.
These names describe that static
use; they do not establish gameplay meaning. The counter preserves the zero
sentinel and the two array limits. One unsigned-halfword register binding keeps
the mask's original value lifetime; six unnecessary bindings were removed after
the exact match.

The lookup reuses the canonical map-registration layout: data pointer at zero
and unsigned extent at `+0x10`. It reads only the two low bytes of the packed
cell. Either coordinate at or beyond the extent returns null; otherwise it
returns the byte at `data + y*extent + x`. A local extent serves both bounds
checks, while the accepted valid branch reloads the extent for multiplication.
One C pointer binding preserves the context's lifetime. No instruction bodies
are embedded. Changing the X boundary or the twelve-cell limit rejects one
byte in each complete original extent.

The neighbor helper copies sixteen bytes from `0x0807F410` into eight local
coordinate pairs, then selects a pair using the byte-sized direction argument.
It adds and stores the two low coordinate bytes before checking them against the
same registration extent. The result is zero or one. The direction index remains
unchecked, and the writes precede the validity result; those input assumptions
are preserved. The shared prototype now uses a sufficient unsigned-byte result
instead of the earlier provisional void return. The accepted 412-byte walk
direction caller still matches, and its real changed-source control rejects.
The neighbor body uses ordinary C and zero alignment; changing its success value
from one to two rejects one byte.

Private comparison evidence is retained under `actor-target-cell-canonical4-contiguous-*`
and `actor-target-neighbor-return-consumers-*`.
Earlier width, loop-order and register-lifetime trials remain under
`actor-target-*`. The 356-byte selector itself still differs and receives no C
coverage. It appears to prefer the actor's current cell or a nearest usable
candidate, with optional matching on either restricted axis; its outputs and
failure assumptions remain under investigation.

## State 46 relation, facing and audio handoff

State 46 joins the first player's position, a distance threshold, facing,
relation records, animation and audio. It saves the actor subtype before calls
that may change actor state, then reloads the current halfword only after the
distance, flag and object-ID guards pass. The positive-relation branch compares
the widened current value; the negative branch explicitly narrows its separate
copy. The saved subtype remains a full unsigned word for the adjacent-ID test.
Keeping these widths and lifetimes separate closes the complete 468-byte extent,
including its three literal pools and zero alignment.

The partial relation view reads a signed byte at game-state `+0x39`, with stride
four and index `actor_id-18`. The ROM descriptor at `0x080612A4` has stride 44,
a cue-record pointer at `+0x20` and a variant byte at `+0x25`; the positive branch
reads cue word seven. The negative branch chooses among cues 138, 139, 147 and
148. These layouts follow the loads and address arithmetic; their relation and
greeting names remain provisional. Bounds and unchecked indexing are preserved.

Three local register bindings preserve the late-loaded halfword, its distinct
negative-branch copy and the unsigned narrowing intermediate. They express C
value lifetimes and conversion; no instruction bodies are embedded. Ordinary
cast/helper variants remain locally with their raw mismatches. The canonical
positive matches all bytes; changing timer 60 to 61 rejects one byte. Private
evidence is retained under `reports/audio-root/actor46-canonical/` and the
`actor46-load-lifetimes`, `actor46-copy-aliases` and `actor46-minimize` trials.
This closes all directly dispatched handler bodies as matching C, without a
runtime or gameplay claim.

## Local proofs and remaining boundaries

Private ready metadata is `reports/agents/vblank-wrapper/actor-state-batch-manifest.json`,
`reports/agents/vblank-wrapper/actor-route-batch-manifest.json`,
`reports/agents/vblank-wrapper/actor-route-update-batch-manifest.json`
`reports/agents/vblank-wrapper/actor-scene-batch-manifest.json`
`reports/agents/vblank-wrapper/actor-social-batch-manifest.json`
`reports/agents/vblank-wrapper/actor-interaction-batch-manifest.json`
`reports/agents/vblank-wrapper/actor-actions-batch-manifest.json`
`reports/agents/vblank-wrapper/actor-carry-batch-manifest.json`
`reports/agents/vblank-wrapper/actor-idle-batch-manifest.json`
`reports/agents/vblank-wrapper/actor-distance-batch-manifest.json`
`reports/agents/vblank-wrapper/actor-effect-batch-manifest.json`
`reports/agents/vblank-wrapper/actor-speed-exit-batch-manifest.json`
`reports/agents/vblank-wrapper/actor-attachment-batch-manifest.json`
`reports/agents/vblank-wrapper/actor-choice-batch-manifest.json`
and `reports/agents/vblank-wrapper/actor-target-cell-batch-manifest.json`.
Full positive/control comparisons against the current headers are retained under
`actor-state-route-types13-*`, `actor-route-path-layout13-*` and
`actor-route-updates-current10-*` and `actor-scene-current12-*` and `actor-social-current4-*` and `actor-interaction-current2-*` and `actor-actions-canonical7-*` and `actor-carry-canonical5-*` and
`actor-carry-shared-layout6-*`, `actor-idle-canonical12-*`, `actor-distance-canonical4-*` and `actor-distance-word-return1-*`, `actor-effect-canonical9-*`, `actor-effect-speed-canonical14-*`, `actor-pool-header-shared1-*`, `actor-speed-exit-canonical4-*`, `actor-attachment-canonical7-*` and `actor-choice-canonical5-*` in the same ignored
agent report tree. Original CFG scans and all 29 handler entry summaries remain
local. Mutations change the dispatcher flags, animation IDs, countdown, wait
factor, direction update flag, group offset, record stride, state target, point
arithmetic, route limit, slot bound, active-count decrement, probe-vector length, mode transition,
path-copy argument, destination direction, flags argument, search-status field, scene timer/request ID, scene-counter increment,
activation mask, factory flags, allocation size, proximity cue, transition duration, special-subtype selection,
centered-width divisor, velocity arithmetic, move countdown, social countdown,
value-reader field, terrain class, option ID range, condition action ID, descriptor lookup bound, action notification ID,
game-value ceiling, parameter level bound, state-41 animation ID, sequence mode and state-42 cue threshold, effect flags, completion mode and state-43 countdown and state-47 bound adjustment.

All 29 direct handler functions are reconstructed here. Useful next
connected targets are the need target selector `0x6F20`, action-target selector
`0x7DC4`, reverse path extraction `0x3C08C`, and grid search `0x3BCF4`.
Camera-margin predicate `0x67E0` and terrain query `0x2ABB0` remain connected
next targets. World-choice cleanup `0xA0A4` and target-cell search `0x3B75C` are additional
connected next targets. The retained CFGs are closed; those scans alone do not establish C coverage, final function boundaries
or runtime reachability. These bodies remain explicit unconverted ROM regions
in the full build.
