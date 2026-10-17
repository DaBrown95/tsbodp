# Attachment jobs 42 and 94

The initial five-function batch reproduces 692 bytes at its original addresses.
Normal and strict positives match the complete spans, including literal pools
and alignment. Changed-source controls reject under both profiles. No new
low-level instruction glue is introduced.

| Body | ROM offset | Instructions | Literals | Zero alignment | Full span |
| --- | ---: | ---: | ---: | ---: | ---: |
| Kind 42 update | `0x1DB2C` | 170 | 4 | 2 | 176 |
| Kind 94 update | `0x1DBDC` | 386 | 28 | 2 | 416 |
| Choices callback | `0x1DDA8` | 24 | 4 | 0 | 28 |
| Begin callback | `0x1DDCC` | 26 | 0 | 2 | 28 |
| Shared dispatch | `0x1DDE8` | 44 | 0 | 0 | 44 |
| **Total** | | **650** | **36** | **6** | **692** |

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
The nearby unrooted predicate remains unowned and adds no recovered-C credit.

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

Together these two stubs and the original five-function batch own seven
functions / 700 extent bytes: 656 instruction bytes, 36 literal bytes and eight
zero alignment bytes. The separately owned eight-byte EC action switch and
76-byte capacity predicate receive no additional credit. All observed nonnull
callback pointers in physical row 99 now point to matching C bodies. This closes ownership
of that row's stored callbacks, while selector domains, later pointer writes,
owner lifetimes and gameplay reachability remain open. The preceding unrooted
predicate and following return-100 body remain unowned.
