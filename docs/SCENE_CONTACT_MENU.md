# Contact scene controller

The flat scene table at `0x0805797C` has row 20 values `0x08028A11`,
`0x08028BD1` and `0x080292ED`. The accepted contact-resource tick submits
kind 20 through the scene request provider. This identifies a connected scene
path; the names below describe static accesses and are not recovered original
identifiers or a claim about gameplay.

This connected path reconstructs thirty-two C functions, totaling 5,692 bytes:

| Entry | Bytes | Observed role |
| --- | ---: | --- |
| `0x08028A10` | 448 | Initialize the contact display, state, selected labels and notice handler |
| `0x08028BD0` | 556 | Advance phases 0 through 6 and dispatch activity, notice and return operations |
| `0x08028EBC` | 124 | Refresh the amount text when state flag 8 is set |
| `0x08028F38` | 184 | Clear display storage and start the selected activity, clock text and transition |
| `0x08028FF0` | 264 | Load the completion background, selected label and explanatory text |
| `0x080290F8` | 188 | Check two unsigned parameter results and a signed amount, then write the selected value |
| `0x080291B4` | 312 | Send condition triples from scene and saved-value tests |
| `0x080292EC` | 96 | Retire objects or clear state flag 16, then reset display and audio dependencies |
| `0x0802934C` | 52 | Add an incoming signed-word delta and record its sign in the result byte |
| `0x080293C0` | 80 | Handle command words `0x82` and `0x43`, with two halfword output pointers |
| `0x08029410` | 60 | Prepare a background, text control and palette ranges |
| `0x080297A4` | 180 | Initialize the primary activity's display, selected callback and view |
| `0x08029858` | 220 | Load the selected tile, palette, map and cell resources |
| `0x08029934` | 60 | Update the primary view and effects, then call an optional activity tick |
| `0x080299B0` | 80 | Initialize the secondary activity and restore its palette |
| `0x08029A00` | 40 | Call the selected secondary activity tick |
| `0x08029A28` | 16 | Release the primary object list on the alternate activity path |
| `0x08033940` | 204 | Initialize definition row four's backgrounds, clock, objects and palettes |
| `0x08033A0C` | 232 | Coordinate moving-event creation, completion, score penalties and activity flags |
| `0x08033AF4` | 172 | Reset eight primary item slots and accumulate their byte penalties |
| `0x08033BA0` | 120 | Create the control object at fixed position, initial waiting state and callback |
| `0x08033C18` | 104 | Create the auxiliary selector object at fixed position and callback |
| `0x08033C80` | 224 | Create a selected item with coordinate words, animation and slot-derived flags |
| `0x08033D60` | 360 | Create a selected moving event with paired slot, position, speed and animation |
| `0x08033EC8` | 216 | Update primary x movement, control launch flags and animation completion |
| `0x08033FA0` | 340 | Advance control phases, vertical motion, paired-slot removal and wait timer |
| `0x080340F4` | 196 | Change the selected halfword, animation frame and two auxiliary flag bits |
| `0x080341B8` | 292 | Advance the moving event, fill or update a secondary slot and retire it at a boundary |
| `0x080342DC` | 72 | Test the control byte and eight paired object identifiers |
| `0x08034324` | 52 | Retire nullable secondary objects and clear their slots |
| `0x08034358` | 44 | Load seven item palettes into descending banks |
| `0x08034384` | 104 | Create the primary object at fixed position and callback |

Every comparison includes the complete original extent, internal switch tables,
literal pools and alignment. Every function has an actual changed-source
negative control and a separate strict declaration diagnostic. The bodies use ordinary C without added reads, volatile access views or
fabricated initializers. The primary callback below has one short annotation
on an actual state-root pointer; the auxiliary callback has three annotations
on its actual object, shifted selection and flag-field address. The activity
coordinator has three call-free annotations on the actual item-table pointer
and two object pointers consumed by identifier loads. The other bodies need
no register bindings. Source coverage remains separate from whole-ROM
matching and runtime evidence.

# Observed representations and contracts

The initializer allocates 420 zeroed bytes and stores a scene byte at
offset `0x12`, an option byte at `0x13` and phase zero at `0x14`. The declared
state view covers the observed prefix through flags at `0x15`; its pinned
compiler size/alignment are 24/4. It does not replace the 420-byte allocation or
describe complete storage. The amount at offset 8 is signed, while result,
return mode, scene, option, phase and flags are bytes. The cursor access view
reads one byte at object offset `0x4E`; nullable cursor slots are preserved.

The resource table uses the native 32-byte stride. Its union exposes the same
32-byte prefix as fields, eight words and sixteen halfwords. The requirement
pointer is at `+8`, four cost halfwords start at `+12`, and the label prefix
starts at `+20`. The pointed requirement view observes parameter bytes at 0
and 5 with four threshold bytes after each. The compiler rounds that view to
12 bytes, but this code does not use its size as a serialized record stride.
The observed eight resource pointers are `0x080596BC`, `0x080596C8`,
`0x080596D4`, `0x080596E0`, `0x080596EC`, `0x080596F8`, `0x08059704` and
`0x08059710`. All are four-byte aligned and spaced by 12 bytes. This supports
the declared alignment for those observed records without establishing the
complete resource-table capacity or arbitrary incoming scene values.
Definition records use a 28-byte stride: two callback words at `+0` and `+4`,
an eight-byte clock at `+8`, eight delta bytes at `+16`, sequence byte at `+24`
and flags at `+25`. The callback view describes the specific effect-only,
no-argument calls made here. It does not establish the original declarations
or return types of the unconverted targets, or refine other callback families.

The progress test uses one parameter-root access view at game storage `+0x98`.
Its value bytes at `+0x69D` are the same bytes as the existing contact-world
view at game `+0x735`. This common base captures the native pointer lifetime
across both parameter calls without new traffic or a forced register. The
signed parameter getter results are converted to unsigned words before the
observed unsigned threshold comparisons. The signed amount is compared with
the selected unsigned halfword cost. Only option indices 0 through 3 enter
this test. A valid scene/value index, resource table capacity and surrounding
storage are not established by that guard.

The notice handler takes a complete command word and two halfword pointers,
and returns a word 0 or 1. Command `0x82` combines the result byte shifted by
14 with the amount's low 14 bits, writes output kind 2, then clears the result.
Command `0x43` changes the phase to 6. This is a function-specific contract;
it does not refine unrelated generic indirect callback types. A pinned
compiler assignment diagnostic checks its declared callback type, alongside
field and alignment checks with real wrong-header rejection controls.

# Controller behavior and remaining originals

The controller reads the selected player byte at view-context `+0x31`, uses
the native 12-byte view stride, and reads linked pressed keys at `0x03004228`.
It retains the cursor snapshot across provider calls. Phases 0 and 5 react to
mask 11. Phase 2 updates the countdown and amount text, invokes the selected
activity tick, and pauses for cursor state 5 or game flag 16. State flag 1 or
a definition-enabled clock equality moves to phase 3 and initializes the
request timer to 20. The timer is an unsigned word; decrement to
`0xFFFFFFFF` triggers the progress test. The caller explicitly consumes the
test and clock-equality returns through their observed low bytes.

The activity start initializes one real halfword source to zero through a
scoped pointer, then passes its address to the existing BIOS SWI `0x0B` glue
for the observed VRAM transfer. The source-address lifetime ends after the
initial store; the actual transfer still consumes the initialized object.
That ordinary pointer scope reproduces the native argument setup and avoids
carrying the zero value across later calls. The function then resets display
mode, layers and tile allocation, clears the first linked pressed-key
halfword, invokes the selected activity initializer, and updates the
clock and amount text. The SWI provider is existing assembly glue and receives
zero new C credit. Hardware execution is not established by this match.

Phase 4 tears down the current activity, calls the completion drawer
and starts the first transition. Phase 6 stores result 3 and follows one of
three return paths. Previous request word 1 credits the signed amount, advances
the world clock, sends condition triples and submits kind 1 using the distinct
return argument word at `0x03004334`. Return mode submits kind 10; the fallback
submits kind 5. The condition marker preserves the unconditional final
`(0,4,0)` call in scene 0, even after an earlier triple. Its paired scene sums
use saved bytes 3/7, 4/6 and 5/1 exactly as the original accesses do.

