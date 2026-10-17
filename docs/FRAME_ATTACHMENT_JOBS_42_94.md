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
