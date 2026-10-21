# Definition row three: selection controller, moving event and row actors

This connected path has twenty-five matching C functions covering 4,812 bytes,
including their original literal pools and alignment. It follows selection input
through initialization, value updates, object creators and the installed event
and row updates, coordinate and vector helpers, animation resets, palette
requests and temporary-object removal. Row preparation at `0x08019640` (544
bytes), event drawing at `0x08019D80` (368) and line rasterization at
`0x08019EF0` (320) remain explicit original
dependencies and receive no C credit.
An exact source match does not recover those dependencies or establish gameplay.

The observed definition row at `0x080595B0` installs the reconstructed initializer
`0x08018B29` and the reconstructed no-argument controller `0x08018C71`.
The event creator installs `0x080190B1`; the row creator installs `0x0801925D`
at object offset 136. Both callbacks take one `FrameObject *`. The row creator
has an actual incoming word selector, stores its low halfword as the object ID,
and increments the scene's signed halfword active-row count. The callback and
creator declarations are checked against the actual reconstructed definitions.

The scene uses an observed 92-byte, four-aligned prefix within the existing
420-byte allocation: sound countdown at 10, signed active-row count 12,
sequence restore field 14, option 19, flags 21, primary/secondary/cursor pointers
24/28/32, observer slot 36, event slot 40, five eight-byte row-origin points 44,
sample handle 84 and three value bytes 88. The control root `0x03004350` has a
24-byte prefix, with refresh count 8, selection word/byte view 12, phase 16 and
timer 20. Temporary storage at `0x030038E0` has sixteen observed pointer slots
and a word count at 64 in a 104-byte prefix. Native writers establish delta,
origin, endpoint and step points at 68, 76, 84 and 92, followed by the horizontal
byte at 100. Typing the former opaque suffix preserves its size and alignment.
Complete original capacities and
ownership remain unproved; no one-element array substitutes for these prefixes.

Three line-drawing services add 580 C extent bytes: ensure-slot at `0x1A20C`
(104), plot-pixel at `0x1A274` (80), and update-slots at `0x1A030` (396).
They contain 542 instruction, 36 literal and two alignment bytes. The pixel
extent includes its natural zero tail after 78 instruction bytes; the former
78-byte map estimate omitted those two data bytes, not executable code.
Normal and strict full comparisons match, and each changed flags/pixel-value
control rejects by one byte. Actual allocation, animation, position, clear,
remove and event-step definitions remain exact in separate contexts; wrong
layout and formal contracts reject.

The updater reuses the canonical next-position word view, creates missing line
objects, positions the final object at the endpoint, copies tiles through the
existing BIOS service-0B glue and hides unused slots. The ensure-slot helper
retains its full-word index and original allocation assumptions. The pixel
writer clamps X only. Valid slot/count, object-zero, allocation, source-tile,
pixel Y/buffer and later-writer domains remain preconditions; these matches do
not establish all drawing inputs or hardware behavior. The parent draw and
raster bodies remain original dependencies.

The activity's object view is 224 bytes, four-aligned, within the separately
verified 320-byte allocation. It names only observed positions, velocity,
acceleration and destination points; ID/subtype at 8/10, flags 12, direction 18,
speed 20, amount/phase/outcome/palette bytes 76..79, countdown word 88, step
callback 136, D1 and D3 bit fields, D5 palette/layer fields and animation fields
216..223. The native D1 operation clears bits 2..3, not the generic actor view's
provisional three-bit interpretation. Local typed views preserve this concrete
role without changing the shared actor layout or callback API.

The initializer stores an actual returned observer pointer into slot 36. Its
local union preserves that pointer's word representation. Reading the stored
word and converting it back to the observed object pointer restores the original
reload after writes to the automatic point. This is a causal compiler finding,
not proof that game objects alias those local points at runtime. Attachment
reads require the actual successful result 1 and initialized signed-byte X/Y
outputs. The coordinate consumers read each component only after its real
provider write; no uninitialized aggregate copy or invented incoming value is
used to preserve registers. The original attachment resource currently has an
observed attachment entry, but arbitrary incoming objects/resources are unproved.

