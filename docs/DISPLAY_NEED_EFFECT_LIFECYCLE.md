# Need-effect allocation, handoff and teardown

Seven connected C replacements cover 616 bytes, including their literal pools
and observed alignment, at their original Thumb addresses:

| Function | ROM offset | Bytes |
| --- | --- | ---: |
| `frame_need_effect_remove` | `0x2E1E8` | 56 |
| `frame_need_effect_before_step` | `0x2E220` | 48 |
| `frame_reset_need_effect` | `0x2E250` | 52 |
| `frame_need_effect_enabled` | `0x2E284` | 72 |
| `frame_allocate_need_effect_state` | `0x2E2CC` | 248 |
| `frame_release_need_effect_state` | `0x2EB40` | 92 |
| `frame_create_need_effect_state_node` | `0x2F3D0` | 48 |

The published `frame_spawn_need_effect` installs the removal and handoff
callbacks and invokes the state constructor. The published interaction family
uses the same state kind, object and three attachment records. These callers
establish the path; no execution or gameplay test is claimed.

The pool-node allocator requests exactly 256 bytes from the existing intrusive
pool functions. Its active-list access covers the head and tail at
`0x03005868`; that head is already accessed as `g_frame_pending_action_head`
elsewhere. The new list name describes this caller's role, not an exclusive
storage type. The free-list head is at `0x03001E34`. A separate 256-byte access
view retains unknown fields and generic callback pointers rather than expanding
the existing partial shared state layout into a speculative universal type.
The constructor's raw store and 36-byte descriptor index preserve the complete
incoming kind word. Its former byte parameter declaration is therefore refined
to a word; the published 424-byte spawn caller still matches with its actual
negative control.

Construction clears the object pointer, byte `+0x63`, optional byte and parameter,
the 48-byte and 40-byte work ranges, four retained words and a byte at `+0xDC`.
It copies descriptor bytes `+0x20` through `+0x22` to state bytes `+0x5D`, `+0x60`
and `+0x61`. The seven callback slots at state `+0xE4` through `+0xFC` receive
descriptor words in the observed order `+0x1C`, `+4`, `+8`, `+0x0C`, `+0x10`,
`+0x14`, `+0x18`. Finally, it clears the same three 24-byte attachment records
used by the interaction/status sources. Their signatures and remaining fields
stay provisional. No descriptor kind bound or failure handling is invented.

The constructor uses two short `r0` address locals for serialized callback reads;
no constrained value survives an external call. The table, kind and record offset
use ordinary compiler allocation. The final descriptor cursor consumes the offset
only after earlier slots have been copied. These are C address calculations and
stores; no original instruction body or output transformation is embedded.

The handoff copies state words `+0xD4`, `+0xD8`, `+0xCC`, `+0xD0` into object
words `+0x9C` through `+0xA8`. Its local volatile object access view preserves
four observed reads of the state pointer between stores. This qualifier describes
the required access sequence, not a claim about the original typedef, asynchronous
hardware or an established non-aliasing invariant. The advancing byte cursor is a
semantic inline helper. The word meanings remain neutral.

Removal checks object byte `+0x82` (the existing provisional `mode` field), calls
the unconverted registration-removal function when it equals one, then reloads
the state pointer before releasing it. Release sends an auxiliary object at
state `+0x58` to state one, detaches each non-null actor in the three records,
repairs the active-list tail when needed and returns the node to the pool.
The registration function at `0x3B4F0` remains unconverted and its wider context
is uncertain. Reset clears the phase, object state, two byte arrays and flags.
The enabled predicate excludes subtype 141 in world nine and otherwise tests
the accepted world exclusion helper and state bytes `+0x62`/`+0x63`.

