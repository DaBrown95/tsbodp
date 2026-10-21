# Attachment jobs 42 and 94

Ten C bodies cover the contiguous range `0x0801DB2C..0x0801DE1C`, reproducing
752 complete extent bytes. Two remain unrooted: matching their source does not
identify incoming callers or callback roles. Normal and strict positives match
the complete spans, including literal pools and alignment; changed-source
controls reject under both profiles. No new executable assembly is introduced.

| Body | ROM offset | Instructions | Literals | Zero alignment | Full span |
| --- | ---: | ---: | ---: | ---: | ---: |
| Kind 42 update | `0x1DB2C` | 170 | 4 | 2 | 176 |
| Kind 94 update | `0x1DBDC` | 386 | 28 | 2 | 416 |
| Initialization callback | `0x1DD7C` | 4 | 0 | 0 | 4 |
| Unrooted predicate | `0x1DD80` | 38 | 0 | 2 | 40 |
| Choices callback | `0x1DDA8` | 24 | 4 | 0 | 28 |
| EC action switch | `0x1DDC4` | 8 | 0 | 0 | 8 |
| Begin callback | `0x1DDCC` | 26 | 0 | 2 | 28 |
| Shared dispatch | `0x1DDE8` | 44 | 0 | 0 | 44 |
| Empty tick callback | `0x1DE14` | 2 | 0 | 2 | 4 |
| Unrooted constant result | `0x1DE18` | 4 | 0 | 0 | 4 |
| **Total** | | **706** | **36** | **10** | **752** |

The 36-byte definition row 99 begins at `0x08063C68`. Its field 16 supplies the
shared dispatcher, which looks up an attachment record, selects full-word kind
42 or 94 and otherwise returns zero. Definition-row index 99 and record kinds
42/94 are distinct. The row's choices and begin callbacks feed this path; its
init and tick callbacks also have matching C source, as described below. EC has
matching C source. The unconditional lookup-result dereference is retained,
without a new null guard.

Both workers capture the actor's need-state pointer before their phase switch.
Running byte exactly one selects cleanup. Phase zero initializes animation 35,
phase 64 and the signed actor countdown to 150. Kind 42 takes the owner's
direction and retains the handle returned by cue 70. Kind 94 reads signed
parameter two before clearing its indicator, conditionally creates an indicator
and turns toward the owner, then applies the owner's direction through the
existing setter. It stops sequence playback before selecting the parameter's
sequence byte. Unknown phases retain result one.

The need-adjustment provider's second argument selects a table row across eight
needs: kind 42 uses row 16; kind 94 uses row 16 for parameter ten and row 35
otherwise. The definition's byte 35 selects the multiplier-table entry used by
the provider.
The older kind-48 and kind-71 workers likewise select adjustment row 12.

In kind 94's phase 64, a non-ten parameter updates the indicator and rereads the
parameter before testing advancement. Parameter ten directly decrements the
actor countdown. Both branches then call the existing need/timer helper, even
if cleanup was already selected. That helper can decrement the same countdown
again. Each reached signed decrement must be representable; excluding only an
initial `INT_MIN` is insufficient on the double-decrement path. No fixed frame
duration or universal completion-call count follows.

Cleanup restores animation and effect state. Kind 42 stops its retained sample;
kind 94 finishes a retained indicator, stops the sequence, rereads the canonical
scene period and selects the period's audio. The selector's actual full definition
takes an unsigned byte. The need/timer helper returns a word, but both workers
consume only its low byte.

The sequence access at `0x080534D8` scales a signed parameter by four and loads
one byte. Its provisional read-only byte-row view does not establish an original
row type, complete capacity or disjointness from the unknown-extent text-ID table
at `0x08053460`. Valid nonnegative row backing and valid audio resources remain
source preconditions; the signed-byte reader alone proves no safe array index.

Existing actor, owner and work views remain conditional selector-specific
contracts. Reached pointers, definitions and resources need initialized backing
and valid lifetimes. Allocator-null indicator creation is outside the actual
provider's defined completion domain. No runtime fixtures, nested-provider
execution, hardware behavior or gameplay have been established for this batch.

The dispatcher uses a sparse switch: both kind comparisons precede the default
result and the two worker blocks. The worker checks cover 36 layout facts and
four complete existing provider definitions. Fourteen other provider type units
are reused through exact source, prototype, preprocessor, assembly and header
identity; they were not recompiled for this batch. Deliberately wrong API and
layout units reject. These type checks add no provider or runtime coverage.

