# Contact scene controller

The flat scene table at `0x0805797C` has row 20 values `0x08028A11`,
`0x08028BD1` and `0x080292ED`. The accepted contact-resource tick submits
kind 20 through the scene request provider. This identifies a connected scene
path; the names below describe static accesses and are not recovered original
identifiers or a claim about gameplay.

This connected path reconstructs twenty-nine C functions, totaling 5,048 bytes:

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
| `0x08033AF4` | 172 | Reset eight primary item slots and accumulate their byte penalties |
| `0x08033BA0` | 120 | Create the control object at fixed position, initial waiting state and callback |
| `0x08033C18` | 104 | Create the auxiliary selector object at fixed position and callback |
| `0x08033C80` | 224 | Create a selected item with coordinate words, animation and slot-derived flags |
| `0x08033D60` | 360 | Create a selected moving event with paired slot, position, speed and animation |
| `0x08033FA0` | 340 | Advance control phases, vertical motion, paired-slot removal and wait timer |
| `0x080341B8` | 292 | Advance the moving event, fill or update a secondary slot and retire it at a boundary |
| `0x080342DC` | 72 | Test the control byte and eight paired object identifiers |
| `0x08034324` | 52 | Retire nullable secondary objects and clear their slots |
| `0x08034358` | 44 | Load seven item palettes into descending banks |
| `0x08034384` | 104 | Create the primary object at fixed position and callback |

Every comparison includes the complete original extent, internal switch tables,
literal pools and alignment. Every function has an actual changed-source
negative control and a separate strict declaration diagnostic. The bodies use
ordinary C with no register bindings, added reads, volatile access views or
fabricated initializers. Source coverage remains separate from whole-ROM
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
carries no new C credit. The mode service and the original view
operations at `0x0800EB14` and `0x0800E8B4` are likewise explicit. Retained failed candidates and
raw comparisons distinguish genuine source-lifetime improvements from these
remaining mismatches.

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

The 232-byte activity step at `0x08033A0C` remains original. The three
connected creators are recovered below; the primary and auxiliary object
callbacks remain explicit original dependencies.
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
Other paths copy the actual next-position members into position. The
232-byte activity coordinator and primary and auxiliary callbacks remain
unconverted; this callback closes only the specific moving-event handoff.

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
target model, without a portable arbitrary conversion claim. The primary
callback at `0x08033EC8`, auxiliary callback at `0x080340F4`, activity tick at
`0x08033A0C` and need-adjustment provider remain explicit original bodies.

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
