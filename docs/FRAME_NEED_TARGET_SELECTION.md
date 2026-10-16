# Actor need-target selection

`frame_find_need_target` covers the complete 272-byte span at `0x08006F20`.
It connects the existing actor states 24, 26 and 35 to need-effect checks,
action-list production and the accepted target-use handoff. Those callers and
providers gain no additional coverage from this replacement. Names and field
roles remain inferred.

The routine reads eight need values through the existing byte-return provider.
Values at most 30 increment a byte count and append their index to a local
eight-byte array. The original subsequently uses the random ordinal directly,
without reading that collected array. The source preserves this behavior;
it does not substitute the collected need index or infer the intended algorithm.

When the count is nonzero, the routine selects an ordinal from zero through
count minus one, then walks the existing need-state list. It captures `next`
before calling anything, checks definition byte `+34`, calls the state's
word-return predicate at `+0xE4` and tests only its low byte. An accepted node
receives a cleared seven-byte action buffer through callback `+0xE8`; that
callback's return value is unused. The routine scans at most seven nonzero
codes, stopping at zero, and compares the existing action-text row's first
halfword with the selected ordinal. The first match writes the target pointer,
then the full-word action code, and returns one. Failure returns zero without
writing the outputs.

The actor's need-state pointer is copied from four bytes of the whole canonical
`FrameObject` representation at `+0x60`. This stays within its 312-byte extent
and avoids introducing another actor word overlay. The state/list access uses
the existing `FrameActionSearchNode` view and callback declarations. Reuse does
not prove universal effective-type compatibility of every legacy allocator,
list and state view. The copied pointer must have a valid target representation.

The current observed definition prefix contains 149 rows of 36 bytes. Its
allocator copies definition `+28` to state `+0xE4` and definition `+4` to
`+0xE8`. All six observed predicate targets have matching word-return C
contracts. The observed action producers include 21 matching C targets and
38 original targets; their wider capacity and side effects remain uncertain.
Null action callbacks in observed rows 125, 126 and 139 are excluded by their
zero enabled byte. This finite table finding does not exhaust writable callback
assignments or establish a complete runtime population.

Calls require a live, finite list, backed definition/action rows, compatible
callbacks and output objects, and valid need storage. The action writer must
stay within seven bytes and must not retain the buffer beyond the call. Clearing
the buffer and bounding the scan do not prove that every original writer obeys
that contract or writes a terminator. Callbacks must leave the current node and
captured next node valid for the remaining accesses.

The meaningful source control changes the eligibility threshold from 30 to 29.
With one need byte equal to 30 and the other seven equal to 31, the positive
source selects ordinal zero while the control has no candidates. Existing
definition row 3 supplies a concrete conditional witness: its capacity check
passes with three empty state attachment records, capacity one and empty actor
attachment slots; optional mode zero and clock hour six produce action 33,
whose first table halfword is zero. The positive writes target/action 33 and
returns one; the control returns zero. This requires the existing callback's
320-byte actor backing, beyond the core layout's 312-byte extent. It is static
source/ROM evidence, not a gameplay observation.

The native function has 256 instruction bytes, twelve referenced literal bytes
and two internal zero alignment bytes. Its 270-byte function symbol is followed
by two further zero alignment bytes before the independently called state-34
entry. Matching includes the full 272 bytes. The explicit assembly directive
only requests alignment; it contains no original instruction body.

The match uses ordinary C with independent byte counters for the two scans,
a function-scope action buffer and a sequenced local store before the count
increment. These source producers account for the retained compiler results;
they do not identify the original source spelling or historical toolchain.
Whole-ROM matching, finite static mapping and runtime behavior remain separate
claims. No inventory discovery or existing provider adds recovered-C credit.


## Connected action writers

Two ordinary C callbacks add 236 verified extent bytes through the existing
need-effect definition and consumer paths. This includes pools and alignment;
it adds no credit for existing callers, providers or inventory findings.

| Entry | Callback | Bytes | Observed definition rows | Output writes |
| --- | --- | ---: | --- | --- |
| `0x080432CC` | `frame_select_optional_attachment_kinds_432cc` | 124 | 5, 6, 7 | Bytes 0 and optionally 1 |
| `0x08016F24` | `frame_select_optional_attachment_kinds_16f24` | 112 | 104 | Bytes 0 through 3 at most |