The controller retains one real local binding. At `0x08018D2A` the old full
selection word is held in callee-saved R4 across the actual input call at
`0x08018D38`. After the new selection word is stored from R1, `0x08018D40/42`
narrow the same old word to its low byte in place. That call-free byte phase is
consumed as the first refresh argument at `0x08018D48` and is dead before the
refresh call at `0x08018D4A`. The second argument is the new low byte; the next
refresh receives new/new. Both calls, cursor movement and cue happen even when
the selected values are equal. Removing the binding keeps 576 bytes but differs
in 41 bytes. The decrement helper below retains one separate call-free byte-pointer binding.

Five observed 56-byte row definitions begin at `0x08052B60`: speed 44 and four
byte thresholds at 48..51. Seven eight-byte phase records start at `0x08052C78`:
scale 0, threshold 4, probability 6 and frame delay 7. Three twelve-byte
background entries at `0x08052CB0` contain background pointer 0, palette pointer
4 and scale 8. Five four-byte option records at `0x08052B4C` provide three value
bytes. These are bounded local prefixes inferred from access strides and static
neighbor boundaries; they are not an inventory of all game data.

The direction helper takes four actual coordinate words in R0..R3. Unsigned
word subtraction defines the coordinate wrap before conversion to the signed
point passed to the existing angle provider. Four scalars and two grouped points
are both possible low-level source interpretations; the coherent C caller/callee
interface uses four scalars and a full unsigned return word. The existing angle
provider returns 0..31. The separate four-byte Thumb BIOS service-0A handoff at
`0x0804C8BC` is explicit assembly glue with zero C credit; the accepted service-0C
neighbor at `0x0804C8C0` is a different function. BIOS hardware behavior is not
established by matching or the finite memory model.

Normal positive/changed-source pairs cover all eighteen new functions and
22 accepted providers/dispatch contexts; strict diagnostics cover all new bodies.
Pinned compiler diagnostics check 74 layout facts and eighteen actual APIs,
physical bit masks and the pointer/word union; thirteen wrong headers reject.
A real omitted palette-queue declaration remains legacy-byte-identical but
rejects with strict declarations. The full current literal-header closure,
source/native function extents, pool relocations and natural zero tails are
separately audited. Whole-ROM acceptance and publication remain separate gates.

The finite packet executes 907 initialized cases: 903 bounded source-operation
cases and four angle-255 injections that test only the declared ABI. It records
345 real source-control divergences and seven deliberately rejected interpreter
or input cases. The actual input provider is separately executed in 24 zero,
directional and high-word cases; it supplies the word outcomes used by the
controller checks. A distinct wrong-old-selection source control diverges in
18 of 27 old/new cases. Predecessor fixtures incorrectly gated refresh calls on
unequal values; equal-selection checks exposed that model error, and the failed
model, raw bodies and corrected full replay are retained locally. The C source
and ROM were unchanged. Temporary pointers are unique initialized live objects;
the removal abstraction records the observed ID-FFFF tombstone. List, palette,
free-list and gameplay effects remain outside that abstraction. Direct children
use explicit provider hooks, with caller-saved poisoning and call effects; this
is bounded static/compiler evidence, not hardware execution or gameplay proof.


The initializer at `0x08018B28` and value refresh at `0x08019CF0` add 328 and
144 bytes. The actual background tile sequence is 31, 35, 39; the native tile
increment is four, and the earlier private 31/32/33 hypothesis was wrong.
An ordinary array-entry loop with a separately scoped doubled row recovers the
observed background and coordinate lifetimes without hints. The role now
contains the real `void display_fill_background(unsigned int,unsigned short)`
prototype. Omitting it still gives a legacy-identical initializer but fails the
separate strict declaration diagnostic. The refresh uses signed division by
eight for `114 + 16*lowbyte`, whose full range is 114..4194; the equivalent
arithmetic shift failed byte comparison despite identical bounded semantics.
Its first draw argument is tile `43 + 4*lowbyte`; pixel X is 32. The formatter
initializes its returned 16-byte local buffer before drawing reads any bytes.

