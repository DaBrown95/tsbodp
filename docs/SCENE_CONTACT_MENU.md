# Contact scene controller

The flat scene table at `0x0805797C` has row 20 values `0x08028A11`,
`0x08028BD1` and `0x080292ED`. The accepted contact-resource tick submits
kind 20 through the scene request provider. This identifies a connected scene
path; the names below describe static accesses and are not recovered original
identifiers or a claim about gameplay.

This connected path reconstructs ten C functions, totaling 1,880 bytes:

| Entry | Bytes | Observed role |
| --- | ---: | --- |
| `0x08028BD0` | 556 | Advance phases 0 through 6 and dispatch activity, notice and return operations |
| `0x08028EBC` | 124 | Refresh the amount text when state flag 8 is set |
| `0x08028F38` | 184 | Clear display storage and start the selected activity, clock text and transition |
| `0x08028FF0` | 264 | Load the completion background, selected label and explanatory text |
| `0x080290F8` | 188 | Check two unsigned parameter results and a signed amount, then write the selected value |
| `0x080291B4` | 312 | Send condition triples from scene and saved-value tests |
| `0x080292EC` | 96 | Retire objects or clear state flag 16, then reset display and audio dependencies |
| `0x080293C0` | 80 | Handle command words `0x82` and `0x43`, with two halfword output pointers |
| `0x08029410` | 60 | Prepare a background, text control and palette ranges |
| `0x08029A28` | 16 | Release the primary object list on the alternate activity path |

Every comparison includes the complete original extent, internal switch tables,
literal pools and alignment. Every function has an actual changed-source
negative control and a separate strict declaration diagnostic. The bodies use
ordinary C with no register bindings, added reads, volatile access views or
fabricated initializers. Source coverage remains separate from whole-ROM
matching and runtime evidence.

# Observed representations and contracts

The original initializer allocates 420 zeroed bytes and stores a scene byte at
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
Definition records use a 28-byte stride: an eight-byte clock at `+8`, eight
delta bytes at `+16`, sequence byte at `+24` and flags at `+25`.

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

The initializer `0x08028A10` remains original, with a complete 448-byte extent.
Need adjustment `0x0802944C` / 100 bytes also remains original. Their
typed call declarations are local, provisional descriptions of observed
operands and carry no new C credit. The original primary/secondary activity
ticks and mode service are likewise explicit. Retained failed candidates and
raw comparisons distinguish genuine source-lifetime improvements from these
remaining mismatches.

The source preserves unchecked player, scene and table accesses, nullable
cursor handling, callback output writes and the original teardown behavior.
It adds no capacity guards or allocation failure handling. These are static
and compiler-matching findings; this batch does not establish complete scene
formats, hardware execution, save compatibility or gameplay correctness.