Every new public source matches the complete linked extent. Each real source
mutation fails: removal mode, handoff word, reset range length, subtype guard,
constructor work length, attachment loop count and pool allocation size. The
424-byte spawn and all seven interaction sources were freshly verified against
the refined header, with their actual controls. Failed contracts, ordinary field
views, cursor variants and raw expected/actual bytes remain in ignored local
`reports/agents/display_audio/interaction/`; accepted-only metadata is
`need-effect-lifecycle-ready.json`. The initial milestone left the update, commit and tick unconverted; the following
section records the subsequent connected update/tick batch. Whole-ROM equality is a separate integration
claim made by the full build gate.

## Update, tick and action completion

Six further connected replacements cover 1,688 bytes:

| Function | ROM offset | Bytes |
| --- | --- | ---: |
| `frame_update_need_effect` | `0x2D7C0` | 292 |
| `frame_commit_need_effect` | `0x2D9AC` | 608 |
| `frame_need_effect_tick` | `0x2DC0C` | 220 |
| `frame_need_effect_choose_action` | `0x2DE84` | 192 |
| `frame_need_effect_finish_action` | `0x2DF44` | 292 |
| `frame_need_effect_restore_audio` | `0x2E194` | 84 |

The constructor already installs the updater and tick. The updater hands the
signed request byte at object `+0x103` to the commit function, selects
palette resources, installs or clears callback slot `+0xC8`, and sets the OAM
horizontal flip from direction. Its resource pointer table is at `0x08D71C6C`;
the six-word palette rows are at `0x08066FC4`. The three special palette slots
at `0x08062E70`, `0x08062E74` and `0x08062E78` are passed by address. Table storage
bounds and those slots' wider meanings are unknown. The callback slot is described
through an explicit access at `+0xC8`; it does not silently adopt the existing
partial actor view's callback at `+0xCC`. The callback at `0x11328` is reconstructed below; the palette setter
at `0x30168` is now reconstructed with its connected slot lifecycle in
[the object palette evidence](DISPLAY_OBJECT_PALETTE.md).

The incoming commit parameter is a complete word. This caller performs a signed
byte load without narrowing its argument before the call; the matching commit
switch retains the incoming word. Both previously published byte declarations are
therefore refined to word arguments. The eleven accepted sources whose include
closure reaches either affected header were freshly compiled and linked with their
actual changed-source controls. These include the actor action selector and the
interaction/attachment sources. All still match. The commit routine now also matches its entire 608-byte extent.

The commit selects a resource at offset 16 or 48 according to directions one/seven
or three/five; other directions return. For kind 82, it selects an eight-byte
appearance record from `0x08062D78`, retaining the appearance in the state's
parameter high byte and setting optional byte ten. Existing optional-ten states
recover a signed appearance index from that parameter. It then selects an animation
program from seven-word rows at `0x08068190`: requests zero through five use slots
zero, one, three, two, four and five. A missing program updates the resource pointer,
previous/current frame sentinels and request byte, clears the command pointers,
and invokes the accepted set-frame helper. Kind 32 performs the related retained
appearance selection for the frame byte. The remaining row slot and table storage
bounds are unknown; no valid-index or allocation invariant is assumed.

The commit's optional and parameter scalar access locals bind to `r3` and `r0`
within each appearance block. Both are assigned from the observed state reads and
consumed before an external call; no constrained value survives a call. A short
signed-frame sentinel helper binds its word value to `r0` before storing the byte.
The other semantic values use ordinary allocation. The last appearance selection
uses a named signed index before reading the table. These views preserve the observed
read order and narrowing without adding asynchronous-memory or original-typedef
claims. Plain/scoped field trials, alternative sentinel types, getter forms and
raw comparisons are retained, including the closest four-byte scheduling failure.

The tick dispatches states 0 through 18, including explicit no-op states. State
one enables flag two, state three resets the state, state 15 advances variant zero
to 55 and then calls the action selector, and state 18 calls completion. Afterward
it updates horizontal flip and, for object mode one, calls the unconverted attachment
step at `0x2E984`. The extent ends at `0x2DCE8`, after its return and alignment;
the earlier exploratory range through `0x2E1E8` crossed several independent bodies
and is not its function boundary. The compiler-generated switch table is included
in the 220-byte comparison.