The time-based writer selects 45 or 22 for optional modes 1 or 3. Other modes
map the current time period to 28, 32, 30 or 31. Mode 2 appends 12 only when
the signed interpretation of the parameter exceeds 10,240. Its second mode
read remains fresh after the first output write and the time-provider call.
The control changes `>` to `>=`: mode 2, parameter 10,240 and hour six produce
`[28, 0]` from a cleared buffer, versus `[28, 12]` in the control.

Row 104's writer checks the low byte of the optional-ready word result.
Readiness selects 45; otherwise a zero signed parameter selects 57. Other
parameters first write 56 and 100, then reread the parameter before appending
the pairs for `0xA00`, `0xB00` and `0xC00`. Output bytes may alias state storage,
so caching that read would change the source meaning. The first two cases
share an ordinary C append destination for their common final 101. The 57-to-58
control uses optional mode zero and parameter zero with the actual predicate
returning zero.

Rows 5, 6, 7 and 104 have enabled byte one. Their table assignments and the
existing consumers provide conditional static routes, without proving every
such state reaches a consumer or establishing gameplay use. Both callbacks
return the existing word value one. They append no terminator and leave unused
output bytes unchanged. Calls require live seven-byte output backing; the
target selectors clear their local buffers, while the embedded choice-buffer
path retains its own initialization and lifetime requirements. Existing partial
state/list/allocator owner relationships remain provisional. The signed-short
accesses and conversions use the pinned target's 16-bit representation; current
layout/API checks do not identify historical source types.

The two bodies contain 230 instruction bytes, four referenced literal bytes
and two internal zero alignment bytes. The full 236-byte extents are included
in matching. Whole-ROM equality, static routes and runtime behavior remain
separate claims. The 319,640 mapped extent bytes remain the historical
comparison baseline.

## Further action writers

Two further callbacks add 224 matching extent bytes. The former row-97 hold
at `0x08017AC4` now matches its complete 124-byte span; the row-87 writer at
`0x080220C0` matches 100 bytes. Existing consumers and inventory findings add
no recovered-C credit.

| Entry | Callback | Observed row | Behavior |
| --- | --- | ---: | --- |
| `0x08017AC4` | `frame_select_need_actions_17ac4` | 97 | Writes one code: 66, 65 or 64 |
| `0x080220C0` | `frame_select_optional_attachment_kinds_220c0` | 87 | Modes 4 through 9 write 92 through 97; other modes write nothing |

Row 97's writer selects 66 when the signed parameter is positive. Otherwise,
the existing signed-parameter return is converted to unsigned for its `> 3`
and `> 6` tests. Exact low-byte condition checks select 65 or 64. Repeated
condition and parameter calls stay fresh and short-circuit in the original
order. Its 66-to-67 control uses parameter one and calls no providers. The
row-87 writer reads its byte mode once and calls no providers; its 92-to-93
control uses mode four. Both controls change the emitted byte while retaining
the word return value one and leaving unused output bytes unchanged.

The two sources retain eight explicit address operations: the output pointer
is converted to the target's 32-bit unsigned integer, combined with the local
index by bitwise OR, then converted back. Each index is initialized to zero,
never changed and never exposed to another function. Thus the operation keeps
the same pointer bits within this pinned target's pointer/integer conversion
contract. This is implementation-specific C, with no claim that the historical
source used this spelling, that addresses contain tags, or that the operation
works for a nonzero index. The surrounding conditional, switch and provider
logic remains ordinary C. The only assembly directive requests alignment and
contains no instruction body.

Both callbacks write at most output byte zero, retain no output pointer, and
append no terminator. The consumers' live seven-byte backing and initialization
requirements still apply. The signed parameter uses the corresponding signed
16-bit view of the existing field. The existing partial state/list/allocator
relationships remain provisional; matching and target-width checks do not
prove universal effective-type compatibility or runtime state populations.

Row 87 has enabled byte one. Row 97 has enabled byte zero, so both guarded
target selectors skip its factory-installed callback. The choice-builder calls
the action callback before later enabled checks, supplying a conditional
source route. All codes emitted by these two callbacks have first action-row
halfword eight, while the current need selector compares an ordinal from zero
through seven. That selector cannot accept these codes under its current
comparison. These table and consumer facts do not establish gameplay use or
exhaust all possible callback assignments.