The completion drawer has a complete 264-byte extent ending at the independent
progress-test entry `0x080290F8`. It sets state flag 16 and performs the original
zero-halfword VRAM transfer, background setup and text calls. Its background
control word at `0x0805953C` is distinct from the original initializer's control
word at `0x08059540`. The selected background pointer is read from resource
offset 4; the label halfword is read from offset 20 plus twice `option + 1`.

The drawer carries the resource address as a 32-bit unsigned word and advances
that address to the label prefix after drawing the title. This expresses the
observed address calculation without arithmetic beyond a declared struct
member. Pinned compiler diagnostics establish four-byte pointers and unsigned
words, a 32-byte resource prefix with alignment 4, pointer-field offset 4 and
label offset 20. The fixed resource root `0x0805971C` supplies the corresponding
word and halfword alignment. These are target-specific address and access
views, not a portable pointer-conversion contract or a capacity check. The
code preserves the unchecked scene and option indices and does not establish
that arbitrary inputs stay within the observed resource or label prefix.
No register bindings, added reads or fabricated values were needed; the actual
audio notification 54-to-55 control changes the compiled result.

Need adjustment `0x0802944C` / 100 bytes remains original. Its typed call
declaration is a local, provisional description of observed operands and
carries no new C credit. The input status service is covered by the
IRQ-shared reset and polling section below. The view-mode setter at `0x0800E8B4`
is already source-owned.

The [interpolation setter](../src/transition/transition_set_view_interpolation.c)
at `0x0800EB14` now owns its full 24 bytes: 20 instruction and four literal bytes.
It writes the low byte of the incoming word to the existing 48-byte motion
record's `interpolate` field at `+0x2E`. Its index is an unsigned byte, matching
the native entry's narrowing; the provisional two-word declaration is replaced
by the canonical view-effects declaration. The actual primary activity caller
passes `(0,0)`, the reset writes one, and the view controller tests for one.
The setter, these actual connected definitions, their normal/strict controls
and separate target API/layout witnesses are checked. An integration diagnostic
exposed the existing transition-object header's missing include guard; adding
the guard changes no layout or callable type.

These facts identify a stored value and its consumers. They do not establish a
bound for the unsized motion table, all writers or every incoming index. No
runtime or gameplay observation is added.

# Connected activity dispatch and resource loading

The activity wrappers preserve the scene-byte selection and the native
definition-table stride. Both initializers call the first callback word
without a null guard. The primary tick first updates map view zero, view
motion and transient effects, then tests the second callback word before
calling it. The secondary tick calls that word without a guard. In the
observed eight-record prefix, the first secondary word is null and the other
seven are nonzero; all eight initialization words are nonzero Thumb addresses.
That prefix is evidence for these accesses, not a complete table capacity or
a valid-scene guarantee. The original BX-R0 call veneer remains a low-level
handoff with zero new C or glue credit.

The primary initializer installs the accepted scene VBlank callback and uses
background control `0x08059544` for layer one and `0x08059540` for layer two.
The top-level initializer uses `0x08059540` for layer one instead.
These distinct source operands are retained. After resource setup and the
initialization callback, the wrapper reads the state prefix's first pointer
word for the view provider and passes the existing two-word view dimensions
by value. The eight-byte state access view leaves the second word unnamed;
it does not describe the remaining allocation or establish a nonnull object.

The resource loader takes an incoming word index and uses a 60-byte record
stride rooted at `0x0805985C`. Its union represents the observed fifteen
pointer words as a named prefix and a word array. The two tile streams are
decoded into `0x06000000` and `0x06008000`, followed by the two map source
controls, the 256-color palette and primary/combined map resources for views
zero and one. Cell resources are decoded next. Only the extra type pointer is
tested for null before the extra decode; the final call resets object palette
slots. No other pointer, allocation or index guard is introduced.

A small inline accessor adds the row offset to the address of each real
pointer field and reads that field. Its unsigned address representation is
specific to the measured four-byte target pointers and words. The table base
lifetime begins before the row offset; both remain separate across the real
provider calls. This ordinary C spelling reproduces the full 220-byte extent
without register bindings or repeated reads. Direct entry-pointer spellings
produced a shorter, unmatched body and remain preserved as failed candidates.
The observed record prefix and alignment do not establish arbitrary incoming
index validity or complete resource capacity.

# Connected top-level initialization

The initializer has a 446-byte function symbol and two original zero alignment
bytes before the independent controller entry at `0x08028BD0`. The source's
alignment directive describes that section tail; it supplies no instruction
body or new glue credit. Every byte of the complete 448-byte extent is checked.

An ordinary inline helper stores zero into the actual halfword fill source
before the existing BIOS transfer. Its pointer lifetime ends at that store;
the subsequent transfer consumes the initialized object. This real producer
scope reproduces the native zero-value lifetimes without added reads, volatile
storage, register bindings or an invented later initializer. Earlier direct
scalar initializers produced unmatched code and remain separate raw evidence.

The function uses the resource prefix's background word at offset 0 and label
halfword at offset 20 plus `scene * 32 + option * 2`. Its unsigned-word address
calculation uses the same measured four-byte pointer and 32-byte union basis
as the completion drawer. Scene and option are unchecked bytes, and the code
does not add allocation failure or resource-capacity guards. Layer zero uses
the distinct control word at `0x08059558`; layer one uses `0x08059540`.

Previous request word 10 selects return mode 1 and stores the accepted notice
handler into the input root at `0x030040B0`, offset `0x2C`. The specific access
view covers 44 preceding bytes and that function pointer, with measured size
48 and alignment 4. Its typed handler takes a command word and two halfword
output pointers. This observed prefix does not establish complete input
storage or other indirect callback interfaces. Other previous request values
store return mode zero. The changed allocation-size control, callback-type
assignments and wrong-layout diagnostics are checked against current headers.

The source preserves unchecked player, scene and table accesses, nullable
cursor handling, callback output writes and the original teardown behavior.
It adds no capacity guards or allocation failure handling. These are static
and compiler-matching findings; this batch does not establish complete scene
formats, hardware execution, save compatibility or gameplay correctness.

# Connected definition-row-four lifecycle

Definition row four at `0x0805955C + 4 * 28` contains initialization word
`0x08033941` and step word `0x08033A0D`. The accepted activity wrappers reach
these words through their existing table dispatch. This is a definition-row
identity within the kind-20 path, not another flat scene-table kind.

The row-specific state access view covers 100 bytes with alignment 4 inside
the existing 420-byte allocation. It observes the first object at 0, a signed
score halfword at 12, eight primary pointers at 24, eight secondary pointers
at 56, a control pointer at 88 and eight selected bytes at 92. These arrays
express the actual eight-slot loops. They do not establish all allocation
contents or arbitrary object-pointer validity. The main 24-byte state view
and its declared global pointer retain their existing types.

Configuration records at `0x08069E54` have a measured 12-byte stride and
alignment 4: the clock occupies the first eight bytes, count is at 8,
interval at 9 and a byte used by the original step is at 10. Five consecutive
record prefixes are observed; the declaration remains unsized. Item records
at `0x08069E90` have a measured 24-byte stride and alignment 4, with a palette
pointer at 16 and penalty byte at 20. Seven consecutive prefixes are observed
and used by the palette loop. This establishes those local accesses without
proving complete tables or valid arbitrary indices.

Initialization preserves the three background controls and map operands
390, 1 and 780. The configuration address is first formed at the actual
clock-copy call, after the background calls. It is read again after item
reset for the interval word, then objects and palettes are created in their
original order. An earlier configuration-pointer capture changed the
compiler's live values and did not match; it remains separate evidence.

Reset assigns the real coordinate pair `(212, 86)` before entering the loop.
The existing ordinary `FramePoint` is measured as two word members, size 8
and alignment 4. Its by-value call view occupies the original creator's
R0/R1 coordinates, while the selected value and slot remain complete words
in R2/R3. The creator captures those four incoming words before
allocation; its later low-halfword and low-byte stores do not justify
narrowing the call formals. This grouping describes this observed call,
not a recovered original declaration or a generic callback ABI.