The action selector reads the signed index at `0x03004370 + 0x0C`. This global
is also accessed as `g_resource_scene_arg`; the new name describes this role rather
than asserting a universal storage type. Only the `-1` sentinel is checked. No
choice-index bound is invented. Choice 40 stops the actor and enters completion;
choice 34 stops the actor, changes its state and links it to the requesting object.
Other choices invoke state callback `+0xF0` with the state, actor and choice byte.
Only the low byte of its word result is tested. The indirect call uses the existing
Thumb `_call_via_r3` glue at `0x4CCFC`; that stub is separate from C coverage.
Failure resets the requesting object and sends the actor to state 16, variant two.

Completion stages variants zero, 14 and 15. It queries the current actor-entry
list through game-state `+0xF0`, starts a countdown of eight, submits the kind,
optional byte and parameter's high byte, and waits for the actor's completion flag.
The accepted actor-entry functions have their canonical word/int return types;
this caller explicitly narrows their results to a byte, as the original loads and
shifts show. Failure marks bit `0x200000` in an observed 56-byte saved-object record
at `0x03004130`, indexed by byte `+49` of storage at `0x030040E0`. Wider table
bounds and the exact meaning of that bit remain uncertain. Object `+0x68` is read
as an actor pointer in this action path; a separate access view records that usage
rather than replacing the existing need-effect object's flags-word view globally.

The updater's game-state halfword reader and completion's entry-list reader each
use a short `r0` address local to preserve the observed base-plus-offset access.
No constrained value remains live across an external call. Other locals use ordinary
compiler allocation. These bodies are semantic C with explicit unknown access views;
the only assembly directives request observed zero alignment.

All six complete linked extents match with the current public header. Six real
mutations reject with one differing byte each: palette sentinel, optional sentinel,
variant 55, choice 40, countdown sentinel and restore optional guard. Fresh raw comparison/control receipts and all
useful failed attempts remain under the ignored interaction report directory;
accepted metadata is `need-effect-update-ready.json`. The 412-byte choice builder and attachment-step function remain
explicit unconverted targets. Static control flow and compiler matching establish this
connection; runtime behaviour and whole-ROM equality require separate evidence.

The restored dependency at `0x2E194` selects audio rather than a graphics sequence,
so the former provisional `frame_need_effect_restore_sequence` alias is corrected
to `frame_need_effect_restore_audio`. For optional byte other than one and kinds
42 through 45, 49 or 104, a nonzero signed parameter triggers the scene resource's
audio selection and then clears the parameter. It uses the canonical scene context
at `0x03004320`, resource pointer `+4`, resource-audio reader at `0x26A9C` and
sequence selector at `0x411BC`. The two audio callees remain unconverted; these
call-site roles do not establish their full semantics or runtime behaviour. The
84-byte restore source uses ordinary C and observed zero alignment. All six sources
were freshly verified after the alias/header refinement, with real controls.

## Attachment effects and optional progress

A further three connected replacements cover 672 bytes:

| Function | ROM offset | Bytes |
| --- | --- | ---: |
| `frame_need_effect_read_center` | `0x2E144` | 80 |
| `frame_need_effect_advance_optional` | `0x2E888` | 252 |
| `frame_step_need_effect_attachments` | `0x2E984` | 340 |

The tick's attachment step counts occupied actors in the same three records and
reads the primary object's visibility bit. It stages an auxiliary effect through
object pointer slot `+0x90`. Optional one creates the effect only when there are no
attachments and the primary object is visible. Optional two additionally tests the
signed parameter against `0x45FF`, and removes an existing effect at or below the
threshold. Optional three creates an effect, searches for subtype 41 to decide its
visibility bit, and invokes the progress function. Other optional values retire an
existing effect; loss of the primary object's visibility also retires it. Finally,
a non-null state callback at `+0xF8` is called through existing `_call_via_r1` glue.
The stub remains separate from C coverage, and its wider callback contract is
provisional.

