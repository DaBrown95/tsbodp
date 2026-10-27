# Actor-palette menu scene lifecycle

The audited phase table's row nineteen connects initialization `0x08013F3D`,
state dispatch `0x08015F69` and shutdown `0x0801405D`. These three ordinary-C
functions add 564 original extent bytes and connect the previously reconstructed
[actor/palette menu](ACTOR_GROUP_BINDING.md) and its transition path. Two state
handlers remain explicit original dependencies; matching these scene callbacks
does not establish complete reconstruction or runtime behavior of this menu.

| ROM extent | Function | Bytes |
| --- | --- | ---: |
| `0x13F3C` | `scene_palette_menu_initialize` | 288 |
| `0x1405C` | `scene_palette_menu_shutdown` | 112 |
| `0x15F68` | `scene_palette_menu_step` | 164 |

## Initialization and shared state

Initialization allocates 308 zeroed bytes and stores the pointer at
`0x03001954`. The observed word at allocation offset zero receives 25 and
later bounds the available-object slots; its existing `initial_word` name is
retained. The pointer at `+0x130` receives existing game-state storage at
`0x03003978`, or game-state `+0x28`. The partial structure now records the
twenty-five pointer slots at `+4` and five rows of ten pointers at `+0x68`,
preserving the 308-byte allocation and four-byte alignment. The parameter
pointer retains its existing opaque type; its byte interpretation is local
to the observed count accesses.
Allocation failure is unchecked, as in the original.

The shared request receives scene zero, transition/state word `+0x10` zero
and timer `+0x14` thirty. All fifteen words beginning at `0x03001918` are
cleared; the existing menu-choice declaration and its accepted consumers are
reused. Four background controls at `0x08051F60..0x08051F6C` configure layers
zero, three, two and one. Layers zero, two and one are filled with zero. The
layer-zero control also selects the text background. An original palette is
loaded through the canonical word-argument palette interface; no palette bytes
are embedded in the reconstructed source.

The existing exit-object array at `0x03001958` is cleared for 32 bytes. Its
count byte at `0x03001978` and the following control byte at `0x03001979` are
cleared separately. These are the same views used by the accepted transition
routine; their complete ownership and valid count domain remain unproven.
The timer is then set to thirty-one. The intervening provider calls can observe
the earlier thirty, so both stores are retained. Initialization loads layer
three's background, sets both velocity coordinates to 65,536, selects sequence
one and runs the first transition with `(63, 0)`.

## State dispatch and shutdown

The state dispatcher reads the shared request word at `+0x10`. Its complete
switch owns the fifteen-word jump table at `0x08015F84` and the following call
blocks through `0x1600A`, plus two zero alignment bytes. Explicit empty cases
seven, thirteen and fourteen reproduce the original table and upper bound;
values above fourteen return without calling a handler. An initial implicit-
default model omitted the two high empty cases, emitted 156 bytes and failed
comparison. The accepted switch needs no manufactured work or register binding.

| State | Observed target | Current source status |
| ---: | --- | --- |
| 0 | `scene_palette_menu_phase_0` | Matching C |
| 1 | `scene_palette_menu_phase_1` | Matching C |
| 2 | `frame_step_palette_menu_transition` | Matching C |
| 3 | `frame_step_palette_menu` | Matching C |
| 4 | `scene_palette_menu_phase_4` | Matching C |
| 5 | `scene_palette_menu_phase_5` | Matching C |
| 6 | `scene_palette_menu_phase_6` | Matching C |
| 7 | Empty case | Part of this dispatcher |
| 8 | `scene_palette_menu_phase_8` | Matching C |
| 9 | `scene_palette_menu_phase_9` | Matching C |
| 10 | `scene_palette_menu_phase_10` | Matching C |
| 11 | `0x080152D0` | Original |
| 12 | `0x080153EC` | Original |
| 13, 14 | Empty cases | Part of this dispatcher |

The original-target declarations use state-number names until their bodies
provide semantic evidence. They are address handoffs and receive no C credit.
The accepted handlers connect row choice, character entry, text drawing, actor
resources, input and transitions to this lifecycle.

Shutdown copies the low bytes of the first seven choice words into the existing
game-state selectors at `+0x20..+0x26`. The eighth selector is left untouched.
It then runs the second transition, releases the primary object list, resets
display and palette jobs, clears scene-object slots and frees the allocation.
The global allocation pointer is not cleared. This matches the existing actor
updater's selector widths and storage while preserving the observed operations.