The random result is stored as a byte in the selected array and forwarded as
a complete word to the item creator. After each removal or creation,
the code reloads the actual global state pointer for the slot update. It adds
the item record's penalty byte, indexed by the created object's halfword at
offset `0x0A`, to the signed score and stores the halfword result. No null
guard, capacity check or portable arbitrary narrowing guarantee is added.
Assigning the coordinate members separately gives the matching register
lifetimes with no bindings. Aggregate initializer variants emitted an extra
allocated constant section and were rejected; no section was discarded.

The completion test returns a full word 0 or 1. It requires control byte
`0x4E` to equal 1 and all eight secondary slots to be nonnull with identifiers
equal to their primary partners. Control and primary pointers remain
unchecked. Secondary cleanup preserves nullable-slot removal and the
post-call global reload before storing null. Palette loading uses seven
records, banks 15 through 9 and 16 colors per call. The completion symbol
occupies 70 bytes followed by two original zero alignment bytes before the
independent cleanup entry; the complete 72-byte extent is compared.

The 232-byte activity coordinator at `0x08033A0C` and its three connected
creators and primary, control and auxiliary callbacks are recovered below.
Their local declarations describe only the calls made by this batch. The
five new bodies use ordinary unbound C and have complete native, actual
changed-source and strict declaration comparisons. Compiler layout and
compatible-type diagnostics reject altered pointer counts, score width,
record offsets, stride and slot width. These findings do not establish
hardware execution or a complete activity format.

# Connected item creation and amount update

The item creator retains the complete coordinate words in R0/R1 and selection
and slot words in R2/R3 before allocation. It stores only the low slot byte
and selected halfword, but uses the full unsigned slot for animation and flag
classification. The existing eight-byte, alignment-four `FramePoint` supplies
the grouped coordinate call view. Its signed members are converted to
unsigned words before the defined 16-bit shifts; the target then interprets
those resulting words as coordinates. No input narrowing or bounds guard is
invented.

The flag access view is rooted at the complete object pointer, covers 216
bytes and has measured alignment 4. The actual allocator reserves 320 bytes;
the existing `FrameObject` view is 312 bytes. Compiler-generated initialized
object representations independently check the bits at `0xD1`, `0xD3` and
`0xD5`. This is a local access representation, not a complete original object
format. Palette 3, layer 1, two cleared display flags and the two slot-derived
render flags preserve the original byte operations.

The actual initial flag-view pointer ends before the position and animation
calls. Later render operations use direct access casts, so no separate flag
pointer is carried across calls. A scoped unsigned direction range starts at
3, is ANDed with the retained direction and then decremented. That real value
is consumed destructively by the native AND/subtract pair. These ordinary
scopes close the earlier saved-pointer and scratch-register mismatches without
bindings, volatile access or extra memory traffic. The full 224-byte extent
contains a 222-byte symbol and two original zero alignment bytes before the
independent event creator at `0x08033D60`.

The amount helper at `0x0802934C` ends after 52 bytes, before the already
accepted 32-byte nibble reader at `0x08029380`; the following nibble writer is
also an independent accepted 32-byte function. These neighboring functions
are not part of the helper's new coverage. It consumes the complete signed
word, adds its unsigned representation to the existing halfword bit pattern,
sets flag 8 and stores result 1 for a positive input or 2 for a negative
input. Zero leaves the previous result byte unchanged. The word sign test
also applies when the low halfword is zero, so an earlier private short-formal
inference is corrected. Target halfword storage is preserved without a claim
that arbitrary signed narrowing is portable.

Fifteen finite initialized-memory fixtures cover zero, positive and negative
word inputs, halfword wrap patterns and sign decisions beyond the halfword
range. Twelve distinguish the actual changed-source mask control. Their
Thumb memory model checks the original, matching bytes and bit-pattern model;
unmapped input, truncated pools, unsupported instructions and exhausted
budgets are rejected. These are bounded interpreter findings, with no
hardware-fault, pointer-validity or gameplay claim. The original step remains
unmatched and explicit.

# Connected moving-event creation

The event creator at `0x08033D60` owns the complete 360-byte extent through
`0x08033EC8`, including its seven-entry internal switch table and literal
pools. It allocates the existing object, writes identifier 4, and compares a
signed random result from 1 through 100 against the selected configuration's
chance byte. The below-threshold path stores selected halfword zero; the
other path requests a value from 1 through the row's count byte.

Selected identifiers 0 through 6 choose one of four adjacent slot pairs:
0/1, 2/3, 4/5 or 6/7. The switch has no default write. Other identifiers
retain the existing byte at object offset `0x4C`; no initializer, validity
check or replacement slot is added. The five observed configuration records
have counts 2 through 6, but this does not establish complete configuration
storage, arbitrary option bounds or behavior of an altered provider.

Position records at `0x08069F38` have size 12 and alignment 4, with signed
word x, y and speed at offsets 0, 4 and 8. Eight consecutive prefixes are
observed. The declaration remains unsized. The whole-object access prefix
has size 80 and alignment 4: the speed word is at 20 and slot byte at 76.
This keeps the speed store within a declared word member while retaining
the older object view's fields and offsets. The actual allocator reserves
320 bytes; this prefix does not describe the complete object.

The separate 216-byte, alignment-four flag view preserves the event's
halfword identifier load before palette subtraction. Its palette field uses
an unsigned-halfword underlying type, with the same checked four physical
bits at `0xD5`. The item creator's earlier byte-backed view remains unchanged.
A byte-backed event predecessor matched all other instructions but differed
at that load; the final ordinary C has no register bindings, volatile access
or extra memory traffic. Independent compiler-produced object representations
check the flag mapping and reject changed widths, offsets and callback types.

The slot selects position and speed, and its low bit selects direction byte
2 or 6. The existing velocity table and fixed-product provider then supply
the two velocity words. Coordinate shifts use unsigned words before target
signed interpretation. The animation call receives the existing 16-byte
resource prefix of the selected 24-byte item record; its accepted provider
reads that record. The installed single-object tick is the connected update
at `0x080341B8`.

Fifty finite initialized-memory cases use the five observed configuration
rows and in-range abstract provider results. Two additional cases inject an
out-of-contract random result solely to check the preserved default slot;
they do not claim that this occurs with the observed configuration. All 52
compare original bytes, freshly linked C and a bounded model, with actual
changed-source divergences and caller-saved register poisoning. Position,
allocation, random, fixed-product and animation hooks are explicit model
limits; the animation hook is observational here. Missing memory, truncated
pools, unsupported instructions and exhausted budgets are interpreter
rejections, not claims about GBA hardware faults or gameplay behavior.

# Connected moving-event update

The installed callback owns `0x080341B8` through `0x080342DC`, a complete
292-byte extent ending before the independent paired-slot completion test.
Its standard single-`FrameObject` callback type agrees with the accepted
object dispatcher and the creator's stored pointer. It first adds each
velocity word to the position word and stores the two next-position words.
The arithmetic uses unsigned word representations before the target's signed
interpretation, preserving modular additions without a portable arbitrary
signed-conversion claim.

The actual lower and upper coordinate pairs use ordinary eight-byte,
alignment-four `FramePoint` locals. They preserve the original register and
stack lifetimes for the control-centered bounds: x plus or minus `0xC0000`
and y plus or minus `0xA0000`. The bounds are computed before the control
identifier test. Capture requires control identifier zero and strict
inequalities in both dimensions; no bound or pointer-validity check is added.
An aggregate coordinate initializer emitted an extra allocated constant
section and was rejected. The final source uses explicit real member stores,
ordinary point values and no register bindings or extra memory traffic.

The callback's row-state view preserves the same 100-byte, alignment-four
prefix, now exposing the observed unsigned current-slot halfword at 14.
Score remains signed at 12, the eight nullable secondary pointers at 56 and
the unchecked control pointer at 88. The current-slot value is unchecked.
This access view does not alter the established state/global declaration or
describe the complete 420-byte allocation.