The decrement helper at `0x08019A98` adds 96 bytes. It compares the full word
selector to two and one, selecting those banks and otherwise bank zero. It
unconditionally decrements an unsigned byte with modulo-256 wrap, tests only
the low 24 bits of the word at scene offset 88, and sets flag bit zero when all
three value bytes are zero. Both refresh arguments are the control selection's
fresh low byte. The published row update calls it at `0x08019486`; the original
linked-row update calls it at `0x08019A86`. Both load the full control word, so
a byte formal would change high-word selectors.

A local named union exposes the same 92-byte, four-aligned scene prefix as
existing state fields and an explicit word at 88. The three values occupy
88..90; byte 91 is storage read by the native word load and excluded by mask
`0x00ffffff`, not a fourth value. The actual common initializer requests 420
bytes from the zeroed allocator, which rounds and clears 432 bytes; this
establishes initialized word storage on the successful allocated-state path.
The view does not widen a three-byte array access into an out-of-bounds word
and does not establish a complete original state type or portable union ABI.

The helper's sole source hint is the real byte-pointer value in R1. Its three
branch assignments feed the load at `0x08019AC2` and final byte store at
`0x08019AC6`; R1 is dead before mask scratch reuse at `0x08019ACC` and refresh
at `0x08019AE2`. There is no intervening call or overlapping live value.
Removing the hint gives 100 bytes with 77 differing bytes under both compiler
profiles. A separate root-address R2 hint proved unnecessary and was removed;
the ordinary root address is consumed by the actual fresh-state reload at
`0x08019AC8`. The changed decrement control keeps 96 bytes but differs in one.

Private finite evidence for this extension has 1,129 cases: 90 initializer
cases (30 ordinary, 60 deliberate abstract effects), 189 refresh cases (144
ordinary, 36 deliberate abstract effects and nine NULL-formatter ABI-only
cases), and 850 initialized marker cases with an abstract refresh call. The
marker control diverges in all 850, a low-byte-selector error in 255, and a
wrong fourth-byte mask in 68. The unbound but byte-mismatching marker remains
model-equal in all 850. The omitted fourth byte is explicitly rejected. These
bounded interpreters compare native memory, calls and writes; they do not
execute rendering hardware or establish gameplay reachability or behaviour.


The linked-row update at 0x0801994C adds 332 bytes of ordinary C with no
source register bindings. The row callback has two source control-flow uses
which the compiler tail-merges into one native BL at 0x0801952E; both source
identifiers receive only the same-address canonical helper name. The helper
reads the observer attachment and checks the next position against a five-pixel
vertical band. An on-screen point outside the band returns unchanged. Completion
clears the linked event and decrements the active-row count; the in-band path
loads its row background, adds 20 + 5*subtype + amount*(subtype+2), increments
the completion counter, and coordinates the sequence/timer restore fields.
Both completion paths then request the full-word-selected value decrement.

This names actual byte 91 as the completion counter, separate from the three
value bytes. It confirms why the marker's aligned word mask excludes that
upper byte. The five 56-byte row records occupy 0x08052B60..0x08052C78;
background pointer 36, unsigned sequence halfword 52 and timer halfword 54 are
native loads, with an explicit low-byte sequence conversion for the real audio
formal. Record/scene sizes and all earlier offsets stay unchanged. The count
0..4, subtype 0..4 and amount 0..255 bound ordinary table and score accesses;
two count 254/255 fixtures are explicitly ABI-only rather than ordinary game
states. Complete object/resource reachability remains unproved.