The complete spans contain 186 instruction bytes, 32 referenced data bytes and
six alignment bytes. The data includes the bounded six-case switch table and
its referenced pointer. Four newly owned trailing zero bytes account for the
inventory extent changing from 324,000 to 324,004 and the treemap extent from
324,008 to 324,012; the remaining two alignment bytes are internal. Existing
estimated boundaries are not reclassified as complete game-code coverage.
The 319,640 mapped extent bytes remain the fixed historical comparison baseline.


## Row-87 attachment lifecycle

The allocation, dispatch and worker path connected to row 87 adds three matching
C functions and 572 extent bytes. Existing action writers, callers and thirteen
worker providers gain no additional C credit. Names and phase roles are inferred.

| Entry | Function | Complete bytes | Role |
| --- | --- | ---: | --- |
| `0x08021E98` | `frame_step_attachment_job_87` | 508 | Parameter progress, indicator, animation and cleanup |
| `0x0802212C` | `frame_begin_attachment_job_87` | 28 | Allocate an actor record and store its full-word kind |
| `0x08022148` | `frame_dispatch_attachment_job_87` | 36 | Dispatch record kinds 92 through 97 to the worker |

The existing factory installs row 87's begin and dispatch callbacks in state
fields `+0xF0` and `+0xF4`. Allocation returns zero when all three record slots
are occupied; otherwise it stores the requested kind and returns one. Dispatch
uses the existing record finder and classifies the six actual action kinds with
a grouped switch. Other kinds return zero. As in the original, dispatch
dereferences the finder result without a null guard; a matching live record is
a caller requirement. Other small callbacks in the row remain explicit original
regions.

A record whose running byte is exactly one enters phase one. Phase zero either
starts a low-need animation and waits in phase eight, or initializes parameter
progress and waits in phase 72. The parameter branch creates and updates an
indicator when the current signed value differs from ten. It adjusts the actor's
needs using the definition row's amount byte and advances when the value reaches
the next step or ten. The completed-value branch instead decrements the actor
timer until minus one. Phase eight observes the animation-completion flag and
clears the need countdown. Phase one requests the idle animation, transitions
and clears any indicator, and returns two; other paths return one.

The source copies the actor's need pointer and integer timer from the existing
canonical object's character storage at `+0x60` and `+0x58`. It copies the
indicator pointer through four bytes of the state's existing seven-byte field
at `+0x58`. These accesses stay within their declared character arrays and
require initialized, valid target representations. They introduce no foreign
actor or state word overlay. The bounded shared-world declaration represents
the observed mode byte at offset `0x20` and six parameter words at `0x98`,
with target extent `0xB0`; it supplies no original data initializer. Its wider
owner and effective-type relationship with other global views remains
provisional. Existing record-owner casts and provider views retain their
previous compatibility requirements.

Every parameter-table access requires the current optional byte to be four
through nine, including after opaque provider calls. The factory initializes
that byte to zero, so factory allocation alone does not establish this domain.
The existing spawn interface can install the required modes, and the row-87
writer emits the corresponding kinds 92 through 97. These are conditional
source routes: their action-row halfword eight still cannot match the current
need selector's ordinal zero through seven. They establish neither gameplay
use nor all runtime assignments. Calls also require valid actor/need/indicator
objects, a backed definition row, direction-table indices zero through seven,
and a timer decrement that does not overflow. The captured need storage must
remain live across provider calls, even if the job's actor field changes. Fresh
optional, kind and provider reads remain after calls; no unsupported caching is
introduced.

The three meaningful controls change cleanup return two to three, the allocated
kind to kind plus one, and dispatch case 92 to case 91. Respectively, a valid
cleanup phase with no indicator changes the return value; a free record stores
a different kind; and a kind-92 cleanup record changes from worker return two
to default zero. All retain the surrounding provider and lifetime requirements.