On capture, the callback sets removal mask 2. A null secondary slot creates
an item at coordinate words `(212, 30)`, forwarding the selected halfword and
current slot as complete call words. The created pointer is captured before
reloading the actual global state and storing it. A nonnull slot receives
the selected low byte through the established animation-frame API, followed
by a fresh global reload and halfword identifier store. Both paths reload
the control pointer and mark its identifier 1.

Selected identifier zero decrements the score halfword, sets it to 1 if the
stored signed result is nonpositive, and requests cue 189. Other identifiers
request cue 188. These operations preserve target halfword narrowing and
the original post-call global reloads. Outside capture, direction byte 2
retires an event above `0xB7FFFF`; direction 6 retires it at or below zero.
Other paths copy the actual next-position members into position. The activity
coordinator below connects this callback to the creation and scoring path.

Forty-one finite callback cases compare original and freshly linked bytes
with a bounded model; 27 distinguish the actual removal-mask control. They
cover capture edges, both secondary-slot paths, score halfword narrowing,
current slots 0 and 7, and wrapped next-position and bound coordinates. Four
abstract hook cases change the global pointer to check the observed reloads;
this does not claim that the accepted callees cause such a change at runtime.
Two selected-256 cases check operand and store widths while leaving the
unbounded item lookup inside the abstract hook unexecuted. Item creation,
animation-frame selection and audio cues are explicit hook limits. The four
rejected input/interpreter controls remain model findings, with no hardware
fault, general asset capacity or gameplay guarantee.

# Connected primary, control and auxiliary objects

The three constructors own complete extents at `0x08033BA0` (120 bytes),
`0x08033C18` (104 bytes) and `0x08034384` (104 bytes). They allocate through
the established 320-byte provider, set their actual halfword identifiers and
flag fields, set fixed coordinate words, select animation records and install
specific single-object callbacks. The control starts at `(88,140)` with
identifier 1, palette 1 and flags `0x100001`. The auxiliary starts at
`(212,30)` with identifier 2, palette 2 and flags 1. The primary starts at
`(88,152)` with identifier 0, palette 0 and flags 1. Position shifts use small
positive constants; no allocation guard, extra initializer or arbitrary input
validation is added. The accepted row-four initializer changes only the three
callee names at their existing addresses.

The installed control callback owns `0x08033FA0..0x080340F4`, 340 bytes with
its literal pools. It uses the standard one-`FrameObject` callback interface.
The separate whole-object access view has size 92 and alignment 4, exposing
the state byte at `0x4E` and timer word at `0x58` while preserving the
320-byte allocation. The animation-resource prefix is the existing 16-byte,
alignment-four provider view. The four observed animation record roots are
word-aligned; their content and pointers are pinned privately, without a claim
about complete resource or table capacity.

State 1 is the observed waiting phase: the constructor and two callback paths
write it, and this callback performs no operation for it. Keeping that real
phase as an explicit no-op switch case lets the historical compiler reproduce
the original decision tree. Without it, the same complete body and pools differ
only in the first nine dispatch bytes. No synthetic state, guard, register
binding or native operation is introduced.

In state 2, animation flag `0x400000` starts timer 10, moves to state 7,
clears the observed flags and copies the primary object's x coordinate. In
state 3, next y advances by velocity y, then velocity y advances by acceleration
y. Positive resulting velocity writes identifier 1. Above `0x8BFFFF`, the
callback stops both vertical words, fixes position y to `0x8C0000`, clears the
identifier, and compares x with the primary-centered inclusive interval of
plus or minus `0xE0000`. Outside it, cue 187 precedes removal of each nullable
secondary slot and a post-call global reload before clearing that slot. The
control changes to state 2, selects the failed animation and sets scene flag 2.
Inside it, cue 186 changes the control to state 1, clears flag 16 and selects
frame zero. Before the vertical boundary, it copies actual next y to position y.

In state 7, decrementing the timer to `0xFFFFFFFF` changes the control to
state 1, sets flag 1, selects the waiting animation and clears scene flag 2.
Vertical additions, x bounds and timer subtraction use explicit unsigned-word
representations before the target's signed interpretation. The source adds no
signed-overflow dependency or new guard; these casts describe the pinned 32-bit
target model, without a portable arbitrary conversion claim. The primary and
auxiliary callbacks and the activity coordinator are recovered below. The
need-adjustment provider remains an explicit original body.

Fresh complete native comparisons include actual source controls, strict
provider declarations, current importer proofs and independent layout/type
rejection cases. Nine constructor cases and 51 control-callback cases compare
original bytes, freshly linked C and a bounded model; ten distinguish the
actual source controls. One removal hook redirects the global state pointer
solely to check the original post-call reload, without claiming that the
accepted removal provider does so at runtime. Finite fixtures use explicit allocator,
position, animation, audio and removal hooks with caller-saved clobbering.
They test bounded traces and storage effects, not those provider bodies or
gameplay. Null, missing-storage and interpreter failure cases retain their
model-only meaning. Slot capacities, pointer validity and surrounding storage
remain unchecked.

# Connected primary movement and control launch

The primary constructor now installs the matching callback at
`0x08033EC8..0x08033FA0`, a complete 216-byte extent including its pools and
original alignment. The existing constructor changes only the stored callback
name at the same address. Its standard one-`FrameObject` declaration agrees
with the installed callback and the established object dispatcher.

Scene flag 2 suppresses the input and control-launch block. Otherwise current
input halfword zero at `0x03004220` gives mask 16 priority over mask 32. The
callback adds or subtracts `0x30000` from x using word-wrap arithmetic, stores
next x, and conditionally copies it to position x. Right movement copies at
or below `0xA9FFFF`; left movement copies above `0xE0000`. These tests retain
an already-outside or wrapped coordinate's native behavior, without an added
clamp or validity guard.

Control state byte `0x4E` equal to 1 allows copying the primary x coordinate
to control x. Pressed input halfword zero at `0x03004228`, mask 1, then
requests cue 185, sets flag 16 on both objects, writes control state 3,
sets vertical velocity to `-0xC0000` and acceleration to `0x8000`. The final
primary-object animation-flag test runs independently of that scene flag.
Flag `0x400000` clears itself together with flag 16 and selects frame zero.
The code adds no null-control or coordinate guard.

The post-cue access view is a 92-byte, alignment-four state prefix. Its named
union at byte 88 exposes the same four bytes as a `FrameObject` pointer and
an unsigned address word; the existing 100-byte pointer-array view stays
unchanged. Pinned compiler layout and representation checks establish word
and pointer widths, matching field offsets and the target's byte order. The
source uses the address representation for the actual pointer loads and casts
back to the declared object view. This is a bounded model of the observed
32-bit target storage, without an arbitrary portable pointer-conversion claim.
The prefix remains inside the observed 420-byte state allocation.

Actual control and flag-value snapshots retain each original load and store.
The first post-cue state root is captured before the control flag read; after
the state-byte store, the actual global root is reloaded before the velocity
and acceleration pointer loads. One short R2 annotation applies to that real
state pointer within the call-free block. The generated native values and uses
are audited separately: both captures follow the audio call, their last use
precedes the final animation call, and they cross no ABI clobber boundary.
An otherwise identical unannotated predecessor differs in nine bytes. A
second control-pointer annotation was removed without changing bytes.

Complete current constructor/importer/provider proofs include real changed-source
controls and strict declaration checks. Separate layout, compatible-type and
pointer-representation diagnostics distinguish the chosen access model from
byte equality. Ninety-three bounded initialized-memory cases compare original
bytes, freshly linked C and an independent bit-pattern model; twelve distinguish
the actual cue-identifier control. Three interpreter failure checks reject an
unsupported instruction, a truncated supplied extent and an exhausted budget.
Two injected audio-hook effects check post-call root and flag reloads. One
initialized aliased-storage case checks the control-address reload after its
flag store; this is input-model evidence, not an asserted gameplay arrangement.
Audio and animation hooks poison caller-saved registers and check call operands
without executing those provider bodies. Pointer validity, complete storage,
arbitrary surrounding capacity and gameplay remain unproved. The auxiliary
callback and the activity coordinator are recovered below.

