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
partial actor view's callback at `+0xCC`. The callback at `0x11328`, palette setter
at `0x30168` remain unconverted.

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