The ordinary source preserves a genuine base-score assignment expression used
by the actual score argument. Native 20+5*subtype is produced before the amount
load, then added to the real product. Operand-order and separate local variants
remained 332/12 or 332/8; the used expression closes the full extent without
invented dependencies, extra traffic or hints. The changed outcome control
gives 336 bytes with 226 differing bytes under both profiles.

The actual observer resource has ten frames and attachment zero in each.
Its provider writes both signed-byte point components before the first C read.
The native point lives at entry-SP minus 28, after a 20-byte register push and
16-byte local frame. A first private model used the wrong stack address;
memory and writes agreed but the attachment call argument exposed the error.
That failed trace is retained, the model was corrected from the prologue, and
the wrong-frame model remains a rejection control; no source change caused
the correction. Arbitrary resources or failed attachment outputs are not
assumed initialized and receive no new guard in the recovered C.

The 262 bounded model cases include 30 cases from every actual observer frame,
twelve deliberate abstract provider effects, two ABI-only high counters and
an initialized object-alias case. The outcome control diverges in 192; early
returns correctly remain unchanged. Ten invalid model inputs are rejected.
Background, audio and decrement calls remain abstract hooks, while score
effects follow its accepted C body as a model. These are not nested native
provider execution or hardware/gameplay evidence.

## Preparation worker: current causes and input bounds

Preparation at `0x08019640` still has no accepted replacement. Its native
544-byte extent contains 522 instruction, 20 literal and two alignment bytes.
A private source now separates the call-free phase search from the phase saved
on its successful edge. The selected-row and working-phase inductions survive;
of the two phase values, only the accepted snapshot crosses later calls.
A four-word eligibility view and a short state-root
snapshot also recover the native memory-backed flags and one root load for the
three availability reads. That composition emits 532 bytes with 480 differences.
It does not recover the native frame or value homes.

A separate diagnostic starts from the ordinary scalar phase-split source and
constrains only the actual persistent object owner to native R8. Every object
use, including the final position argument, uses that
owner; the incoming duplicate dies before any random call. The actual providers
preserve R8. This confirms the owner lifetime but emits 536 bytes with 499
differences and displaces amount, palette and availability values. One subsequent
composition also preserves the actual native amount in R10 and palette in R9.
All three homes survive, but the result is 536 bytes with 492 differences and
a 48-byte frame rather than 52. The selected-row and accepted phase-snapshot
homes now agree; the accepted flag, availability values and output arguments
do not.
This closes that register composition. Further bindings, stack records or
declaration-order searches need a distinct storage or lifetime fact.

The fixed tables establish a conditional bound for option 0..4: selection stays
within the five row records, phase indices stay within 0..6, and acceptance
follows at most eight amount reductions without signed underflow. The successful
progress writer stores only 1..4 into a backed `values[scene]` destination when
the request's option is at most three; option four skips this write. This does
not establish monotonic progression or every incoming option. The same bytes at
world `+0x735` are restored by the saved-nibble reader, which permits 0..15.
The serial controller supplies literal option two on its named request route;
mode three is an additional premise for reaching this activity.
Complete request, validation, backing and later-writer populations remain open.

The named maintained routes also supply at least one available palette bank.
Each valid option initializes a nonzero bank before row creation. The decrement
helper sets completion flag bit zero when all three resulting values are zero;
the controller tests that flag before its later row-creation loop. Its own flag
updates preserve bit zero. This argument requires live distinct backing and no
other value/flag writer or interleaving during creation. It does not prove the
deterministic random sequence selects an available bank.

The ordinary creators pass row IDs 0..4. With at most four initialized prior
origins and representable coordinate arithmetic, the coordinate rejection test
always has a valid candidate: on the two permitted Y boundaries, 32 and 104,
there are 418 X/Y pairs. Each prior origin can exclude at most 63 pairs on only
one boundary, leaving at least 166 pairs. This proves geometric feasibility;
the deterministic random sequence has not been proved to reach those pairs.
Complete palette-writer populations, retry termination, arbitrary IDs and
gameplay remain open. No source guards or new C credit accompany these facts.
