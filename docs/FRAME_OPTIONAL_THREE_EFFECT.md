# Optional mode-three effect lifecycle

Three connected ordinary C replacements cover 204 original extent bytes. They
implement the initializer, begin callback and installed per-frame callback of
need-effect definition row 41. A separate four-byte Thumb `_call_via_r3` bridge
preserves `bx r3` and its original alignment NOP, with zero C coverage. Names and
role views remain inferred; these are source/compiler and static claims without
runtime or gameplay evidence.

| Original ROM extent | Reconstructed function | Bytes |
| --- | --- | ---: |
| `0x18A20` | `frame_optional_three_effect_initialize` | 12 |
| `0x18A5C` | `frame_optional_three_effect_begin` | 68 |
| `0x18AAC` | `frame_optional_three_effect_tick` | 124 |
| `0x4CCFC` | `_call_via_r3`, explicit Thumb glue | 4 |

## Descriptor and concrete callback contract

The definition table at `0x08062E7C` has a 36-byte stride. Row 41 starts at
`0x08063440`, with the new initializer at row `+0` and begin callback at `+12`.
The accepted `frame_allocate_need_effect_state` allocates a 256-byte list node
and copies row `+12` to state `+0xF0`. It also copies the other callback slots and
the descriptor's three enabling bytes. This row's search-enabling byte `+34` is
zero; the generic state-39 search alone does not establish its reachability.

The concrete accepted `frame_need_effect_begin_optional_three` sets its own
state's byte `+0x72` to three and halfword `+0x70` to 12800. It searches for one
object of class five and kind 41, then invokes that object's state callback at
`+0xF0` with `(state, 0, 0)`. The indirect handoff puts the target in R3 and uses
the `_call_via_r3` bridge. Thus the new begin view has a state pointer in R0 and
two unused zero word arguments in R1/R2. Its body ignores both words, and this
producer ignores its observed R0 result of one. Other rows' callback signatures
and result widths remain provisional; no generic shared callback ABI changed.

`frame_step_optional_activity_attachment_job` is the accepted direct caller of
that producer. Its phase 54 starts optional mode three after its countdown and
reset succeed, then sets its job countdown to nine. The accepted
`frame_need_effect_consume_optional_three`, called by
`frame_step_optional_attachment_kind_22`, subtracts 128 while the signed
parameter exceeds 128; it then clears optional mode and parameter. These
concrete producer/consumer paths explain the pending condition scanned by the
new callback without treating every list node as this row's private state.

The accepted spawn routine passes the descriptor's `+0` callback and state
pointer through the existing explicit `_call_via_r1` bridge. It ignores the
initializer's observed result of one. Its row-41 normal update path is
`frame_need_effect_tick`; the subtype-141 branch still points at the explicit
unconverted special callback at `0x0803698C`.

## Local state, countdown and completion

The initializer clears state byte `+0x64`, here named `active`. Begin calls the
existing scene-choice completion helper with zero, requests owner appearance
three through `frame_commit_need_effect(owner, 3)`, requests animation cue
32, and saves the returned word at state `+0xE0`. It sets bytes `+0x64/+0x65`,
sets the owner's signed countdown at object `+0x58` to ten, and installs the new
step callback at object `+0x88`. Byte `+0x65` has a neutral name because its
other consumers and broader meaning remain unresolved.

The step callback reads its state pointer from object `+0x64`. When the state's
active byte equals one, it decrements the countdown. At minus one it walks the
canonical need-effect active list rooted at `0x03005868`, following each state's
next pointer at `+0` and inspecting its optional byte at `+0x72`. If any node
retains mode three, it reloads ten. Otherwise it requests owner appearance two,
calls the game sample-stop wrapper with the saved word, clears both local
bytes and clears its installed owner callback. The list root retains the
existing canonical alias `g_frame_pending_action_head` at the same address;
this source uses the stronger established need-effect list/state access views.

The cue helper and stop wrapper obey the game sample-volume setting. Calling
them does not prove that cue 32 plays or that a sample stops in gameplay. No
cue table bound, state allocation guard or broader timer range has been invented.
Their short ROM sample dispatchers remain original at `0x0804C878`,
`0x0804C888` and `0x0804C88C`. Their literal targets are the existing copied
sample start, release and step providers at `0x030002EC`, `0x03000320` and
`0x030003E8`; those C bodies are freshly verified at their execution addresses.
The ordinary scalar declaration order and cleanup-first branch reproduce the
original lifetimes without register bindings or volatile accesses. Failed
alternative lifetimes and the older generic pending-action view remain local
comparison evidence.

## Complete extents and proof boundary

The initializer has ten native function bytes followed by two original zero
alignment bytes. It ends before the independent prologue at `0x18A2C`. Begin
includes its installed Thumb callback literal at `0x18A9C`, ending before the
constant-one helper at `0x18AA0`. Tick includes the active-list literal at
`0x18B18` and the original trailing alignment; it ends before the independent
prologue at `0x18B28`. The unreferenced predicate at `0x18A2C`, neighbouring
constant/no-op helpers and descriptor predicate at `0x0802F348` remain explicit
original regions, with no new C credit.

Each new C extent and the bridge has a real changed-source negative control.
The finite fresh proof closure covers the concrete mode-three producer,
consumer and their direct callers; definition allocation/list maintenance,
spawn and all its accepted importers; directly selected scene, animation and
audio providers; and every accepted canonical `_call_via_r3` importer. Existing
providers receive no new source credit.

Eighteen metadata consumers retain a bridge alias; fifteen have actual bridge
relocations. The other three audio-player bodies use R1/R2 or direct transfers;
their unused aliases receive the same fresh checks and remain unchanged.
Literal current header closures, allocated native sections, function extents,
symbol mode/address, pools,
alignment and global aliases are audited separately. Publication gates verify
whole-ROM integration; this static closure does not establish runtime behavior.
