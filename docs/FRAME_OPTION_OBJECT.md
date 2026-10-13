# Option object construction, interaction and completion

Observed factory slot nine at `0x0804F29C` contains `0x08013A9D`. Its payload
wrapper connects a constructor, two definition-selected configurations, three
two-object collision callbacks, a frame updater and action progression. Nine
complete matching C extents total 1,916 bytes:

| Function | ROM entry | Complete extent |
| --- | --- | ---: |
| `frame_create_option_object` | `0x08013444` | 276 |
| `frame_option_configure` | `0x08013558` | 260 |
| `frame_option_initialize` | `0x0801365C` | 160 |
| `frame_option_tick` | `0x080136FC` | 372 |
| `frame_option_interact` | `0x08013870` | 160 |
| `frame_option_action_step` | `0x08013910` | 396 |
| `frame_create_option_resource` | `0x08013A9C` | 112 |
| `frame_option_contact_interact` | `0x08011360` | 76 |
| `frame_option_restricted_interact` | `0x080113AC` | 104 |

All extents include their original literal pools and alignment and end at the
next independent prologue. The names describe observed selector behavior and
remain provisional. No original gameplay name or complete resource inventory is
asserted.

## Definitions, payload and callback protocol

The observed first three sixteen-byte records at `0x08051F18` contain a
one-object configuration pointer, two collision callback pointers and a signed
speed word. Kind zero configures through `frame_option_initialize` and installs
`frame_option_contact_interact` in slot `+0xC8`; kinds one and two configure
through `frame_option_configure` and install `frame_option_interact` in slot
`+0xCC`. Null pointers are preserved. The restricted subtype-two configuration
installs `frame_option_restricted_interact` at `+0xC8`, and leaves the second
slot untouched. This records three observed rows without adding a kind bound or
claiming that the table is exhaustive.

The constructor allocates class nine and preserves the original unchecked
allocation result. Its first argument is a complete unsigned word; it stores
halfword and byte versions at `+0xA/+0x4C`. Its direction and option arguments
are bytes. The coordinate formals are signed shorts: the resource wrapper's
original signed halfword loads establish the caller contract; the constructor's
later sixteen-bit shifts alone would not distinguish signed and unsigned
formals. Coordinates become 16.16 position and next-position words. The wrapper
accesses signed halfwords at payload `+4/+6` and kind, direction and option bytes
at `+8/+9/+0xA`; the unused first four bytes remain opaque in its access view.

The constructor selects a sixteen-byte animation record through the twelve-byte
pointer-triplet table at `0x08051ED8` and the existing unsigned direction table at
`0x0804F1B0`. It calls the definition's configure pointer, installs the frame
updater, clears OAM graphics mode and double size, reloads subtype for the speed
word, assigns flags `0x10050655` and writes two to unknown field `+0x84`. It then
runs the existing actor-state updater and chooses horizontal flip from direction
greater than four. Subtype zero increments the shared world byte at `+0x73E`.
The palette pointer table used by configuration starts at `0x08051F08`. These
data remain original unconverted ROM regions; their bytes are not embedded in
the source or counted as C. Table lengths, valid direction indices and the
meaning of `+0x84` remain uncertain.

The local header declares collision slots `+0xC8/+0xCC` with two `FrameObject *`
arguments. The already matched ARM collision dispatcher supplies both objects,
selecting `+0xC8 + bound_index * 4`, and reverses their order for the second
object's callback. Every new interaction materially uses R1. The generic actor
header's provisional one-argument declaration is unchanged. The configuration
entry differs: its indirect call passes only the object in R0, with the target
in R1. The compiler-generated call goes through the shared Thumb bridge
`_call_via_r1` at `0x0804CCF4`. That four-byte BX/NOP bridge is explicit assembly
with zero C coverage; its original alignment NOP and changed-target control are
verified separately. No runtime indirect-call or collision execution is claimed.

## Configuration, movement and input handoff

The normal configuration selects actor state nine, variant seven and a
halfword need timer of ninety. Subtype two instead enters state 44 and replaces
the primary callback when signed parameter three from the opaque option-parameter
root `g_frame_option_need_parameters` at `0x030039E8` is unsigned-comparable to at
most five and the low byte of
`condition_group_active(3,4)` is zero. The low-byte narrowing preserves the
original caller behavior under the established word-return condition API.
The existing `g_frame_actor_local_need_state` is pinned to `0x03003A00` and retains
its separate published view; its type and address are unchanged.
Four halfword parameters at `+0x68..+0x6E`, the speed word and the subtype palette
are then set through the observed subtype-dependent routes. Initialization uses
state nine, variant seven, need timer sixty, the definition callbacks and its
own halfword parameters, then selects palette slot one or two.

The resource wrapper handles observed kind zero directly, kind one through the
world byte at `+0xE5` and kind two through the low byte of
`condition_is_complete(3,4,0)`. Kind one's option must be at most seven before
shifting that flag byte. A completed flag suppresses construction; other values
and unmatched kinds continue to the constructor. Explicit kind zero agrees with
the definition row and its paired creation/removal counter. No additional guard
or table bound is introduced.