## Selection and allocation callbacks

The same definition row supplies the selection callback at `0x1DDA8` and begin
callback at `0x1DDCC`. Their full spans add 56 bytes: 50 instruction
bytes, four literal bytes and two zero alignment bytes. The selector has a
28-byte compiler symbol including its literal; begin has a 26-byte symbol and
an explicit instruction-free alignment directive reproduces the following two
zeros. Both profiles match the complete spans. Changing scene 41 to 40 differs by one
byte. Changing the stored kind to kind plus one produces 32 bytes and differs at
24 offsets, including four bytes beyond the reference span. The controls compare
complete outputs without truncation.

Selection always writes kind 42 into the first choice byte. It writes kind 94
into the second byte only when the canonical unsigned scene word is not 41.
It writes no terminator and leaves the second byte unchanged in scene 41.
The target-search caller starts with seven zeroed bytes, whereas the object
choice builder reuses its choice buffer. Scene 41 alone therefore does not prove
that a reused buffer contains no kind-94 choice.

Begin calls the existing attachment-record allocator with the owner view and
actor. Failure returns zero. Success writes the complete unsigned kind word
and returns one; this callback performs no route or animation work. The
allocator clears selected record fields and only the low byte of its unknown
word at offset 20, rather than initializing all 24 bytes. Valid connected work
still requires the existing conditional owner and actor storage contracts.

Both observed selector callback owners agree on a word result and state/output
pointer arguments. Both begin callback owners agree on a word result and
state/actor/full-word-kind arguments. The observed callers consume the begin
result through its low byte. The init, EC and tick callbacks are now owned by C.
The adjacent predicate and constant-result body also have matching C, without
identified incoming callers or installed callback roles.

The follow-up checks cover 16 shared physical layout facts, the three actual
callback pointer types and the complete accepted scene initializer with a named
unsigned-word declaration. Deliberately wrong callback widths, record offset and
scene-word width reject for the intended type/layout errors. The existing full
allocator type unit is reused through exact source, prefix, preprocessor,
assembly and dependency identity; it was not recompiled for this follow-up.
These checks establish no additional provider execution or gameplay behavior.

## Initialization and tick closure

Two additional dedicated callbacks reproduce eight full extent bytes:
`frame_initialize_attachment_jobs_42_94` at `0x0801DD7C` returns unsigned one,
and `frame_finish_attachment_jobs_42_94` at `0x0801DE14` has a void result and
performs no operation. Both receive the existing `FrameNeedEffectState *`.
Row 99 stores these pointers at offsets zero and twenty. The allocator copies
the latter to state `+0xF8`, where the actual attachment-step consumer calls it
as a nullable void callback. The historical finish name does not establish
that it is only called during teardown.

The empty tick has a two-byte return and two zero alignment bytes. The pinned
GNU 2.10.1 assembler emits a two-byte input section from unchanged compiler
assembly, and the linker supplies the natural two-byte zero tail. The modern
assembler's different alignment bytes are a retained failure. No executable
assembly, output patch, mask or copied instruction body supplies either C match.
Normal and strict positives match the complete four-byte slots. Changing the
initializer result to zero and making the empty tick store optional value one
both reject in full under both profiles; controls that grow are not truncated.

The workers and row-local callbacks, including the eight-byte EC action
switch, account for eight bodies / 708 extent bytes in this range. The separately
owned 76-byte capacity predicate lies outside it and receives no additional
credit. All observed nonnull callback pointers in physical row 99 point to
matching C bodies. This closes ownership of that row's stored callback bodies;
selector domains, later pointer writes, owner lifetimes and gameplay
reachability remain open.

## Adjacent unrooted bodies

The predicate at `0x0801DD80` calls the existing unsigned-byte attachment
counter on its actor argument. Only a nonzero result reads the owner's byte at
`+0x60`; it returns zero when that byte equals one and returns one otherwise.
The source uses the existing 256-byte `FrameNeedEffectState` owner and proper
`FrameObject *` counter interface. Valid reached owner/actor backing remains a
precondition. The body contains 38 instruction bytes and two following zeros,
reproduced by an instruction-free alignment directive.

The four-byte body at `0x0801DE18` returns unsigned 100. Its chosen `(void)`
interface states the project's callable view; original unused formals and
historical result signedness are not established by the return instruction.
Together these bodies add 44 bytes, giving the ten-body / 752-byte contiguous
source range above. They add no observed callback or entry root.

