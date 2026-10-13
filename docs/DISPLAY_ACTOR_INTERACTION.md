# Attachment interaction 0x31

Seven semantic C replacements cover 820 matching bytes in the interaction and
attachment-record path. Each complete linked extent, including its literal pool,
switch table and zero alignment where present, matches at its fixed ROM address.
Every replacement has a real compiled changed-source control that fails that
comparison. This is static source and compiler evidence; no runtime or gameplay
validation is claimed.

| ROM offset | Function | Bytes |
| --- | --- | ---: |
| `0xF4DC` | `frame_interaction_step_31` | 464 |
| `0xF6B0` | `frame_interaction_can_begin_31` | 40 |
| `0xF6E8` | `frame_interaction_begin_31` | 72 |
| `0xF730` | `frame_interaction_dispatch_31` | 32 |
| `0x2E3C4` | `frame_allocate_actor_attachment_record` | 88 |
| `0x2ED60` | `frame_find_actor_attachment_record` | 52 |
| `0x2ED94` | `frame_release_actor_attachment_record` | 72 |

The initializer obtains an empty record, stores its supplied selection word,
reads attachment two of the owner's object and starts a route for the target
actor. The dispatcher looks up the record for both owner and actor, then invokes
the step routine only when the stored selection is `0x31`. The callback table
at `0x08063680` includes pointers to the initializer and dispatcher alongside
adjacent callbacks that remain explicit unconverted ROM. The adjacent predicate
checks the actor's attachment count and the owner's byte at `+0x60`; its wider
callsite role remains uncertain.

The generated switch in the step routine covers indices zero through 45. Its
active cases are zero, one, 41, 43 and 45; other values return one. Case zero
starts a route using the game-state setting byte at `+0x20`. Case 45 copies the
owner object's direction, requests animation 50, writes 90 to actor word
`+0x58` and commits the owner's effect. Case 41 observes flag `0x400000`, clears
animation pending, plays cue 65 and advances the record. Case 43 adjusts need
22 using byte `+0x23` of the owner's 36-byte need-effect definition, then uses
the unconverted need/timer helper at `0x2EDDC` before requesting animation six
and starting another route. Case one requests animation one and returns two.
These selector, need, animation and cue numbers are static observations. Their
user-facing meanings and the callback return protocol are not established.

The code reuses `FrameActorAttachmentRecord` and `FrameActorAttachmentOwner`
from the published attachment status and finalizer path. Lookup and allocation
scan exactly three 24-byte records at owner `+0x0C`; their containing allocation
extent is not inferred from this bound. Record word zero points to the actor,
word four holds this interaction's selection, word eight is used as a state
selector here, byte `+0x0C` is retained as `running`, and word `+0x10` carries
route status. The existing field name `timer` for word eight remains because
other attachment code uses that view. Allocation clears the actor-independent
word and byte fields that it accesses; it clears only the low byte at `+0x14`,
not that entire retained word. Release clears the actor pointer and writes 94
to word eight. The separate `FrameNeedEffectState` owner view exposes its kind
and object at `+8` and `+0x54`. The casts make these overlapping views explicit;
they do not establish a universal owner type.

Inspecting the helper bodies corrected two initial contracts. Allocation takes
owner and actor; its third incoming register is unused. Lookup also takes owner
and actor, so the dispatcher has two arguments even though its first instructions
preserve the second argument without moving it. The caller's third initializer
argument remains a full word and is stored unchanged. The step and dispatcher
return a word, while route and need/timer results are narrowed at their callers.
The dispatcher does not check a failed lookup before dereferencing the record;
no additional validation was invented in the replacement.

All seven accepted sources use ordinary C with no fixed register constraints or
instruction bodies. The only assembly directives select zero alignment at four
observed extent ends. Settings-derived attachment selection is evaluated before
loading the owner's object; this source lifetime reproduces the observed order.
The release helper uses a semantic inline record lookup, matching the already
published attachment status routine. Those existing status and finalizer sources
were freshly compiled with their actual changed-source controls: both still
match and both controls fail. No accepted caller or shared layout was changed.

Local evidence is retained under `reports/agents/display_audio/interaction/`:
raw disassembly and switch/callback observations, the failed initial contracts,
register and control-flow trials, and the public-source positive/control receipts.
The accepted-only metadata is `interaction-ready.json`. The need/timer helper
`0x2EDDC`, wider owner callbacks, and adjacent return/write callbacks remain
unconverted; retained candidates are excluded from coverage. The page redraw
`0xF034`, text row reader, text rasterizer and background-map writer also remain
unmatched and excluded. These are connected next targets, not runtime claims.