## Verification and connected declaration correction

All three functions match without register bindings or added traffic. Their
complete extents include literal pools, the switch table and zero alignment.
The shutdown ends at the independently accepted constructor `0x140CC`;
the dispatcher ends at the next prologue `0x1600C`. Controls change allocation
size, the final selector's source choice and the dispatch word; all must reject.
Current accepted constructor, updater, row-choice/draw, outer input and
transition callers/providers are rechecked without duplicate coverage.

This batch also corrects the scrolling-text header to explicitly declare
`display_load_palette` and `display_load_palette_alternate` with their accepted
`void(const void *, unsigned int, unsigned int)` interfaces. Its previous
initializer relied on C89 implicit declarations. All twelve scrolling-text
sources and their controls are refreshed with the explicit types, with zero
additional C credit. Useful failed declaration, lifetime and switch models
remain local. Static connections and source/byte matching remain separate from
runtime, hardware-timing and gameplay claims.

## State-zero entry and preparation

Two ordinary C providers add 660 matching extent bytes: state zero at
`0x0801553C..0x08015728` owns 492 bytes, followed by the 168-byte preparation
helper through `0x080157D0`. State one is the independent entry reconstructed
below.
The complete pools and alignment belong to these two extents. No register
bindings, new guards, volatile accesses or extra calls and stores are required.
The lifecycle above and the previously reconstructed transition/update handlers
remain distinct connected sources with no duplicate credit.

State zero snapshots the request's full phase word and returns immediately when
it is nonzero. Only the zero-phase path captures the timer word. At timer 31 it
prepares the entry and plays cue 12. Timer 30 sets window one, configures its
control, starts scroll and window moves, enables backgrounds one and zero and
prepares the object slots. Slots 13 and 14 receive IDs 129 and 128; the fresh
request scene decides which receives flag one, need timer 16 and variant 56,
while the other clears flag one and receives variant 58. Scene three reverses
those roles. Slots 8, 12, 15, 16 and 10 receive IDs 131, 130, 135, 136 and 132,
need timers 14, 16, 15, 15 and 15, and variant 56. Object pointers and indices
remain unchecked.

At timer 15, the helper reconfigures window one, enables background two, starts
its scroll and the second window-move view, writes the captured zero phase to the
request parameter and prepares slot 11 with ID 133, need timer 15 and variant 56.
Timer one disables window one; timer zero sets the phase word to one. Other
timers perform none of these branches. Every zero-phase path then decrements
fresh global timer storage, including after provider calls, rather than storing
an arithmetic result from the earlier snapshot. This preserves possible provider
changes to that storage without claiming a runtime trace.

The first of the three 15-valued halfword stores uses an ordinary one-member
`PaletteTimerCell` access view of the existing `need_timer` field at actor
`+0x5E`. Explicit packed, two-byte alignment gives the view size and alignment
two under the pinned compiler, preserving the original halfword store. The
compiler's plain aggregate would have size and alignment four, exceeding this
field's observed alignment. This is no new allocation or complete actor layout.
The word timer assigned during that actual
store supplies the two following stores. A plain halfword-pointer predecessor
kept the object base and omitted a subsequent native table reload, failing by
eight bytes. The cell view preserves the original destructive field-address
calculation, timer value and table reload with no additional traffic. The exact
compiler alias/lifetime mechanism is inferred from the output, while the field
width, address and full byte match are directly checked. Failed forms and raw
comparisons remain private.

Preparation clears backgrounds zero, one and two, selects font one with fill
minus one, loads the two original backgrounds and the established entry palette,
and invokes the C-owned template walker with tile one and word argument 37.
It sets all three background scroll targets with word duration one before calling
the entry-object builder reconstructed below. The template declaration returns a word and
accepts word arguments plus a pointer to eight-byte records containing signed
halfword x/y, byte width/style and halfword text. The pinned compiler gives this
eight-byte record four-byte alignment; the template root at `0x08052444` and its
eight-byte stride satisfy it. Static layout checks independently establish offsets
zero, two, four, five and six. A private width-byte-to-word control fails the
layout checks while this pointer-passing helper still matches, distinguishing
layout evidence from caller-byte equality. The ignored word result and
proper record-pointer type retain the original 168-byte helper. The former
private void/untyped declaration is excluded from canonical interface evidence.

