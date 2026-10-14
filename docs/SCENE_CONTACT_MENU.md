# Contact scene controller

The flat scene table at `0x0805797C` has row 20 values `0x08028A11`,
`0x08028BD1` and `0x080292ED`. The accepted contact-resource tick submits
kind 20 through the scene request provider. This identifies a connected scene
path; the names below describe static accesses and are not recovered original
identifiers or a claim about gameplay.

This connected path reconstructs sixteen C functions, totaling 2,908 bytes:

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
| `0x080293C0` | 80 | Handle command words `0x82` and `0x43`, with two halfword output pointers |
| `0x08029410` | 60 | Prepare a background, text control and palette ranges |
| `0x080297A4` | 180 | Initialize the primary activity's display, selected callback and view |
| `0x08029858` | 220 | Load the selected tile, palette, map and cell resources |
| `0x08029934` | 60 | Update the primary view and effects, then call an optional activity tick |
| `0x080299B0` | 80 | Initialize the secondary activity and restore its palette |
| `0x08029A00` | 40 | Call the selected secondary activity tick |
| `0x08029A28` | 16 | Release the primary object list on the alternate activity path |

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
halfword, invokes the selected original activity initializer, and updates the
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