The frame updater calls action progression for state eighteen and the existing
actor state dispatcher for other states, except state one cleanup. Cleanup
preserves the flag update, decrements the same world byte at `+0x73E` for subtype
zero, plays cue 56 and submits `resource_set_triple(2,2,0)` when the byte becomes
zero. It captures direction before processing pending updates. Pending bit eight
refreshes velocity; bit four refreshes the base animation; bits `0x12` choose
one of the three animation families from the current variant. Variants three,
nine and four use family one and refresh velocity. Variant five uses family two,
and other variants use family zero; both latter routes share the motion stop.
The updater reloads pending state after calls and finally clears it. Known state
nine, 44 and 47 handlers are freshly reverified as connected consumers.

The ordinary interaction excludes object state eighteen and requires the other
object's state sixteen. It captures the selected player pointer through the four
existing twelve-byte input/view slots at `0x030040E0`, then performs the facing
test with the other object first. It snapshots whether that object has ID zero,
the low-byte bit-zero input press indexed by the selected player's `+0x13` input
slot, and the halfword-wrapped subtype-minus-one test for subtypes one and two.
A separate input-slot view avoids naming the player byte as this object's
serialized option. Eligible interaction stops this object's motion, enters state
eighteen and variant zero, puts the other object in state zero, stores its pointer
at `+0x64`, and clears input. Input-slot, pointer and allocation bounds are not
added.

Both additional contacts stop the two objects at their current positions before
checking eligibility. The normal callback then requires the other ID to be zero
and facing availability with the other object first. It clears this object's
flag four, sets variant five, and requests the other's animation thirteen and
variant 23. The restricted callback additionally requires the other's state
sixteen and reverses the facing argument order. Its eligible route requests the
other's animation 69, variant and state 47, and cues 184 and 46. The calls before
the checks are preserved; moving the checks earlier would remove observed effects
for rejected contacts.

## Menu result, entry insertion and completion

Action progression always stops the stored target first. Variant zero writes
result ID `0x17E1` at the existing result root `0x030059F0`, clears three request
bytes in the overlapping request root at `0x03005A00`, submits default request
two and enters variant 55. Variant 55 reads the word result at offset twelve
from the existing scene/menu result base `0x03004370`. Minus one reconfigures and
finishes. Otherwise the low-byte capacity test on the actor-entry list at world
`+0xF0` either begins target animation 32, variant fourteen and timer eight, or
runs the failure path.

Variant fourteen decrements the signed timer and waits for exactly minus one.
It then enters variant fifteen and inserts entry ID 125 or 126, depending on
subtype, with the serialized option byte and zero as the last argument. Only a
low-byte return of one is success. Successful subtype one with option at most
seven updates the corresponding world `+0xE5` bit; success clears flag one and
plays cue 179. Failure reconfigures, marks completion and sets bit `0x200000` in
the selected player's 56-byte UI record beginning at shared base `0x03004130`.
These records and the overlapping result/request views remain partial; their
complete storage and gameplay identity are not established here.

Variant fifteen waits for target flag `0x400000`, then requests this object's
state one and enables flag two. Every completed or cancelled route restores the
target to state sixteen, variant two and animation one. The target pointer, timer,
indices and return-byte domains retain the original unchecked behavior.

## Matching and remaining uncertainty

Four C replacements match without register bindings. The other five use actual
short-lived address or input values: constructor counter address R1; wrapper
world base R0; the frame counter address R4 across the cue call; action list-base
and flag-address values R0 before their calls; and the interaction's input mask
and captured result R2. The mask starts at one and is immediately combined with
the supplied pressed byte. It is a required input operand, not a discarded
initializer. Both R2 constraints and the by-value predicate are consumed before
the first call; removing either constraint fails the full comparison. Counter
R4 is callee-saved. No caller-clobbered binding is used after a call. Address,
boolean scheduling, shared motion-stop, signed-coordinate and table-address
failed attempts remain preserved locally.

All nine actual changed-source controls compile and reject. Thirty-one existing
connected C functions totaling 3,780 bytes are freshly recompiled with their
existing actual controls. Current source and literal header snapshots, complete
linked bytes, section/function ownership, boundary and pool evidence, original
addresses and the separate four-byte bridge control remain in ignored
`reports/agents/actor-interaction/` reports. There are no output patches, masks,
fabricated data or copied instruction bodies in the claimed C.

Source matching, whole-ROM equality, static callback/data connections and runtime
behavior are separate claims. Actual resource domains, gameplay choices, indirect
execution and timing remain unvalidated. Signed shifts and timer arithmetic retain
the pinned target compiler's behavior; portable ISO C behavior for every arbitrary
input is not asserted. Unconverted tables, resources and other callback targets
remain explicit in the ROM build.