# Connected auxiliary selection callback

The auxiliary constructor installs the matching one-object callback at
`0x080340F4..0x080341B8`. Its 194-byte function and original two zero alignment
bytes form the complete 196-byte extent, including both literal pools. The
constructor changes only the callback identifier at the same address and keeps
the standard `void(FrameObject *)` call type.

Scene flag 2 suppresses the callback's writes. Otherwise pressed input
halfword zero at `0x03004228` gives mask `0x280` priority over mask `0x140`.
The first mask changes selected halfword zero to 7 and decrements every other
value. The second changes values above 6 to zero and increments values zero
through six. No input narrows the selected halfword to a byte or adds a row
validity guard. If the resulting value differs, it is stored in the state halfword at offset 14.
Low two bits zero or three select animation frame zero; other values select
frame one.

After that animation call, the actual global state and selected halfword are
reloaded. Selected values above three set object byte `0xD3` bit 4; other values
clear it. The unsigned expression `((selected >> 1) & 3) - 1` at or below one
sets bit 5, otherwise clears it. Zero before subtraction deliberately wraps to
`0xFFFFFFFF`. These are two separate byte stores preserving the other six bits,
including the original reload between stores. No null or capacity guard is added.

The whole-object access prefix is 212 bytes with alignment four, inside the
observed 320-byte allocation. Its nested `0xD3` flag field is a packed one-byte,
alignment-one view. Pinned compiler layout and initialized data checks establish
the field offset and physical bit mapping. A signed one-bit field receives
minus one or zero for bit 4; an unsigned one-bit field receives one or zero for
bit 5. This expresses the observed representation without claiming a complete
object layout or original source declaration.

Three annotations remain after actual removal trials. The callback object in
R4 survives the animation call as a real callee-saved pointer. The post-call
shifted value in R3 and the nested field address in R2 are distinct call-free
lifetimes; both are assigned after the animation call. The field address is
captured after the first flag store and used through the second. Native reads,
writes and call boundaries are checked independently of lexical source scopes.
Removing the object, shifted-value or field-address annotation changes 78,
three or four bytes respectively, with no added traffic or fabricated value.

Fresh constructor, complete current header-importer and animation-provider
proofs include actual changed-source controls and strict declaration checks.
Separate layout, compatible-type and physical mapping failures reject incorrect
field widths, offsets, alignment and callback declarations. Bounded initialized
instruction fixtures and an independent bit-pattern model compare full incoming
halfwords, ordered input masks, animation operands and both flag stores. All 146
cases agree; four distinguish the real wrap-value source control. Three separate
interpreter failures reject an unsupported instruction, a truncated pool and an
exhausted budget. The animation hook poisons caller-saved registers and preserves
the checked stack and callee-saved protocol; its effects are abstracted rather
than executed. Three injected post-call effects test the observed reloads
without asserting that the actual provider produces them. Pointer validity,
arbitrary storage, gameplay and hardware behavior remain unproved; the
need-adjustment provider stays original.

# Definition-row-four activity coordinator

The observed 28-byte definition row at ROM `0x080595CC` contains initializer
`0x08033941` and coordinator `0x08033A0D`. This is definition row four within
the kind-20 activity path; it uses the existing `void(void)` callback contract.
The complete 232-byte coordinator includes its internal literal pool and ends
at the independent reset-items entry `0x08033AF4`.

The request timer uses unsigned-word subtraction and its `0xFFFFFFFF` sentinel.
Creating a moving event precedes the actual global-state reload and selected
row interval read. Completion consumes the low byte of the full-word provider
result, requests cue 27, reports the signed score and clears/reset objects.
The low byte of the clock comparison then gates eight paired-slot comparisons.
Each unmatched or missing secondary subtracts the primary identifier's byte
penalty from the score halfword; each store preserves the target's low-halfword
conversion. A nonpositive final signed score becomes 1 before the score call
and the post-call global reload that sets scene flag 2.

The index begins at zero before an ordinary pointer to the actual global
state slot is captured. Three annotations retain the real item-table pointer
in R5 and the two loaded object pointers in R3 and R1. The table is used only
in the call-free loop; the object pointers die at their identifier reads. No
caller-saved annotated value crosses a call. Removing each annotation changes
the native comparison; a hard R6 global-slot annotation is unnecessary and
its differing predecessor remains private. These lifetimes add no reads,
guards, volatile operations or placeholder initialization.

Primary object pointers and identifier-indexed ROM entries remain unchecked.
Eight pointer slots are an observed access boundary, not a capacity or null
safety claim for arbitrary state. Compiler matches and bounded initialized
fixtures do not establish gameplay or hardware execution.

Fresh canonical coordinator, direct-provider and indirect-dispatch comparisons
include actual cue-identifier source controls and a separate strict declaration
profile. The existing `void(void)` callback, global-slot pointer type, halfword
score/identifier accesses and record strides have compiler-pinned layout/type
checks; meaningful signedness, count, width, alignment and callback controls
reject. Removing the event declaration leaves legacy bytes identical but the
strict compiler rejects the actual undeclared call.

All 118 finite initialized-memory cases agree for the original, linked and
independent model; 50 distinguish cue 27 from the actual control cue 26. Cases
cover unsigned timer sentinels, nullable secondary slots, equal/unequal IDs,
signed score endpoints and target halfword conversion. Four injected root
redirections test the original post-call reloads, and high-word provider results
are synthetic ABI cases for observed low-byte consumption rather than claimed
outputs of accepted providers. External event, completion, cue, score, cleanup,
reset and comparison effects are abstract hooks with caller-saved poisoning and
callee-save/stack checks; these fixtures do not execute those provider bodies.
Four interpreter failure cases reject an unsupported instruction, truncated
pool, exhausted budget and uninitialized access through a null primary pointer.
These are bounded model failures, without a hardware-fault or source-guard claim.

# IRQ-shared input reset and polling

The connected 112-byte reset at `0x0801C6E8`, 64-byte counter preparation at
`0x0801C948` and 52-byte status poll at `0x0801C8A4` reproduce complete original
extents, pools and alignment. The accepted kind-20 scene step calls the poll
under its existing return-mode condition. This is three functions and 228 bytes
of C. The installer and installed IRQ follow-on appears below; its receive
and transmit parser children remain explicit original providers.

The existing input root `0x030040B0` retains its 48-byte declaration and notice
handler at offset 44. Its first 44 bytes now have a union of the original byte
prefix and an observed 44-byte field view, expanded from the initial reset
cohort's 12-byte view. Status is byte zero, mode is byte
one, the counter is byte four and pending is byte five. Bytes two, three and
eight are additional reset fields; other byte roles and the complete protocol
remain unknown. Pinned compiler diagnostics establish size, alignment, handler
offset and initialized physical byte mapping independently of matching callers.
The union expresses one storage object without adding a second global alias.

The volatility has a concrete writer basis. Initializer `0x0801C808`
clears 48 bytes, stores the notice handler at offset `0x2C`, invokes the reset,
installs handler `0x0801C47D` using the accepted IRQ-table setter with index zero,
and enables interrupt bit `0x80`. The accepted dispatcher routes timer-three
and serial mask `0xC0` through slot zero. The installed handler and its receive
child write the same status, mode, counter and pending bytes. That child is
recovered in the connected word-flow section below. Volatile full-byte bitfields preserve
the raw byte reads before whole-byte stores; they are compiler-specific access
views rather than a claim about the original headers.

Reset captures IME at `0x04000208`, disables it, conditionally writes `0x8000`
to `0x04000134` when byte eight is zero, then writes `0xC000` to that register.
It clears halfword `0x04000158`, performs the original observable word read at
`0x04000150` with no scalar result use, clears word `0x04000154`, writes
halfword `0x47` at `0x04000140` and halfword `0x80` at `0x04000202`, clears the
five observed state bytes, and restores captured IME. Numeric register accesses
and their ordering are established; protocol effects are not inferred from a
memory-only fixture.

