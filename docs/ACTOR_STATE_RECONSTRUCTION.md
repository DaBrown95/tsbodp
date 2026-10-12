# Actor state dispatch and connected handoffs

This batch reconstructs 26 Thumb C functions spanning 4,672 verified bytes. The
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
state and do not consume the incoming actor. Their broader side effects remain
unconverted.

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
The central route scratch at `+0x20..+0x113` remains unspecified. Beginning a route
chooses the first free job, initializes those fields, enables actor flag
`0x1000000`, sets the caller's status to 2 and increments the count. It returns
zero when all three slots are occupied. The fourth parameter is a full word and
the fifth is narrowed to an unsigned byte; all published constant-argument
callers still match after this prototype refinement. The limit setter also
narrows its input to a byte. Both setters stop after their first matching actor.
Cancel checks all slots; release clears the route flag, reapplies the saved flag
mask, resets the status word, clears all 280 job bytes and decrements the count.
These handoffs connect the reconstructed state handlers, but route solving and
per-frame route processing remain unconverted.

## Local proofs and remaining boundaries

Private ready metadata is `reports/agents/vblank-wrapper/actor-state-batch-manifest.json`
and `reports/agents/vblank-wrapper/actor-route-batch-manifest.json`.
Full positive/control comparisons against the current headers are retained under
`actor-state-route-types13-*` and `actor-route-current13-*` in the same ignored
agent report tree. Original CFG scans and all 29 handler entry summaries remain
local. Mutations change the dispatcher flags, animation IDs, countdown, wait
factor, direction update flag, group offset, record stride, state target, point
arithmetic, route limit, slot bound, active-count decrement and probe-vector length.

Nine of the 29 direct handler functions are reconstructed here. Useful next
connected targets are the need target selector `0x6F20`, action-target selector
`0x7DC4`, route steering `0x371B4` and the remaining route update family. State 46
(`0x6874`) is a retained near-match joining proximity, relation values, facing,
animation and audio; its inferred relation/descriptor layouts still need matching
confirmation. State 16 (`0x5CA4`) joins input, interaction choices, needs and
world-condition checks but has a larger substate table. Their scanned CFGs are
closed; those scans alone do not establish C coverage, final function boundaries
or runtime reachability. These bodies remain explicit unconverted ROM regions
in the full build.