The complete spans contain 536 instruction bytes, 28 referenced literal bytes
and eight zero alignment bytes. Four alignment bytes are internal to the worker;
two follow its 506-byte function symbol and two follow the begin callback's
26-byte symbol. Independently rooted next entries bound those trailing bytes.
The dispatch symbol itself is 36 bytes. Alignment directives contain no
instruction body, and all spans, pools and alignment are included in matching.
The source-level switch and direct representation copy account for the retained
compiler differences without identifying historical source spelling. Matching,
static mapping and runtime behavior remain separate claims.


## Fixed-parameter kind-72 lifecycle

The related path installed by observed definition rows 16 and 17 adds three
matching C functions and 528 extent bytes. It shares the existing mode and
parameter world with row 87, but reads parameter index five directly. Its names
and phase roles remain provisional.

| Entry | Function | Complete bytes |
| --- | --- | ---: |
| `0x08029A38` | `frame_step_attachment_job_72` | 424 |
| `0x08029C1C` | `frame_begin_attachment_job_72` | 72 |
| `0x08029C64` | `frame_dispatch_attachment_job_72` | 32 |

The begin callback allocates a record, stores the requested full-word kind,
obtains attachment point zero from the owner's object, starts route mode three
with style one through the record's status word, and requests animation six.
It returns zero on record-allocation failure and one otherwise. The attachment
provider must succeed and initialize both point coordinates; its byte return is
ignored. The route copies the local point during the call but retains the record's
status pointer for an active route, so the record and status must remain live.
The route-creation failure return is also ignored, as in the original; the source
adds no guard or fabricated point initialization. Dispatch requires an existing
matching record and calls the worker only for
kind 72; other kinds return zero. The source preserves the unchecked finder
dereference. The same legacy record-owner and provider compatibility limits
continue to apply.

Running byte one forces cleanup phase one. Phase zero either begins the
low-need animation and enters phase eight, or prepares an indicator and animation
seven before entering phase three. Both phase-zero branches initialize the
actor timer to 150. In phase three, a parameter value other than ten updates
the indicator and parameter and completes only when a fresh signed read equals
the captured value plus one. When the captured value is ten, it instead applies
need-adjustment row 47 using the definition's amount byte, then decrements the
actor timer and completes at zero. Phase eight waits on the completion flag
and clears the countdown; cleanup requests animation one, transitions and clears
the indicator, and returns two. Other paths return one.

The sources reuse the published bounded shared-world type and canonical
character-representation copies for the needs pointer, actor timer and state
indicator. They introduce no duplicate world alias or actor/state overlay.
Valid representations, backed actor/need/indicator objects, direction indices
zero through seven, a backed definition row and compatible provider lifetimes
remain required. Captured need storage must stay live across calls. Timer
decrement must not receive the minimum signed integer. The fixed index-five
access requires the six-word parameter backing, but this worker has no
optional-four-through-nine indexing requirement. Wider world ownership and
effective-type compatibility remain provisional.

Both observed rows have enabled byte zero, so the guarded target selectors
skip their factory-installed callbacks. The original eight-byte action writer
emits kind 72, and the choice-builder supplies a conditional callback route;
these facts do not prove gameplay use or all writable assignments. The sixty
bytes between the worker and begin entry remain explicit original regions:
three small callbacks, plus an independent attachment predicate and its two
alignment bytes. None is a direct callee of the three new bodies, and none
gains C credit. All seventeen reused providers already have matching sources.

The controls change cleanup return two to three, the allocated kind to kind
plus one, and dispatch case 72 to case 73. A valid cleanup record with no
indicator distinguishes the first return; a free record with a successful point
provider and valid route/status lifetime distinguishes the stored kind; and a
kind-72 cleanup record distinguishes worker return two
from default zero. These are source-domain witnesses, not runtime observations.

The complete spans contain 504 instruction bytes, twenty referenced literal
bytes and four internal zero alignment bytes. There are no trailing alignment
bytes or added assembly directives. The existing extents gain compiler ownership
without increasing mapped extents. Matching, static routes and runtime behavior
remain separate claims; the fixed historical comparison is 319,640 mapped
extent bytes.


## Row-3 attachment jobs 12, 31, 33 and 45

The four connected bodies add 932 matching C extent bytes through the existing
row-3 dispatcher. Existing callers, action writers and seventeen accepted
providers gain no additional C credit. Names and phase roles remain inferred.