Both complete spans match under normal and strict profiles. Changing the
predicate's comparison from one to zero changes one byte at offset 22 in each
40-byte control. Changing 100 to 99 changes the first byte in each four-byte
control. Actual definitions, the owner byte's offset 96 and size 256, and the
counter's unsigned-byte result receive type/layout checks. Deliberately wrong
offset, result, arity and pointer units reject; the chosen unrooted arity check
establishes declaration/definition consistency, not historical ABI.

No checked direct branch, canonical or mirrored entry pointer, indexed call
or observed definition-table callback identifies an incoming caller for these
two bodies. This finite static absence does not establish dead code or close
computed, writable or serialized target domains. The unrooted
[node-pool lifecycle](FRAME_NODE_POOL_1DAC4.md) immediately before this range
remains a separate state/call protocol; physical adjacency supplies no gameplay
connection. The twelve bytes at `0x1DB20..0x1DB2C` remain unresolved.

## Row 85 counter choices

Eleven C bodies account for the contiguous 608-byte interval
`0x08023238..0x08023498`: 522 instruction bytes, 64 referenced literal bytes
and 22 zero alignment bytes. This establishes source ownership of those bodies;
it does not close their incoming calls, data domains or gameplay path.

| Body | ROM offset | Full span |
| --- | ---: | ---: |
| Initialization callback | `0x23238` | 4 |
| Separate attachment predicate | `0x2323C` | 40 |
| Choice selector | `0x23264` | 96 |
| EC acceptance callback | `0x232C4` | 68 |
| Begin callback | `0x23308` | 28 |
| Kind dispatcher | `0x23324` | 64 |
| Empty finish callback | `0x23364` | 4 |
| Kind 19 worker | `0x23368` | 128 |
| Kinds 68/69 worker | `0x233E8` | 136 |
| Present choice helper | `0x23470` | 20 |
| Remove selection helper | `0x23484` | 20 |
| **Total** | | **608** |

Begin and dispatch use the actual allocator and finder interfaces, both taking
`FrameNeedEffectState *`. The workers use the existing `FrameActorSceneState`
through `ResourceGameState.scene`: counter `+0x744` is an unsigned halfword,
variant `+0x749` an unsigned byte and timer `+0x74C` a signed word. EC reads the
existing signed value at `+4` through `ResourceGameState.actor_values`, whose
member type is the existing eight-byte `FrameActorValueWorld`. Both members view the existing shared state storage. The partial union has
`0x754` bytes under the ARM32 layout checks.

EC keeps one late zero return and one late one return. For variant one, its
kind-equality branches reach the common acceptance label and both mismatches
share rejection. This reproduces the native branch directions that the prior
68-byte candidate missed. It is a compiler match for this source and context,
not proof of the original source spelling.

The definition-row index 85, record kinds 19/20/68/69 and callback offsets are
distinct. The observed row prefix identifies callbacks but does not prove a
complete table capacity or all incoming roles. The separate predicate has no
established incoming caller. Unused callback arguments and the generic EC
consumer remain provisional. The dispatcher retains the native unconditional
finder-result dereference, requiring a matching record and valid backing.

The selector uses the same proper state views and the owned number formatter.
Its short cached state pointer and counter-address values use genuine native
register constraints; neither crosses a formatter call. Full positive and
changed-source control checks cover all 96 bytes, including its literal pools
and two-byte alignment. These constraints describe the matched values and
lifetimes, without establishing the original source spelling.

Settlement `0x0801BA40` remains a 188-byte original dependency. Its latest private
counter-record candidate is 188 bytes with 22 differing bytes: native
zero-before-STRH and read-cursor producers are recovered, while register homes
still differ. That record/header adaptation remains unqualified and unadopted.
Selection removal `0x080454DC` remains a 192-byte original dependency. Their
declaration checks add no provider execution or source ownership. Choice-index
capacity, overlapping scene/menu views, later writers, resource validity,
object lifetimes and gameplay reachability remain open.

## Observed row 117 and kind 68

Six further C bodies own 392 bytes: initialization, selection, preparation,
the 260-byte phase worker, its 32-byte dispatcher and the 80-byte refresh
callback. They contain 344 instruction bytes and 48 referenced literal bytes.
Together with the existing 72-byte begin adapter and separately bounded
40-byte predicate, they cover the 504-byte local span `0x25A14..0x25C0C`.
The predicate's incoming roots remain open.