The program table already consumed by the commit has 28-byte rows. This path reads
bytes 24 through 27 as effect-factory arguments. A separate view records those four
byte roles; it does not assert that the seventh word is an animation command pointer.
The semantic inline record reader uses ordinary allocation and keeps the observed
literal/index ordering. The full function ends at `0x2EAD8`; an earlier exploratory
444-byte range crossed the subsequent pool initializers and is not its boundary.
All embedded literals and alignment within the 340-byte extent are compared.

Optional progress consumes the first word at `0x030040E0` as the current player
object pointer. This storage is also accessed through input and scene-context
views elsewhere; the new alias describes a single observed role. Up to signed
parameter `0x63FF`, it adds 25 to the parameter, compares the accepted point-distance
result with `0x95FFFF`, and increments the primary object's word at `+0x58`. After
that word's old value exceeds 89, it asks the existing signed-parameter reader at
`0x3D1F4` for index three of the social-probe storage at `0x030039E8`, converts twice
that value plus 20 to a byte for the chance function, and resets the counter. A
successful chance can send a player in state 16 to state 47 with animation request
71 and variant 46. The coordinates' units, distance threshold and parameter meanings
remain provisional; no execution claim follows from these branches.

Beyond the parameter limit, progress retires the primary object, clears its
parameter and spawns a kind-146 need effect. It sets the new object's linked byte,
reads the old object's projected bounds midpoint, and calls the existing unconverted
configuration function. Failed configuration removes the new object. The return
word reports this completion path. There is no invented null-allocation check.
The midpoint helper projects the bounds pairs at object `+0x9C` and `+0xA4` through
the accepted grid-coordinate reader, averages each signed axis with division by
two, then forms the shifted fixed-point result. Wider bound validity is unknown.

All three complete extents match from current public sources and the guarded
progress header. Their actual source controls reject: subtype 41 becomes 40,
the progress limit decreases by one, and the midpoint x divisor changes to four.
The published tick caller was freshly verified with its control. These new bodies
use ordinary C without fixed registers; the only assembly directives specify zero
alignment. Canonical prototypes of the effect factory, point-distance, signed
parameter and grid-coordinate functions are preserved. The 200-byte configuration
function, choice builder, action-availability lookup and adjacent pool initializers
remain explicit unconverted targets. Raw trials, comparisons and controls remain
in the ignored interaction reports; accepted metadata is
`need-effect-progress-ready.json`.

## Action availability

`frame_need_effect_action_available` at `0x2ECC0` matches its full 96-byte extent,
including its literal and alignment. The configuration caller at `0x2D8E4` queries
this predicate with action two before searching for an attachment target. The
canonical interface retains a complete action word and returns a boolean byte;
its literal zero/one returns do not establish an original source typedef.

Actions one and four test the low halves of the work words at state `+0xA4` and
`+0x74`, respectively. The source preserves the observed word access and uses an
unsigned shift to discard the upper half for the nonzero test. Other actions read
a pointer from `0x08062B24` indexed by state kind. A non-null record contains two
uninterpreted bytes followed by the observed five groups of five action bytes.
The predicate scans these 25 slots and accepts an equal byte. The wider table
storage, record header meaning and valid kind/action ranges remain unknown.

The common present/absent exits express the two flag cases and bounded row scan
in C. A group-cursor scalar uses `r3`; the routine makes no external calls. The
32-bit integer row-address addition preserves the required operand allocation
before resuming byte-pointer traversal. These are semantic accesses to the observed
record layout, with no instruction body or output alteration. The final public
source matches; decreasing the inner scan bound from five to four changes one
byte and is rejected. All three preceding progress sources and their real controls
were freshly verified with the refined guarded header. Ignored proof inputs and
failed views remain local; accepted metadata is
`need-effect-action-available-ready.json`.