Preparation first reads the unsigned counter. At or below ten it disables IME,
increments the byte counter with the original additional reads, writes IME one
unconditionally and returns word zero. Higher counters set pending one and
mode three, execute the actual reset and return word one. Poll executes
preparation before capturing IME, then disables IME, snapshots status, changes
status four or five to one, restores its captured IME and returns the original
zero-extended status word. In particular, preparation's low-counter path does
not preserve incoming IME; the poll's later snapshot does not undo that behavior.
No interrupt-state guard or normalization is added.

Fresh normal and strict comparisons include actual changed-source controls,
complete current header importers and direct IRQ/heap providers. Incorrect
prefix extent, handler offset, storage alignment, byte mapping, field width and
function declarations have independent diagnostic controls. No register
annotations or additional traffic are used. All 426 finite initialized-memory
cases compare the original and linked three-body call chains with an independent
read/write model; 84 distinguish the actual source controls. These execute the
real reset and preparation calls with checked stack and callee-saved registers,
without abstract provider hooks. Three interpreter failures reject unsupported
instructions, missing pool bytes and an exhausted budget. MMIO is represented
as initialized memory: hardware side effects, asynchronous IRQ interleaving,
serial protocol, arbitrary inputs and gameplay remain unproved.

# Installed IRQ and input-storage construction

The connected installer at `0x0801C808` / 156 bytes, installed IRQ callback at
`0x0801C47C` / 120 bytes and its direct notice helper at `0x0801C988` / 48 bytes
add three complete ordinary C bodies totaling 324 bytes. Their literal pools,
internal alignment and independent following entries are retained. No register
annotations, added guards, placeholder values or extra accesses are needed.
The receive/transmit children are recovered in the next section; upstream
scene initializer `0x0801C9B8` is covered by the later connected session group. This does not complete the
input protocol or scene family.

The fields view now spans the full observed 44-byte prefix within the existing
44-byte union. The setup remains 48 bytes with alignment four and its same
specific notice callback at offset 44. Word fields at offsets 12 and 20 receive
fixed-ROM words from `0x080000AC` and `0x08053094`; their interpretation remains
unknown. The installed IRQ clears a word at offset 16 on its error path.
Incoming complete-word parameters are stored as halfwords at 24 and 26;
allocated pointers occupy 36 and 40. The earlier opaque bytes 28 through 35
are refined into the observed halfword access view described below.
Compiler diagnostics check each observed width, offset, alignment and actual
function-pointer assignment, without treating matching caller bytes as a layout
proof. The specific notice type preserves the previously accepted unsigned-word
command/result and two halfword-pointer contract; this is not a generic claim
about every original callback interface.

The installer captures and disables IME before clearing all 48 bytes. It stores
the two parameter low halfwords, makes two separate 514-byte heap allocations,
stores both returned pointers without null checks, and then stores the notice
handler. It sets byte eight to one before executing the accepted reset, so the
reset skips its optional `0x8000` write and later clears that byte. Registration
passes word index zero and the installed Thumb handler address to the accepted
IRQ-table setter. The installer enables bit `0x80` at `0x04000200`, snapshots
both fixed-ROM words and restores its original IME. These are target-specific
word/pointer transfers; allocation validity and arbitrary callback safety are
not established. Its one mapped incoming original call supplies callback word
`0x0801CED5` and word values 68 and 132, without implying a complete caller list.

The IRQ snapshots the halfword at `0x04000140`. Mask `2` requests a word read
from `0x04000150` followed by the receive child; a zero result low byte
skips the mask-`4` child and takes the error path. Otherwise mask `4` invokes
the transmit child, again testing only its result low byte. Error
clears halfword `0x04000158`, stores status six, clears bytes two and three and
clears the word at offset 16. Mask `1` invokes the actual notice helper even
following an error. The original flags are finally written to `0x04000140`
and the byte counter is cleared. No attempt is made to infer register side
effects or a protocol specification from this ordered instruction sequence.

The notice helper preserves the original discarded volatile word read at
`0x04000150`, writes the captured word from offset 12 to `0x04000154`, writes
halfword `0x20` at `0x04000158`, clears status and byte two, and stores one to
byte three. Volatile full-byte bitfields preserve each original read before its
whole-byte store. The receive/transmit results use word
models with observed byte consumption; original declarations are not claimed.

Fresh source controls change allocation size 514 to 513, error status six to
seven and notice value `0x20` to `0x21`. Independent layout and actual-definition
API controls reject wrong prefix extent, callback offset, alignment, scalar and
pointer widths and incompatible formals. Finite initialized-memory cases execute
these bodies and the accepted reset, heap clear and IRQ setter, including the
real notice call. Only heap allocation and the original receive/transmit children
are hooks; they poison caller-saved registers. Synthetic high result words test
observed byte consumption without claiming those original children produce them.
Allocation-null fixtures establish the unchecked pointer stores only. Ordered
memory events, stack and callee-saved registers are compared; MMIO is a numeric
memory model. Hardware side effects, asynchronous IRQ interleaving, protocol,
arbitrary capacity and gameplay remain unproved.

# Connected receive/transmit word flow

Four complete ordinary C bodies add 672 bytes: receive word
`0x0801C4F4` / 376, transmit step `0x0801C66C` / 124, store received word
`0x0801C758` / 88 and emit buffered word `0x0801C7B0` / 84. Every literal pool
and original alignment byte is included. The final emitter boundary is
`0x0801C804`, before a separate original return-only leaf; that leaf receives
no credit. The receive and transmit bodies preserve their two zero tail bytes
with alignment directives. No register annotations, added reads, guards or
initialization are used.

The same 48-byte, alignment-four setup still holds its callback at offset 44.
Offsets 28, 30, 32 and 34 are observed halfword receive/transmit remaining
counts and receive/transmit indices. Raw receive, store and emit instructions
read these halfwords before their whole-halfword writes, including the
otherwise discarded reads. Volatile full-width halfword bitfields reproduce
those concrete IRQ-shared transactions and reloads after calls. These are
compiler-specific access views, not recovered original declarations. A pinned
physical-byte diagnostic checks all four halfword positions independently of
caller equality; narrowing a field to eight bits loses its high byte even
though the containing record can retain the same size. Other controls check
alignment, pointer widths, callback position and actual function definitions.
The existing 44-byte union and byte view remain unchanged.

Receive preserves the incoming word while deriving a separate word-sized
low-byte command. Its three callback-length halfwords are distinct actual
locals at stack offsets zero, two and four; they represent separate receiving,
sending and completion phases. The first and completion lengths are initialized
from their actual values. The sending length is produced by the callback and
then rounded up to a halfword count. Handshake and command-range branches,
status/mode stores and the original callback return being ignored are retained.
No length, pointer or buffer-capacity check is added.

That output requirement is explicit: the sending callback must write the
length halfword before returning for the subsequent C read to be defined.
The parser does not enforce it. The original installed handler `0x0801CED4`
dispatches commands `0x40` through `0x83`; its `0x80`, `0x81`, `0x82` and `0x83`
children write lengths four, 108, two and a calculated string span respectively.
Command `0x84` can pass the configured second-parameter value 132, but that
handler returns zero without writing the length. The accepted contact-menu
initializer can replace it with `scene_contact_handle_input_notice` at
`0x080293C0`, which writes length two for command `0x82` only. These concrete
facts establish neither a complete protocol nor safety for unsupported
commands or uncooperative callbacks. No invented length initializer or guard
is introduced to cover them.

Store extracts a halfword from word bits 8 through 23 and compares the original
fold helper's low byte with bits 24 through 31. On success it writes through
the first allocated buffer, decrements the halfword remaining count and
increments the halfword index; count and index stores retain their observed
16-bit wrap. Emit reads the second allocated buffer, updates its remaining
count and index, and writes the original folded-byte/halfword/tag composition
to word register `0x04000154`. Transmit preserves its state and command guards,
calls the actual emitter and clears its command byte when remaining becomes
zero. Both receive and transmit return observed word zero or one; the IRQ still
consumes only the result low byte. Its two call identifiers change at the same
addresses without changing control flow or register traffic.