The worker uses phases 0, 78, 79 and 1. It reverses the owner's facing,
requests animations and cues, changes need-effect status, and reads the
canonical game-state value and scene counter. A running record selects phase
1. Phase 78 may activate request `0x125`, advance to phase 79 when the actor
flag is set, and call the still-unconverted settlement provider. The dispatcher
uses the canonical record finder and accepts only kind 68. The refresh callback
updates the owner's animation on a selected-row check, resetting its byte clock
to 100 before decrementing it.

The sources reuse the existing record, need-effect and game-state union owners.
Current normal and strict comparisons match every byte; genuine cue, kind,
clock and return changes reject. The preparation control changes its kind-68
return and grows from eight to sixteen bytes; the other five controls retain
size and differ by one byte. Actual owned definitions remain exact in separate
source contexts; the settlement declaration is checked separately from byte
ownership. No instruction-body assembly or new register constraint is used.

The observed definition row connects these callbacks; it does not close the
generic EC caller or establish all incoming formal roles. Record lookup success,
actor/owner lifetime, reverse-direction index, saved selection, clock writers,
and wider callback populations remain preconditions. The 188-byte settlement
provider remains an original-ROM dependency and receives no C credit here.

## Definition rows 76, 77 and 78

Fourteen matching C bodies own 192 extent bytes: row 76's seven-body range at
`0x08018074..0x080180D0`, and seven shared bodies for rows 77/78 at
`0x08043A2C..0x08043A90`. Each family includes six installed callbacks and a
separate 40-byte attachment predicate. Six source-emitted two-byte zero tails
are included in these full extents. The neighbouring constant-result bodies at
`0x080180D0` and `0x08043A90` remain excluded; adjacency supplies no entry root.

Both selectors clear the first choice byte. Begin uses the real record allocator
and stores the supplied full-word kind. Row 76's status returns two; the shared
77/78 status calls the real record finder and returns zero. The empty F8 body
uses the actual void tick interface; its finish name does not establish a
teardown-only role. The three observed rows retain the already owned common capacity callback
at `0x0802F348` and a null query slot. Neither separate predicate is installed
by these rows or has an identified incoming caller.

The [row 76](../include/frame_actor_attachment_definition_76.h) and
[shared 77/78 declarations](../include/frame_attachment_definitions_77_78.h)
use the existing owner, byte-output, actor and full-word interfaces. Normal and
strict full-byte comparisons and real changed-source controls pass for every
body; actual complete provider/caller definitions qualify the observed
E8/F0/F4/F8 types. The initializer and `prepare(void)` declarations establish consistency with
the chosen C definitions; unused original formals and the generic EC caller
remain unproved. Owner/actor backing, record lifetimes,
selector bounds, later pointer writers and complete target populations remain
open; these are static and compiler findings, not runtime observations.

## Shared position-cycle ends and row 92

The shared initializer at `0x080357FC` and tick at `0x080358AC` own eight C
extent bytes. The observed rows 59–62 and 80–82 install these entries. The
initializer returns one; the tick is an empty void callback with two source
zero-alignment bytes. The initializer's unused formal and historical result
type remain provisional. The uninstalled predicate at `0x08035800` receives no
credit from these rows.

Row 92's remaining six rooted bodies own 600 C extent bytes:

| Body | ROM address | Full extent |
| --- | --- | ---: |
| Kind 12 worker | `0x08045FB4` | 156 |
| Kind 45 worker | `0x08046050` | 156 |
| Kind 59 worker | `0x080460EC` | 216 |
| Initializer | `0x080461C4` | 4 |
| Kind dispatcher | `0x08046288` | 64 |
| Empty tick | `0x080462C8` | 4 |

The first two workers reuse already matched operation graphs at their separate
original addresses. Kind 45 enters cleanup for any nonzero running byte; kinds
12 and 59 require equality to one. Kind 59 preserves the needs-pointer capture,
separate direction-byte read, animation choice and phases 0/46/47/1. The
dispatcher's action enum and source case order 59/12/45 reproduce the compiler's
comparison tree; they do not identify the historical typedef. Finder results
are dereferenced without adding an unobserved guard.