### Attachment-count boundary

`frame_need_effect_attachment_count` at `0x0802ECA0` is a 32-byte matching C
replacement used by the connected choice builder at `0x0802DCE8`. It advances
through exactly three 24-byte records beginning at state `+0x0C` and counts
nonnull actor pointers. The return value is a word; this does not establish a
wider attachment capacity beyond this loop and the corresponding observed state
layout. Ordinary C reproduces the loop and complete extent. The two loop counters
are initialized before the record cursor, preserving the observed initialization
order. A compiled control changing the record count from three to two rejects the
match. The published progress step, optional progression and tick were freshly
verified with their own changed-source controls after the declaration was added.
Failed choice-builder candidates remain excluded from source coverage; the
verified replacement and its boundaries are described below.

### Choice builder and menu handoff

`frame_need_effect_build_choices` at `0x0802DCE8` now reproduces its complete
412-byte extent, including the shared literal pool and alignment. It obtains the
state's callback at `+0xE8` and passes the embedded choice buffer at object `+0x7A`;
the callback's return value is unused. The callback view does not establish what
other producers write. After clearing the 14-byte title buffer at object `+0x6C`,
the builder scans up to seven choice bytes and stops on zero. Each nonzero code
indexes a four-byte row at `0x080645C4`, reading its second halfword as the title
identifier. This row interpretation follows the loads and the menu handoff; the
first halfword and the complete table length remain unknown.

The builder may append choice 40 when the need effect is enabled, or choice 34
when the world exclusion predicate returns one. Each append requires space, no
attached actors, optional value other than three, and a kind other than
133/135/146/147. The first append increments the scan index; the second does not.
When at least one choice exists, it clears bytes `+4`, `+1` and `+2` at
`0x03005A00`, copies seven title halfwords to `0x030059F0`, updates text field two
from the game-state halfword at `+0x744` for kind 117, invokes the still-unconverted
scene-stage handoff at `0x08027DC0` with two, and changes the object state to 15 and
variant to zero. The counter view overlaps existing scene-request storage, and
the title view overlaps the scene-result storage. These are access roles, not
claims about distinct allocations or complete storage bounds. The existing
choice consumer at `0x0802DE84` supplies the next action/attachment handoff.

The replacement uses semantic C register views to preserve the observed
lifetimes: the choices, values and secondary cursor occupy callee-saved registers
through external calls; the scan's table, code and short byte offset occupy
`r3`, `r2` and `r1` only within the scan. Its offset scope ends before the inline
title reader uses `r0` for its offset/result. Each append's constrained code and
pointer are consumed before further work. No unrelated values overlap those
register views, and no caller-saved constrained value survives an external call.
The explicit scan label preserves the observed exit structure. Independent
source/destination views in the final copy and sequential address accumulation
preserve the title-buffer arithmetic. All of these operations remain C; the only
assembly directive specifies zero-filled alignment. Earlier loop-peeling,
register-allocation and literal-sharing mismatches are retained in ignored raw
reports and receive no coverage.

The formatted public source matches all 412 bytes. A real compiled control
changing the first excluded kind from 133 to 134 differs by one byte and is
rejected. The published tick, attachment count and action consumer were freshly
recompiled and checked with their own changed-source controls. Matching and the
static menu connection do not establish runtime correctness or gameplay coverage.

### Two-object callback and movement reset

The installed callback `frame_need_effect_interact` at `0x08011328` matches its
20-byte extent. Its body preserves the incoming second argument, then invokes
`frame_need_effect_stop_at_position` on each of the two objects. This supports a
two-object signature for the callback address and corrects the earlier provisional
single-object declaration. The updater's explicit slot `+0xC8` view now uses that
same signature. The copied matching collision dispatcher supplies two concrete
`CollisionObject` pointers through its callback array starting at `+0xC8`.
The resource factory at `0x0800BD68` installs this callback in slot zero. Its
declaration, formal pointer tags and the updater's explicit storage type now match
that caller's `CollisionCallback`; real local `FrameObject` access views pass each
object to the movement helper. These type corrections retain the existing
20-byte callback and 292-byte updater extents, controls and compiler profiles,
with no new C credit. The generic actor view's separate provisional field at
`+0xCC` remains unchanged. See [the factory path](FRAME_COLLISION_VARIANT_RESOURCE.md)
for the direct producer, field and boundary evidence.