The receive/transmit cohort excluded the fold helper at `0x080133D4` and
specific notice dispatcher. The connected section below adds their complete
C bodies; the upstream initializer remains unconverted. Static instructions
show incoming low-16 consumption and a byte-valued word result; names and
declaration models remain provisional. Allocated buffers are 514 bytes, but
neither allocation validity nor arbitrary count/index bounds are established
by these sources.

That cohort's canonical comparisons included its 38 serial/menu importers and
three direct heap/IRQ providers, with actual changed-source controls, strict
new-body diagnostics and genuine missing-provider rejection cases. Its finite
initialized-memory comparisons executed all four bodies and the original fold
helper. The only abstract provider was the specific notice callback with
explicit length/state writes and caller-saved poisoning. Cooperating-callback
ABI fixtures compare ordered memory events, buffer results, stack restoration
and callee-saved registers. Two omitted-length cases are separate seeded-stack
native diagnostics, not evidence of a defined source read or valid protocol.
Interpreter null/index failures mean uninitialized-memory rejection within that
finite model; they are neither hardware-fault claims nor source guards. Numeric
MMIO, asynchronous IRQ interleaving, general capacity, protocol and gameplay
remain unproved.


# Connected serial fold and specific notices

The complete fold at `0x080133D4` is 112 bytes, and the original installed
specific notice dispatcher at `0x0801CED4` is 372 bytes including its full
68-entry switch table and pools. Two direct replies are complete at
`0x0801D0C8` and `0x0801D158`, each 16 bytes. Their names and access types are
provisional. This adds four functions and 516 bytes; the three accepted
receive/store/emit callers change only their same-address fold identifier.

The fold consumes a halfword, processes the low byte followed by the high
byte from each byte's high bit downward, then appends eight zero bits. It
returns a word containing only the resulting low byte. One real remaining
counter uses R3: two, one and zero for the input-byte passes, then one through
eight for the final pass. Its complete native lifetime is call-free and ends
before the return, with no added memory traffic. The ordinary predecessor
has twelve register differences; removing this one annotation has the same
twelve differences in normal and strict compilation. No other new source
uses an annotation. The fold and dispatcher retain only their original
two-byte zero alignment outside their function symbols.

The dispatcher receives the original full-word command and the same specific
word-result/two-halfword-pointer callback contract as the existing handler.
Cases `0x40` and `0x43` return one without changing either output. Case `0x80`
writes the game word at `0x03003950` to the output and produces length four.
Case `0x82` produces length two, reads the full word at `0x03001B70 + 16`, and
stores its low halfword. The word-output union is four bytes/alignment four;
the read-only state prefix is 20 bytes/alignment four with the word at 16.
These overlapping access views do not establish original declarations,
complete global storage sizes or new storage ownership.

The game-word output requires a live writable buffer that satisfies its word
alignment. The actual installer obtains separate 514-byte buffers through
the accepted heap allocator's aligned HeapBlock access contract. Allocation
success, arbitrary incoming halfword-pointer alignment and unchecked buffer
indices remain preconditions, with no new guard or initialization. Cases
`0x41`, `0x42`, `0x81` and `0x83` originally remained explicit child calls in
this fold/dispatcher group; the later connected session group covers them
with their complete discarded-result interfaces and separate C credit.
The final string child ends at `0x0801D1CC`, before an independent four-byte
return-only leaf, which is also excluded.

Default command `0x84` returns zero without writing either output even when
the parser's second parameter admits it. The parser's sending callback must
write its length before the subsequent source read; the parser ignores its
return and adds no guard. Omitted-length cases are separated seeded-stack
native diagnostics, without a defined-source or valid-protocol claim.

Exhaustive halfword fixtures compare all 65,536 inputs with the original,
linked C and an independent eight-bit polynomial model; a genuine polynomial
edit changes 58,975 results. Separate notice fixtures execute the dispatcher
and the two real replies, with explicit hooks for the four original children.
Connected fixtures execute the actual receive body, BX R3 transfer, notice
dispatcher, replies and fold with no child hooks. Valid `0x80`/`0x82` paths
produce their lengths before the parser reads them; the two actual default
`0x84` paths remain native diagnostics. Compiler layout/type failures and
actual declaration-omission failures supplement complete source controls.
These bounded fixtures do not establish portable object layout, general
protocol, asynchronous IRQ interleaving, hardware or gameplay behavior.

# Connected serial session initialization and record replies

Five complete bodies add 744 bytes: initialization at `0x0801C9B8` (388),
receiving game record and option notices at `0x0801D048` and `0x0801D088`
(64 each), game-record reply at `0x0801D0D8` (128), and text-row reply at
`0x0801D168` (100). The final body ends at `0x0801D1CC`; the independent
four-byte return leaf that follows remains original and receives no credit.
These five sources use ordinary C without register annotations or added
reads, guards or initializers. The dispatcher changes only its four
same-address child identifiers.

The fixed phase table's flat row ten at `0x080579F4` contains initialization
`0x0801C9B9`, step `0x0801CB3D`, and shutdown `0x0801CE55`. The latter two
callbacks and slot preparation at `0x0801CDDC` are covered by the later
connected session-controller group below. The request-tail stores of 45
in these notices do not identify this table row. The background map-fill wrapper
`0x0800D6A8` is covered by the later defaults-provider group below.

Initialization configures the three observed backgrounds and text, reads
and validates save slot three, and conditionally calls the accepted
64-byte load-buffer body with a full incoming word of three. That body
overwrites incoming R0 before reading it. Its declaration and definition
now consistently accept an unused word; this expresses the actual incoming
call without recovering an original signedness or parameter declaration.
The provider contributes zero new C bytes. Its body and its existing source
control remain unchanged apart from that formal parameter.

The initializer writes the three observed halfwords with `0x1A03`, obtains
a zeroed 108-byte buffer and stores the word `0xC000`. Request mode zero
installs the specific notice handler with parameters 68 and 132; other
modes store that same handler at input setup offset 44 and select sequence
zero. No allocation guard is added. The separate session access view is
20 bytes/alignment four with halfwords at 0, 2, 4 and 6, matched byte at 8,
buffer pointer at 12 and word at 16. It overlaps the previously described
read-only notice-state prefix at `0x03001B70`.

Receiving `0x41` compares the first input word with the game word and copies
108 bytes into the session buffer. Receiving `0x42` copies eight option
bytes and indexes the original request-mode table with input byte eight.
Both leave the length output untouched and write their observed request
and status fields. Their readable input, writable session buffer, word
alignment and unchecked table index remain preconditions. There is no new
capacity or successful allocation claim.

Reply `0x81` writes two initial words followed by five observed copies,
produces length 108 and updates request/status fields. The source union is
a 220-byte/alignment-four access prefix at `0x03003950`, whose byte array
bounds each offset and whose word view supplies the two initial loads.
The output union is 108 bytes/alignment four, containing 27 words and the
same byte span. These are overlapping representation views, not complete
original global declarations or ownership claims. The existing 44-byte
need-state capture remains distinct from the 32-byte serialized child view.

Reply `0x83` writes the prefix byte eight, queries the current text bank for
each of eight rows, copies every terminating zero, and adds one zero byte
when the final address is odd. Its actual output pointer begins after the
prefix store; signed row progression reproduces the original loop. The
pointer difference is stored as a halfword. Valid text pointers, terminating
strings and the incoming pointer contract remain unchecked.