| Entry | Function | Complete bytes |
| --- | --- | ---: |
| `0x08035A04` | `frame_step_attachment_jobs_31_33` | 524 |
| `0x080358B0` | `frame_step_attachment_job_12_358b0` | 156 |
| `0x0803594C` | `frame_step_attachment_job_45_3594c` | 184 |
| `0x08035CE8` | `frame_dispatch_attachment_jobs_12_31_33_45` | 68 |

Observed definition row 3 has enabled byte one and installs the dispatcher at
state `+0xF4`. Its accepted action writer can emit 31, 33, 45 and an optional
12. Dispatch looks up the actor's existing record and selects the corresponding
worker; other kinds return zero. The finder result is dereferenced without a
null guard, so a matching live record remains a caller requirement. The row's
eight-byte intermediate callback, 72-byte begin callback and intervening
44-byte region remain original. These finite assignments provide a conditional
source route, not proof of gameplay use or all writable callback populations.

The kinds-31/33 worker captures the actor's need pointer before initializing
its default word result. Phase zero reverses direction, checks the existing
condition and chooses optional-effect work or a waiting animation. Phase six
commits the first need-effect stage and sets the object's byte flag. Phase 24
waits on the completion flag, commits stage three, starts animation 23 and
stores two sample handles before initializing the actor's countdown to 60.
Phase 26 adjusts need row eight, then tests the fresh running byte. Exactly one
short-circuits the decrement; otherwise the unsigned 16-bit countdown wraps
from zero to `0xFFFF`, which advances to phase nine. That phase commits stage
two, stops both stored samples, plays the completion cue and changes direction.
Phase one requests animation one, updates the existing resource triple and
returns two; other phases return one. There is no global running-byte clamp.

The kind-12 worker forces phase one only when running is exactly one. Its
start phase uses animation 14 and one stored sample; phase four adjusts need
row 52 and tests only the low byte of the optional-two consumer's word result.
The kind-45 worker instead forces cleanup for any nonzero running byte. It
reverses direction before the actor-effect test and uses animation 46 when an
indicator is needed. A successful optional consumer stores phase one before
the opaque resource update. The subsequent phase read remains fresh, so a
provider change is not hidden by a cached phase. Cleanup stops the stored
sample, requests animation one, transitions and clears a nonnull indicator,
and returns two. Other paths return one.

The first sample's four-byte representation at `+0xE0` is accessed through
`DisplayNeedEffectStateView.unknown_dd[3..6]`, within the existing allocator's
256-byte access view. The shorter `FrameNeedEffectState` declaration
does not reach that field and is not used as its storage extent. The second
sample at `+0x64` uses four bytes inside the partial state's thirteen-byte
`unknown_63` member. The indicator at `+0x58` similarly uses four bytes of its
existing seven-byte character member. Copies require initialized valid target
representations and the backing extent appropriate to the existing allocation.
Reuse of the allocator/state views does not prove universal effective-type
compatibility among legacy views.

The actor's needs pointer is copied through the canonical motion character
array at `+0x60`, and the countdown uses the existing unsigned-halfword member
at `+0x5E`. The byte flag at `+0x4F` is within the same canonical motion storage.
No actor/state word overlay or shared-header layout change is introduced.
Captured need storage must remain live across calls. Actor, state, record,
indicator, sample, definition, condition, resource and input backing must meet
the existing provider contracts; direction-table indices must be zero through
seven. Fresh state, kind and provider reads remain where they follow opaque
calls. This path establishes no universal optional-mode or global-index domain.

The three worker controls change completion return two to three. A valid
cleanup record and initialized sample/provider backing distinguish each return;
the kind-45 witness uses a null indicator. The dispatcher control changes case
31 to 30: a live kind-31 cleanup record returns two in the positive and zero
in the control. These are defined source-domain witnesses, not runtime tests.

The complete spans contain 780 instruction bytes, 144 referenced literal or
switch-table bytes and eight internal zero alignment bytes. All four function
symbols cover their full spans. The ordinary source switch produces the bounded
27-entry table; no instruction body or table payload is embedded in the source.
The explicit initialization phase explains the retained six-byte entry-order
failure without identifying historical source spelling. Row 97's larger
workers and the renderer remain original; their held candidates gain no credit.
Matching builds, static routes and runtime behavior remain separate claims.