The connected helper at `0x0802B3B8` matches all 28 bytes. It copies the two current
position words at `+0x18/+0x1C` to next position at `+0x20/+0x24`, clears velocity
at `+0x28/+0x2C`, and sets bit zero in the halfword at `+0xAC`. The movement-field
names reuse the existing actor access view. The wider halfword and the precise
meaning of that bit remain provisional. Two word-sized C temporaries preserve
its load/mask/store order without register constraints; the cast on the final
halfword store preserves all other flag bits. The wrapper is ordinary C too.

The helper's compiled flag-mask control (one to two) rejects one byte; changing
the wrapper's second object to the first also rejects one byte. The updater,
tick, action consumer and newly reconstructed choice builder were freshly
recompiled and rejected their own changed-source controls after the signature
refinement. The failed initial halfword-expression and bitfield candidates remain
in ignored raw reports. These static type and matching findings make no claim
about actual indirect-call or gameplay behavior.

## Unrooted actor detachment

The independently bounded entry at `0x0802F400` now has a
[C replacement](../src/frame/frame_detach_need_effect_actors_unrooted_2f400.c)
covering 48 bytes: 46 instruction bytes and two explicit zero alignment bytes
before the next entry at `0x0802F430`. It visits the canonical state's three
24-byte attachment records. For each non-null actor it calls
`frame_detach_actor(actor, state_address)`. That accepted helper compares the
state address against the actor's two attachment slots and clears the first
matching slot. The outer loop neither clears the records nor releases or
unregisters the state.

The provisional definition takes one state pointer and returns no value.
No actual incoming caller was recovered; historical unused formals remain
unknown. The state, all three records and each non-null actor's slot backing
must be live and aligned. The target-address cast is used only for pointer
comparison in the provider. No additional dereference or writer guarantee is
inferred.

Normal and strict qualification match the complete extent. Changing the loop
bound to omit record two rejects in both modes. Separate actual target and
provider definitions pass the API/layout checks; wrong return, provider formal,
record offset, stride and count cases reject. Alignment provenance does not
exclude alternate incoming execution. These static and compiler results add no
runtime or gameplay evidence.

## Unrooted attachment capacity check

The [predicate at `0x080461C8`](../src/frame/frame_check_attachment_capacity_unrooted_461c8.c)
rebuilds 56 bytes: 54 instruction bytes and two zero alignment bytes before
`0x08046200`. It first queries the actor's existing two-slot attachment counter.
If that byte result is nonzero and state byte `+0x60` equals one, it returns
zero. Otherwise it queries the state's existing three-record counter and
returns one only when that word count is below state byte `+0x5D`. These bytes
receive definition bytes `+0x21` and `+0x20` respectively during allocation.
The state threshold read occurs after the second call, as in the native body.
No header layout, provider contract or register binding changes.

The provisional definition returns a word zero/one and takes state and actor
pointers. No incoming caller was recovered; historical unused formals remain
unknown. The actor's two slots and state's three records must have live,
aligned backing. Counting non-null pointers does not establish the pointed-to
objects' lifetimes or a complete writer/serialized-input domain.

A shared failure path preserves the native branch and return-block order.
Normal and strict positives match the complete extent; changing `>=` to `>`
rejects in both modes and changes the result at exact capacity. Separate actual
target and two-provider definitions pass API/layout checks; six wrong return
or layout cases reject. The full-ROM and changed-source controls also pass.
No runtime, gameplay or incoming-root claim follows from this source gain.