For bank observations zero through five, the eight per-row maximum string spans,
including terminating zeros, sum to 170 bytes. The prefix and possible alignment
zero give a static bound of 172 bytes, even if the getter selects a different
supported bank for each row. This fits the installer's 514-byte buffer provided
the allocation is live and writable. The selector condition remains open:
[save-header validation](SAVE_STREAM.md#transfer-and-checksum-boundary) does not
constrain byte ten to that range. This bound adds no runtime or protocol evidence.

Fresh compiler checks pin all partial sizes, alignments, field offsets,
widths and actual function definitions. Restoring the old void-input
load-buffer declaration, wrong child interfaces and wrong representation
views produces real diagnostic failures. Current header importers and
actual direct providers have fresh changed-source controls. Bounded native
fixtures compare initialization, the four children, the dispatcher, bank
getter and load-buffer body with explicit display, audio, save, allocator,
copy, division and installation hooks. Caller-saved registers are poisoned
at those hooks. The receiving branches preserve length, while both reply
branches write it before the parser's later source read under valid callback
preconditions. Unsupported `0x84` still has no length write and retains only
the separate earlier native omission diagnostics. These finite checks do
not establish asynchronous IRQ behavior, hardware, general protocol,
arbitrary pointer validity, capacity safety or gameplay behavior.

# Connected serial session controller and shutdown

Six complete bodies add 1,032 bytes: stopping input at `0x0801C8D8` (112),
the row-ten step at `0x0801CB3C` (372), status drawing at `0x0801CCB0`
(300), slot preparation at `0x0801CDDC` (120), shutdown at `0x0801CE54`
(60), and save commit display at `0x0801CE90` (68). Full pools and zero
alignment are included. The existing initializer changes only its
same-address slot-provider identifier. Its previous 388 bytes receive no
new credit. The independently bounded four-byte return leaf at
`0x0801D1CC` remains original, with no new C or glue credit.

The ordinary step calls the status drawer and switches on the existing
request word at offset 16. Phase zero tests the actual pressed-input table
at `0x03004228`; phases one through three decrement the unsigned request
timer and perform their original transitions when it becomes zero. Phase
two optionally calls world preparation `0x0801BB14`, writes the
observed world/input values, and calls the accepted world initializer.
Only then does it capture the session buffer and copy the two words and
five segments into the 220-byte capture. Its clear operation deliberately
overwrites the upper eight bytes of the first 16-byte segment. The input
word/byte union bounds all accesses within its 108-byte representation;
the destination byte-array pointer and subsequent offsets stay within the
220-byte representation. The 44-byte capture copy stays distinct from
the previously described 32-byte serialized needs view. Phase three
clears the observed 16 bytes and commits without initializing other
capture storage. Phase four and the default preserve their original lack
of step actions. World preparation's complete 84-byte body is covered by
the later defaults-provider group below; its gameplay purpose remains unproved.

The drawer indexes an observed seven-row prefix at `0x080530A8`, with two
halfwords per four-byte row. Text changes, the halfword delay and indices
two or three control the original drawing and animation calls. It reloads
object slot two after the animation provider and updates only physical
bit four at object offset `0xD3`. Both animation uses share the single
command root `0x08053114`; the drawer passes an explicit offset of two,
while slot preparation passes the root. When index one marks the saved
header, one real flags value is constrained to R0. Native instructions at
`0x0801CD80` through `0x0801CD84` initialize one, combine the loaded flags
and store a halfword. The value dies before subsequent work and spans no
call. Removing that sole constraint gives nine differences under both
normal and strict profiles. The other five bodies use no register hints. These sources add no reads,
guards, invented volatility or dummy values; the existing volatile setup
and register accesses preserve their concrete native reads and writes.

Slot preparation allocates object ID 24, stores it in the unchecked slot
array, sets flags 17 and the slot halfword, updates the palette nibble,
installs the specific original object callback, and supplies the observed
coordinates and embedded resource. Four ROM records at `0x080530C4` have
20-byte stride, byte coordinates and a 16-byte resource at offset four;
their actual resource pointers are word aligned. The provisional target
compiler view is 20 bytes/alignment four. The player-input view reaches
byte offset 49 and aligns to 52 bytes; it is an access prefix, not a
complete storage claim. The generic FrameObject view is 312 bytes within
the allocator's actual 320-byte object allocation. Successful allocation,
live pointers, slot count and message/input-table bounds remain unchecked
preconditions; no new guard is introduced.

Shutdown reads the queued kind and preserves the original input-stop
exception for kind twenty, then frees the session buffer and calls the
accepted transition, list and display cleanup providers. Input stop saves
and clears IME, performs the observed volatile register writes and discarded
word read at `0x04000150`, clears interrupt-enable bit seven and the shared
count byte, restores IME and IRQ table entry zero, frees both setup buffers,
and clears all 48 setup bytes including its handler at offset 44. These
numeric register accesses and IRQ-shared views do not establish device
behavior or asynchronous interleaving. The small commit body draws its
original message before committing save slot three.

Fresh actual-definition checks cover 35 physical properties and nine APIs;
ten wrong-width, offset, packing or interface cases reject. Seven real
provider-declaration omissions remain byte identical under the legacy
profile and reject under strict declaration diagnostics. All current
session-header importers and 22 additional direct providers have exact
positives and actual changed-source controls. Finite fixtures compare
398 cases with original and linked bytes and a separate semantic model,
executing all six bodies and seven accepted small providers. Their 124
control divergences include timer transitions, status thresholds, slot
flags and interrupt-mask changes. Explicit display, animation, allocator,
free, world, save and poll hooks poison caller-saved registers; pointer
replacement probes the actual object and session-buffer reloads. Four
interpreter failures include an invalid unmapped allocation result as a
diagnostic only, without a hardware fault or defined-source claim. The
fixtures retain earlier callback output-write preconditions and establish
no general capacity, protocol, hardware, asynchronous IRQ or gameplay
result.


# Connected world defaults and background map fill

Three complete C bodies add 112 bytes: world defaults at `0x0801BB14`
(84), a game-value word setter at `0x0801BC10` (12), and the zero map-fill
wrapper at `0x0800D6A8` (16). The latter has a 14-byte body followed by the
original two zero alignment bytes before the independent `0x0800D6B8`
entry. Its source contains only the alignment directive needed for those
bytes. None of the three bodies uses register annotations, added reads,
volatile qualifiers, guards or invented initialization.

The default-state body clears 1,876 bytes at the existing world root
`0x03003950`, prepares the accepted 800-byte actor-entry context at offset
220, calls the explicit original reset hook, and clears 52 bytes at the
existing input root `0x030040E0`. It writes one to byte 48, resets the
complete game-value word at world offset four through the new setter, and
passes world offset 16, ROM source `0x08052F48` and count 16 to the original
bounded string-copy routine. The 1,876-byte array is an observed access
span, not a complete global storage or ownership claim. The existing
player-input tag is reused; byte 48 is accessed through its character
representation within the independently checked 52-byte object.

Pinned target-compiler diagnostics establish the world span as 1,876 bytes
with alignment four, the actor context as 800 bytes with alignment four,
and the player prefix as 52 bytes with alignment four. The fixed world and
player roots, and world plus 220, satisfy that alignment. The game-value
view remains the existing eight-byte, alignment-four partial view with its
word at offset four. The setter's `int` formal follows accepted signed-word
consumers; the producer itself stores the complete input word and does not
establish the original declaration's signedness. The background wrapper
passes its complete word index and zero halfword tile and palette values
to the accepted map-fill provider. This does not claim that it disables a
background layer.

The serial initializer and step change only their two same-address
provider identifiers. All eleven current importers of the two session
headers and five additional heap, actor-entry, map-fill and game-value
providers are recompiled with actual changed-source controls. The return hook
at `0x0802A70C` now has a separately verified empty C definition covering its
four-byte slot, including two zero alignment bytes. Normal and strict caller
replays remain exact, and an actual state-changing call added to the hook is
rejected. The 112-byte padded string-copy provider at `0x0804EA70` already has
matching C and a padding-value control, documented in the
[string-provider evidence](LIBC_STRING_PROVIDERS.md). That later ownership
supersedes this path's earlier four-byte failed candidate; it adds no new credit
here. The reset caller's direct providers now all have source. Their valid input
and memory domains remain separately qualified.

Finite checks cover 32 initialized numeric-memory cases, with 32 actual
source-control divergences and four deliberate interpreter/input failures.
They execute the original and compiled defaults/setter/map wrapper, the
accepted heap clear and actor preparation, and the unchanged original hook
and copy bodies. Allocation and map-fill calls use explicit abstract hooks
that poison caller-saved values. Existing and failed allocation returns are
preserved as nullable stored collection pointers; the defaults body does
not dereference that pointer. The game-value negative fixtures avoid signed
overflow. These checks do not prove arbitrary pointer validity, allocator
success, table capacity, hardware/IRQ or protocol behavior, or gameplay.
