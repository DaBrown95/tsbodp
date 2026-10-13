# Attachment interaction 0x31

Ten semantic C replacements cover 1,016 matching bytes in the interaction and
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
| `0x2B9B0` | `frame_actor_need_average` | 40 |
| `0x2EDDC` | `frame_step_attachment_need_timer` | 88 |
| `0x2EE34` | `frame_attachment_need_is_low` | 68 |

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
the need/timer helper at `0x2EDDC` before requesting animation six
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
argument remains a full word and is stored unchanged. The step, dispatcher and need/timer helper
return a word, while route and need/timer results are narrowed at their callers.
The dispatcher does not check a failed lookup before dereferencing the record;
no additional validation was invented in the replacement.

The initial seven accepted sources use ordinary C with no fixed register
constraints or instruction bodies. Their only assembly directives select zero
alignment at four observed extent ends. Settings-derived attachment selection is evaluated before
loading the owner's object; this source lifetime reproduces the observed order.
The release helper uses a semantic inline record lookup, matching the already
published attachment status routine. Those existing status and finalizer sources
were freshly compiled with their actual changed-source controls: both still
match and both controls fail. No accepted caller or shared layout was changed.

Local evidence is retained under `reports/agents/display_audio/interaction/`:
raw disassembly and switch/callback observations, the failed initial contracts,
register and control-flow trials, and the public-source positive/control receipts.
The initial accepted-only metadata is `interaction-ready.json`; the follow-on
metadata is `interaction-needs-ready.json`. Wider owner callbacks and adjacent
return/write callbacks remain unconverted; retained candidates are excluded
from coverage. The page redraw
`0xF034`, text row reader, text rasterizer and background-map writer also remain
unmatched and excluded. These are connected next targets, not runtime claims.

## Connected need thresholds and countdown

The follow-on functions close the need/timer handoff and its adjacent threshold
consumer. `frame_actor_need_average` sums eight signed high bytes from successive
four-byte need values into an unsigned accumulator, divides by eight and narrows
the result to a byte. This matches the observed signed byte loads and logical
right shift; no additional range or nonnegative-value invariant is assumed.
The existing need-value getter reads the same high byte without sign extension.
`frame_attachment_need_is_low` treats selector eight as an average-only test
against 29. Other selectors additionally require the selected value to exceed
30. That latter selector is not range-checked in the original body.

The need/timer helper first returns zero when record byte `running` equals one.
Selectors above seven return one without touching the need or timer pointers.
For other selectors, a non-null need pointer is queried; a value at most 99
returns one without changing the timer. A null need pointer, or a value above
99, proceeds to the timer check. A null timer returns one; otherwise the helper
decrements the pointed word and returns whether it differs from exactly minus
one. The consuming interaction step observes the low byte, and advances to
its next route/animation phase when that byte is zero. These thresholds and
terminal values describe the code rather than a validated gameplay model.

Two short semantic inline helpers separate the need threshold and timer tick.
Each constrains only its own unsigned result local to `r1`, as required by the
matched compiler allocation; the threshold result is initialized after its
external query, and the timer helper makes no calls. No fixed result is kept
live across an external call, and no original instructions are embedded. The
need helper's local exit label preserves its result lifetime before the caller's
comparison. Both helper values remain zero or one. The definition uses a word
return and the existing interaction caller now explicitly narrows it to the
observed low byte. This is a coherent C contract that matches both extents;
the original source typedef is still unknown.

All three new public sources match and their real changed-source controls fail.
All seven interaction sources were recompiled against the updated header and
all their actual controls still fail; the main step's 464 bytes remain exact.
The follow-on checks cover the signed byte average, selector-eight branch and
threshold 99 through independent source mutations. Raw failed byte-return and
control-flow candidates remain local. No runtime test is claimed.