The 160-byte template walker at `0x08044F00..0x08044FA0` is now C-owned,
including its pools and alignment. Its existing typed header connects both
palette-menu callers to the recovered provider. Incoming counts, complete
template populations and buffer backing/capacity remain open; see the
[template reconstruction](DISPLAY_TEXT_RECONSTRUCTION.md#template-record-walker).
The 336-byte object builder is reconstructed
as part of the following character-entry path. Its accepted text decoder/drawing/font/buffer context,
the actual background, window, variant and audio providers, the lifecycle caller
and incoming background-enable wrapper are verified separately.

Fresh canonical positives and changed-source controls cover both complete
extents and the current connected providers/callers. Controls change the timer
value in the actual halfword store and the template word argument. Source,
literal current-header dependencies, allocated native sections, symbols, original
addresses and pools are pinned; stricter implicit-declaration warning-as-error
builds run outside the unchanged acceptance profile. These are static and
compiler/link claims, not gameplay, object-capacity, template-content or complete
menu reconstruction claims. Six state targets remain original.

## Character entry, cursor and object handoff

Four connected functions add 1,364 matching C extent bytes. State one is called
by the accepted state dispatcher, uses the cursor and character-bank helpers,
and reuses the entry objects created by the state-zero preparation. The object
builder also handles the mode-seven exit-object handoff into the accepted
position-movement and scene-object callback path.

| ROM extent | Function | Bytes |
| --- | --- | ---: |
| `0x157D0` | `scene_palette_menu_phase_1` | 792 |
| `0x15AE8` | `scene_palette_menu_refresh_cursor` | 128 |
| `0x15B68` | `scene_palette_menu_build_entry_objects` | 336 |
| `0x1600C` | `scene_palette_menu_refresh_character_bank` | 108 |

State one reads the local player's halfword pressed-input value from the
canonical local array at `0x03004250`, widening it to a word. The linked array
at `0x03004228` is a separate view. Input priority is confirm, cancel, the two
bank-toggle bits, then up, down, left and right. One semantic word is bound to
R1 to preserve native allocation. Every use of that input word precedes the
first call in its selected branch; it is never expected to survive a call.
Original control-flow checks and fixtures that poison caller-clobbered registers
establish this limited lifetime. Both display helpers and the builder use ordinary
C without register bindings, volatile accesses or added traffic.

Confirm on scene three clears sixteen bytes of the existing game text field,
then appends the resources identified by each exit object's halfword at `+0x0A`.
That halfword is distinct from the object ID at `+8`. A nonempty entry selects
phase two, timer thirty and parameter seven for mode seven or six otherwise;
empty confirmation plays cue three. On the other scenes, the count-greater-than-
seven guard applies only to adding a character. It creates a label from the
word resource table, positions the first at `(67,37)` in fixed-point units and
places later labels four pixels after resource IDs 93 or 96, or nine pixels after
other resources. It stores the resource ID, increments the byte count and plays
cue one. Cancel decrements a nonzero count and marks a nonnull removed object;
empty cancel selects phase two, timer thirty and parameter thirteen.

The two bank-toggle input branches invert the existing byte at `0x03001979`,
redraw the character bank and play cue one. Up and down cycle scenes zero through
three; entry into scene two adjusts the selected parameter to the observed
first/last range. Left and right wrap within the selected range except on scene
three. The entry records at `0x08052418` have a four-byte stride, with first and
last at offsets zero and one and two uninterpreted bytes. The resource table at
`0x08052694` uses bank, row and entry strides of 208, 52 and four bytes. Its first
dimension and actual storage capacity remain unbounded declarations rather than
invented complete tables.

The cursor helper treats scene three separately, clearing flag one in slot
thirteen and setting it in fourteen. On other scenes its conditional tests
whether *any bit other than bit zero* is set in slot thirteen, then sets bit zero
and clears it in slot fourteen. It reads the selected unsigned halfword x and
byte y coordinates, shifts their native bit patterns into fixed-point arguments
and plays cue zero. This preserves unchecked index and signed-argument behavior;
it does not establish portable arbitrary-coordinate arithmetic.

The bank helper clears background zero, selects its text control and font, and
reads the bank flag after that font call. It chooses the original eight-byte
entry records at `0x08052444` or `0x0805256C` and passes word arguments `(1,37)`
to the C-owned template walker. The latter root follows thirty-seven eight-byte
records; neither root is asserted to own a complete table. Slot twelve's ID
toggles between 134 and 130, with all other IDs selecting 134. Its fresh pointer
is then passed to variant state 58.

Outside mode seven the builder creates six scene objects and two labels through
accepted constructors and text providers. The actual first constructor result
is obtained before initializing the object-table pointer; a separately scoped
last-object pointer recovers the native register lifetimes without manufactured
work. In mode seven a fresh byte count controls each loop iteration. Each exit
object receives the accepted scene-object callback, state fourteen, an observed
halfword timer store of eighteen, a position move toward y 37 with duration
nineteen, one movement step and variant three. The begin provider writes its
duration over that timer under the established movement protocol; the following
step reduces it to eighteen in normalized fixtures. The nullable menu object
in slot seven is marked for removal, and the request scene becomes three. The
existing actor-field access view is used only for this timer at `+0x5E`; it does
not classify every created label as a complete actor.

Pinned compiler layout diagnostics establish the four-byte range size and
alignment, record offsets, word resource strides, eight-byte template with
four-byte alignment, local-input byte/halfword interfaces, request words and the
observed object fields. The range and template roots and their strides satisfy
those alignments. The timer is a genuine two-byte primitive at the existing
object-base offset, rather than an incorrectly aligned plain one-member
aggregate. Widening the range field, narrowing resource IDs and imposing
one-byte range alignment each fail separate layout assertions. These diagnostics
claim no C coverage and are separate from byte matching.

All four complete extents, including interspersed pools and alignment, have
current canonical positive and actual changed-source negative proofs. Controls
change the add guard, the cursor's real flag predicate, the template argument
and the movement duration. Current accepted callers, input producers and text,
object, movement, background and audio providers are freshly checked; the
template walker's 160-byte body is now C-owned. Its template-table and buffer
population limits remain open. Separate strict declaration builds reject
implicit interfaces without changing acceptance compiler flags. Useful failed
pointer-lifetime and discarded-control forms remain local.

The finite checks cover 35 input cases, 36 cursor/bank cases and fifteen builder
cases, using generated normalized objects and abstracted callees. They execute
the linked functions and original extents, check callee-saved registers and
reject unsupported instructions, missing bytes and exhausted execution budgets.
Called-provider models, normalized movement, scenes zero through three and
counts zero through eight bound these checks. Real label resource lengths,
allocation success, index validity and capacity remain unchecked. In particular,
the append provider's request for 1,024 bytes after a sixteen-byte clear does not
establish safe capacity for arbitrary strings. These results do not prove whole
menu behavior, hardware timing or gameplay.

## Selector input, confirmation and redraw

Three connected functions add 696 matching C extent bytes: selector input at
`0x14B40..0x14CB0` owns 368, confirmation at `0x15270..0x152D0` owns 96,
and the redraw helper at `0x14A58..0x14B40` owns 232. The complete extents
include their literal pools and zero alignment; the adjacent navigation body
at `0x14834..0x14A58` remains an explicit original dependency with no C credit.

Selector input reads the selected player's linked pressed-input halfword from
`0x03004228`, separately from the local array used by character entry. Confirm
mask nine has priority over cancel mask two and directional mask 240. Confirm
returns without a handoff when the allocation's initial word is nonzero;
otherwise it selects state ten, timer thirty and parameter five. Cancel selects
the same state and timer with parameter six. Both play cue twelve. Directional
input calls original navigation, then redraws the previous and fresh selected
scenes when they differ. Fresh scene thirteen or fourteen hides slots three,
four and six and shows five. Other scenes update three IDs and variant 58,
with fresh object-table reads after variant calls. The selected value supplies
two original palette entries at byte offsets `2 * (11 - value)` and
`2 * (value + 1)`, loaded at indices 65 and 81, except on scene thirteen.
No arbitrary index, value, object-lifetime or palette-capacity check is added.

The redraw helper reads the enabled flag before selecting font three and its
fill mode. Scenes eight through twelve draw two text resources on a row at
`20 * (scene - 8) + 43`, using separate resource offsets 460 and 455; the first
word draw result is narrowed to the observed halfword for the second draw.
Scene thirteen clears a rectangle and draws the selected resource with offset
451. Scene fourteen draws resource 31 only when the initial word is zero.
The enabled declaration now covers the observed fifteen-byte prefix at
`0x08051FA0..0x08051FAF`, including the actual selector reads through index
fourteen. The separate count declaration remains eight bytes at `0x08051F70`.
This extends a partial access view, not an allocator or universal table-capacity
claim. The original navigation and earlier choice/draw providers corroborate
these reads; all sixteen accepted literal header importers are rechecked.

Confirmation uses the same linked input snapshot. Mask nine selects state
twelve, timer fifteen and parameter fourteen; otherwise mask two selects the
same state and timer with parameter nine. Both play cue twelve. Its three
semantic register bindings hold the actual input-root pointer, shared mask-nine
value and computed mask result. The root dies at the indexed read, the shared
value is last used at the cancel parameter store, and each computed result dies
at its branch test. All uses precede either mutually exclusive cue call. The
selector handler's single directional-result binding also dies before its first
call. Neither function adds synthetic initialization, volatile accesses or
extra traffic; redraw uses no register bindings.

Fresh positive and changed-source controls cover all three full boundaries and
current accepted callers/providers. Controls change the real direction mask,
confirmation parameter and redraw range. Separate strict declaration builds
reject missing navigation and cue prototypes without changing acceptance flags.
Pinned compiler checks establish fifteen byte flags and eight byte counts;
the former eight-flag declaration and a widened flag-element control reject.
The finite checks execute original and linked bodies with abstracted callees
that poison caller-clobbered registers. They cover 39 selector, 30 redraw and
116 confirmation cases, preserve mask priority and reject unsupported
instructions, missing pools and exhausted execution budgets. Selector values
zero through fourteen, initialized object slots, values zero through eleven and
input indices zero through three bound these checks. Navigation, text, variant,
palette and audio providers are abstracted; these checks establish no gameplay,
hardware timing, arbitrary storage validity or complete menu reconstruction.

## Remaining selection transitions

Seven connected C functions add 2,112 complete extent bytes. Four timer handlers
at `0x14584`, `0x146E4`, `0x14CB0` and `0x14F08` own 352, 336, 600 and
516 bytes. Their directly called selection-label constructor at `0x16100` owns
96 bytes; background handoffs at `0x16078` and `0x16160` own 136 and 76.
All boundaries include their original pools and alignment. The apparent region
after state ten contains independent entries: the selection-list builder at
`0x1510C..0x151C4` and the release helper through `0x15270` now have source
as described below. Navigation remains unconverted; the following
text-transition section covers states eleven and twelve separately.

State six acts at timers thirty and fifteen, prepares window/background moves
and object slots, redraws rows zero through seven, then enters state three at
zero. State eight reverses those moves and selects request, entry or selection
handoffs from the parameter word. State nine prepares rows eight through
fourteen, uses two distinct actual object-table snapshots around the branch's
variant call and loads the selected pair of palette entries. Its real ID-eleven
assignment supplies the later palette-offset base; no unused initialization or
additional read is introduced. At zero it invokes the matching list builder
before checking the fresh owner word and updating slot eight's visibility.

State ten invokes the list release, reverses object/window movement,
then selects a queued request, state six or the selected-exit background path.
Its final three scroll calls need five short register constraints: the first
and second hold their actual layer and X arguments in R0/R1; the third holds
only its actual layer in R0. Each value dies at its own call, with no intervening
call, unused value or added memory traffic. Four other initial constraints were
removed while preserving all 516 bytes. The other six functions have none.
Every handler reloads and decrements the real timer at the common exit;
stores of thirty-one or sixteen therefore become thirty or fifteen there.

The label constructor allocates object kind twenty-four, narrows its word ID
to the existing halfword, sets flag one and the existing palette/layer bitfields,
installs the original animation record and scales both incoming word pixel
coordinates by sixteen bits. Allocation failure and arbitrary coordinate or
resource validity remain unchecked. The pinned compiler measures both existing
object access views at 312 bytes with four-byte alignment; the accepted allocator
reserves 320 bytes. The unused eight-byte tail is not described by either view.
The mode-seven handoff sets its initial
background Y to negative one hundred in fixed point, then requests positive
one hundred as a later scroll target. These are separate observed operations.

The owner remains a partial 308-byte access view. The builder and release show
pointer slots and byte-derived loop counts; neither establishes valid serialized
counts or guards the represented capacity. The builder remains original and
both helpers retain their no-argument, effect-only calls. Current canonical
source/control proofs for this seven-function batch cover all seven functions and
25 accepted direct callers/providers, with seven additional strict diagnostic
pairs. Twenty-nine pinned layout/type checks and four mutated-header cases
establish the actual access views; two missing-provider declarations are rejected
by the strict diagnostic even when their legacy byte comparisons still match.
Removing each of the five final scroll argument constraints separately changes
native bytes while preserving the actual value and scope. These diagnostics do
not count as additional C coverage.

The builder's bounded R5-column trial remains a nonmatch: 176 emitted bytes
and 163 differing or missing bytes against the fixed 184-byte native extent.
The column's actual R5 lifetime spans both constructor loops and the real
callee-saved constructor calls. The binding survives all intermediate stages;
the first causal failure is LOOP's induction recognizer, which accepts only
pseudo-register candidates. It therefore recalculates column-derived X and
slot offsets instead of retaining the native increments. This composition is
closed without another binding or profile grid. Five fresh byte-count row
loops decrement an initial available count of 25 before the remaining-slot
loop; the native code supplies no capacity or total-count guard.

The five row counts now have an identified save-input origin. Initialization
points `parameters` at game state `+0x28`; bytes two through six are the five
`SaveStreamSixNibbles.values` bytes written by
[the six-nibble reader](../src/save/read_six_nibbles.c). The
[world-record loader](../src/save/read_world_record.c) reaches that record at
game `+0x10+0x18`. A completed load with valid backing and no later writer
therefore gives each count a range of `0..15`. It does not prove the ten-slot
per-row capacity or the total of 25 available objects. The builder already
reloads these bytes after constructor calls; this backing identity supplies
no missing source dependency or new matching-code credit.

The 178 finite cases independently execute original and linked bodies against
normalized call models, check callee-saved state and poison caller-clobbered
registers. They include zero and maximum-word timers, the observed handoff
parameters, both owner-count branches and native coordinate wrapping. All seven
real source controls diverge in these cases; unsupported instructions, missing
pools and exhausted execution budgets are rejected separately. Called providers,
allocation, original list operations and window/background hardware are
abstracted; no complete menu, gameplay or arbitrary capacity claim follows.

## Selection object construction

The builder at `0x1510C..0x151C4` owns all 184 C extent bytes: 178 instruction,
four literal and two zero-alignment bytes. It starts the available word at 25,
visits five groups using parameter bytes two through six, and creates each
object at `(106 + 3*column, 46 + 20*row)`. Each grouped store decrements that
word. It then creates the remaining available objects at `(83 + 3*column, 28)`.
The owner and parameter/count reads retain the native observations around the
factory calls; allocation failure and malformed counts remain unchecked.

The ordinary source reuses the actual column and returned object word across
the two loops, while each post-call owner has its own body lifetime. This
recovers the native induction and result staging without register bindings,
additional reads or unused work. The object address is carried through an
unsigned word and converted back only for its real pointer store, using the
pinned 32-bit target representation.

Normal and strict-aliasing/warning builds match; changing the initial count to
24 rejects. The actual factory, timer-nine caller, release and initializer also
retain their complete bytes and reject their real controls. The shared owner
still represents 308 allocated bytes, 25 available slots and five groups of
ten. Per-row counts at most ten, totals at most 25, live parameter backing,
valid owners and nonnull object allocation remain source premises. This adds
no runtime or gameplay claim and establishes no wider count/writer domain.

## Selection object release

The independent function at `0x151C4..0x15270` adds 172 complete C extent
bytes, including its sole owner-pointer literal. Its ordinary C source uses
no register bindings and makes no calls. It visits five groups, reads each
count from parameter bytes two through six, sets flag two on the pointed-to
object and clears that pointer slot. It then does the same for the available
slots bounded by the owner's word at zero. It does not deallocate objects or
reset either count source.

The real five-row do-loop and existing parameter-member offset give the
original allocation without synthetic initialization or additional accesses.
Both former annotations were removed together while retaining all 172 bytes;
the earlier mismatches and annotated match are retained privately. The group
loop reloads the owner at each actual body iteration and rereads its parameter
pointer/count after the two stores. The available loop likewise reloads the
owner at each body iteration and rereads its count from that iteration's
owner snapshot. No interrupt or opaque provider mutation is assumed.

The pinned compiler checks the existing owner size/alignment and all observed
pointer offsets, row stride and widths. Wrong available prefix, row stride,
count width and parameter byte interpretation fail the corresponding layout
checks. The actual changed-source control sets grouped-object flag four instead
of two and fails the byte comparison. Strict declaration builds also use the
complete canonical header graph.

Ten finite fixtures execute the original and linked bodies for counts within
the represented 25 available slots and five rows of ten slots. They include
zero counts, skipped null slots and repeated valid object pointers. Seven
fixtures distinguish the changed flag; attempted null accesses are rejected
as uninitialized-memory inputs in both interpreted bodies, without a new
source guard or a claim about hardware faults. Native read/write traces pin the real
root/count reloads. These normalized fixtures do not validate arbitrary
serialized counts, pointers, aliasing, allocation failure or gameplay. The
548-byte navigation routine remains explicitly original; the builder above
now has a verified source owner.

## Selected text transitions

States eleven and twelve add two complete C extents, 284 bytes at
`0x152D0..0x153EC` and 336 at `0x153EC..0x1553C`. Both include all original
literal pools and alignment; the latter ends at the separately reconstructed
entry handler. The existing full state dispatcher calls both no-argument,
effect-only providers. State ten selects eleven with timer sixteen, and state
five selects twelve with timer fifteen. No navigation or list-helper coverage
is added by these two functions.

State eleven retains the observed timer-thirty branch without an action. At
fifteen it moves the window and backgrounds, selects scene zero and font three,
draws text resources 33, 34 and 35, enables backgrounds one and zero, then
updates IDs and animation timers in slots eight and nine. The full-word return
from drawing all lines supplies the first line call; that line's full-word
return supplies the second. Its actual style-one value is bound to R5 across
the text lookup and consumed as the all-lines stack argument, then dies before
the returned tile value reuses R5. The natural unbound spelling remains a
preserved mismatch. At one the window is disabled; at zero state five is
selected. The common exit decrements the freshly read timer, including the
native unsigned wrap from zero.

State twelve starts reverse window/background movement at fifteen, updates the
same two object timers and variants, and hides the backgrounds/window at one.
At zero, parameters fourteen and thirteen request default scenes twenty-five
and five. Parameter nine stores state nine and timer thirty-one, loads the
mode-seven backgrounds/palette, sets an initial background Y of negative one
hundred in fixed point, and requests positive one hundred as a later target.
The window move's observed axis argument is zero in both handlers. Its common
fresh timer decrement turns the new thirty-one into thirty.

Nine remaining state-twelve register bindings hold only actual position and
scroll call arguments. The position call and first scroll each bind their layer
and X values to R0/R1. The next scroll additionally binds its Y argument to R2;
the final scroll binds only its layer and X values. Every value dies at its own
call, with no intervening call or added memory traffic. The initial tenth
binding on the final Y argument was removed while retaining the complete
extent. Separate removal checks preserve each actual value/scope and change
native bytes for all nine retained bindings.

Both handlers use the existing object views and halfword timer at byte 94; no
new aggregate layout or storage capacity is introduced. Object slot nine is an
observed original access, not a declaration of the complete table extent.
The text pointers, dimensions and backing buffer capacities remain unchecked.
Finite instruction checks use initialized slots zero through nine, boundary
timers and selected parameter words, with abstract text/background providers.
Three specified full-word all-lines return values exercise the subsequent
line-return chain. Real timer-fifteen-to-fourteen source controls diverge at
both thresholds; caller-clobbered registers are poisoned, and unsupported
instructions, missing pools and exhausted budgets reject. These checks do not
execute real strings, rendering hardware or gameplay.

Current positive and changed-timer source controls cover both complete extents
and 22 accepted dispatcher, state-producer and direct-provider functions,
24 real pairs in total. Two additional strict pairs check the new source's
explicit declarations. Eighteen pinned compiler layout checks and five
callback/provider type assignments establish the unchanged word, halfword,
size and alignment contracts; four mutated-header cases reject. Removing both
actual lookup declarations or the all-lines declaration can leave legacy bytes
identical, but the strict diagnostic rejects those missing prototypes. Ten
separate annotation-removal diagnostics cover the style and nine argument
values; every retained annotation changes native bytes when removed. All 72
finite fixtures agree with the normalized call model and both real controls
change observed behavior. These diagnostics add no C or glue credit.
