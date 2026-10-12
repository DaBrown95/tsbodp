# Actor state dispatch and connected handoffs

This batch reconstructs 52 Thumb C functions spanning 8,608 verified bytes. The
names describe static accesses and call relationships; selector-derived handler
names deliberately preserve uncertainty about gameplay roles. Each complete
extent, including pools and zero alignment, matches its fixed ROM address. Real
source mutations fail the same comparison. This is source reconstruction evidence;
no runtime or gameplay test is claimed here.

| ROM offset | C function | Verified bytes |
| --- | --- | ---: |
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

## Local proofs and remaining boundaries

Private ready metadata is `reports/agents/vblank-wrapper/actor-state-batch-manifest.json`,
`reports/agents/vblank-wrapper/actor-route-batch-manifest.json`,
`reports/agents/vblank-wrapper/actor-route-update-batch-manifest.json`
`reports/agents/vblank-wrapper/actor-scene-batch-manifest.json`
and `reports/agents/vblank-wrapper/actor-social-batch-manifest.json`.
Full positive/control comparisons against the current headers are retained under
`actor-state-route-types13-*`, `actor-route-path-layout13-*` and
`actor-route-updates-current10-*` and `actor-scene-current12-*` and `actor-social-current4-*` in the same ignored
agent report tree. Original CFG scans and all 29 handler entry summaries remain
local. Mutations change the dispatcher flags, animation IDs, countdown, wait
factor, direction update flag, group offset, record stride, state target, point
arithmetic, route limit, slot bound, active-count decrement, probe-vector length, mode transition,
path-copy argument, destination direction, flags argument, search-status field, scene timer/request ID, scene-counter increment,
activation mask, factory flags, allocation size, proximity cue, transition duration, special-subtype selection,
centered-width divisor, velocity arithmetic, move countdown, social countdown,
value-reader field and terrain class.

Thirteen of the 29 direct handler functions are reconstructed here. Useful next
connected targets are the need target selector `0x6F20`, action-target selector
`0x7DC4`, reverse path extraction `0x3C08C`, and grid search `0x3BCF4`. State 46
(`0x6874`) is a retained near-match joining proximity, relation values, facing,
animation and audio; its inferred relation/descriptor layouts still need matching
confirmation. State 16 (`0x5CA4`) joins input, interaction choices, needs and
world-condition checks but has a larger substate table. Their scanned CFGs are
closed; those scans alone do not establish C coverage, final function boundaries
or runtime reachability. These bodies remain explicit unconverted ROM regions
in the full build.