The row's capacity, choice selector, EC entry and begin body already have C
owners. All observed nonnull stored callback bodies in row 92 therefore have
source. The separate predicate at `0x080461C8` remains uninstalled and excluded.
This is source ownership of a finite observed row, not complete callback,
selector, writable-target, backing, scheduling or gameplay closure.

The eight new bodies contribute 608 full C extent bytes, including ten
source-emitted zero-alignment bytes. Normal and strict complete-byte positives
and all real changed-source controls pass; growing controls retain their whole
output. Actual provider/caller definitions and deliberately wrong callback
contracts qualify the chosen interfaces. Full matching/control and progress
gates verify the integrated sources. No executable assembly or original
instruction payload supplies these replacements.

## Restoration rows 125/126/139 and row 138

Three matching C bodies contribute 156 extent bytes: restoration at
`0x0802CA74` (148), row 138 initialization at `0x0804649C` (4) and its empty
tick at `0x08046588` (4). These contain 146 instruction bytes, four referenced
literal bytes and six source-emitted zero-alignment bytes. Normal and strict
complete-byte positives and real changed-source controls pass; the tick control
retains all eight emitted bytes.

Restoration keeps the flag gate and the distinct coordinate views: kinds
125/126 create option objects from signed pixel halves, while kind 139 passes
full fixed-point words to the saved-effect provider. Kind 125 conditionally
clears the actual shared-state byte at `+0xE5`, then reloads the owner object.
The final state setter reloads it again after any opaque creation call.

The revised source combines a short-lived R2 base-address pointer with a
separate ordinary case-125 object pointer. Its output retains the native base
literal and `+0xE5` addition, and the fresh R0 object load with the old R4 home
available as coordinate scratch. These are two output observations from one
combined source change. Neither edit was independently ablated, so this does
not isolate their causal contributions or establish the original source spelling.

The [restoration declarations](../include/frame_need_effect_object_restore.h)
and [row 138 declarations](../include/frame_optional_parameter_lifecycle.h)
retain the canonical owner, signed-short option coordinates and pointer-returning
providers. API checks compile six complete actual source definitions with their
original leading includes, plus proper global-union and F8-consumer witnesses.
The eight positive translation units and two intended prototype/layout negatives
pass. The initializer's unused formal and historical result spelling remain
nonunique; its factory ignores the result.

Rows 125/126/139 share restoration and the already owned capacity callback.
Row 138's selector, check, begin, status, capacity and two connected workers
already have C owners. All observed nonnull stored callback bodies in these four
rows therefore have source after integration and full gates. This is finite
stored-target ownership. Runtime installation/populations, generic EC delivery,
selector bounds, later writers, owner/object/world backing, allocation success
and incoming signed-coordinate domains remain open. The following entries at
`0x0802CB08`, `0x080464A0` and `0x0804658C` remain excluded.

## Independently bounded route-49 worker

The [worker at `0x258C4`](../src/frame/frame_step_route_attachment_49_258c4.c)
and [wrapper at `0x259F0`](../src/frame/frame_dispatch_route_attachment_49_259f0.c)
add 192 matching C extent bytes. The worker owns 154 instruction bytes, four
literal bytes and two internal alignment bytes; the wrapper owns 32 instruction
bytes. Both retain the existing need-effect, actor and attachment-record owners,
with [shared declarations](../include/frame_route_attachment_49.h).

State zero copies the owner's direction to the actor, sets state 41, requests
animation 50 and stores countdown value 150 at actor `+0x58`. State 41 waits
for animation flag `0x400000`, clears it through the existing provider and sets
state 43. State 43 applies need criterion 24 using the definition byte at `+35`,
then passes the countdown and argument four to the existing timer provider.
A zero low-byte result sets state one and requests animation one. The worker
returns two when the final state is one, and one otherwise.

The wrapper looks up the actor's record, dispatches kind 49 to the worker and
returns its full-word result; other kinds return zero. The lookup's null result
is dereferenced without an added guard, preserving the native backing premise.
The neighboring route-begin adapter at `0x259A0` was already owned and receives
no additional credit. No incoming root connects these two new bodies to a
complete callback or gameplay population.

Complete normal/strict comparisons, real criterion/kind changes, actual provider
contracts and full-ROM matching/control gates pass. These independently bounded
bodies were already mapped; no executable discovery or runtime coverage is
claimed. Record/actor lifetimes, descriptor indexing, countdown arithmetic and
all other input/writer populations remain conditional.
