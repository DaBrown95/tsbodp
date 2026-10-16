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
null guard, so a matching live record remains a caller requirement. The four-body milestone left the row's
eight-byte intermediate callback, 72-byte begin callback and intervening
44-byte region original. The begin callback is covered by the follow-up below;
the eight-byte callback and 44-byte region remain original. These finite assignments provide a conditional
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
failure without identifying historical source spelling. At that four-body milestone, row 97's larger workers and the renderer remained
original. The later kind-64/65 path below covers its primary worker; kind 66 and
the renderer remain original.
Matching builds, static routes and runtime behavior remain separate claims.


## Row-3 allocation and route handoff

`frame_begin_attachment_jobs_12_31_33_45` adds the complete 72-byte callback
at `0x08035CA0`. This connects row 3's existing begin slot to the four published
dispatch/step bodies. It adds no credit for those 932 bytes or for its four
already matching providers. The row's eight-byte intermediate callback and
44-byte neighboring region remain explicit original code.

The callback allocates one of the owner's three actor records. Failure returns
zero. Success stores the supplied full-word kind, reads attachment point zero
from the owner's object, starts route mode zero with style one through the
record's status word, requests animation six, and returns one. The route mode
is zero here; the related kind-72 callback uses three. No kind filter or new
validation branch is added. The source uses the same canonical owner/record
interfaces and existing provider declarations.

The attachment provider's return is ignored. Whenever a free route slot reads
the destination, that provider must have initialized both signed point
coordinates within its resource and arithmetic domain. The route copies the
local point during the call and retains the record's status pointer. Record,
status and actor storage must therefore remain live until the route completes
or is cancelled. Route-allocation failure is also ignored; the callback still
requests animation six and returns one. These are preserved caller contracts,
not successful-route guarantees. Legacy allocator, command and tick-object
view compatibility remains provisional.

The control adds one to the stored kind. With a free record, kind 31 and valid
point/provider/route backing, the sources store 31 and 32 respectively while
both return one. A full owner would not reach the changed store and is not the
witness. Row 3's enabled definition and existing actor-state callback use give
a conditional allocation-to-step route; no gameplay observation or exhaustive
callback-population claim follows. The entire function is 72 instruction bytes,
with no referenced pool or alignment bytes.


## Parameter jobs 64 and 65, and activity jobs 88 and 89

Seven connected bodies add 2,160 C extent bytes. The kind-64/65 primary worker,
its begin callback and dispatcher contribute 1,008 bytes. The two kind-88/89
workers and their begin/dispatcher pair contribute 1,152 bytes. Existing action
writers, capacity checks, routing services and shared providers add no further
credit. The renderer and kind-66 worker remain explicit original code.

| Body | ROM start | Complete matching extent |
| --- | --- | ---: |
| Begin kinds 64–66 | `08017FDC` | 72 |
| Step kinds 64/65 | `08017B40` | 884 |
| Dispatch kinds 64–66 | `08018024` | 52 |
| Step kind 88 | `080470C0` | 520 |
| Step kind 89 | `080472C8` | 516 |
| Begin kinds 88/89 | `0804750C` | 72 |
| Dispatch kinds 88/89 | `08047554` | 44 |

The parameter worker uses fixed index two in the existing six-word world
parameter view. The signed parameter provider reads the high byte of a word
and returns an `int` in the range -128 through 127; it is not a signed-halfword
reader. Converting that result to unsigned for the `<= 9` check deliberately
excludes negative values. A fresh read after the update is compared with the
captured prior value plus one. The already-ten branch instead waits for the
actor's unsigned-halfword countdown to wrap to `FFFF`. Kind 64 commits mode one
and stores `2800` in the owner's parameter; kind 65 commits mode three and stores
`5000`. Current percentage and signed-parameter APIs remain unchanged.

The actor's countdown is the real canonical member at `+0x5E`; the needs pointer
is copied from the canonical motion character storage at `+0x60`. Indicator
pointers at state `+0x58` use bounded four-byte representation copies. One shared
percentage local and one shared post-update value retain the real value phases
across mutually exclusive states; direct assignments retain the actual timer
write position. There are no fixed-register constraints or instruction bodies.
Captured needs, indicators, actors, records, direction indices and provider
backing must remain valid and live across the corresponding calls.

The parameter dispatcher calls this worker for kinds 64 and 65. Its kind-66
branch still calls the original `08017EB4` service, whose provisional word
contract and fresh signed-halfword owner-parameter tests are not changed here.
Neither a failed candidate nor a function declaration earns C credit. Definition
row 97 has enabled byte zero: the guarded need/action selectors skip that
unchanged factory row. Its recorded callbacks establish a conditional source
connection, not gameplay use or universal writable-callback reachability.

Enabled definition row nine emits choices 88 and 89 in its original two-byte
writer and records the new begin and dispatcher addresses. The worker families
share the existing amount-ten gate and optional-state providers. On success
phase zero requests animation 58 and cue 170; failure requests animation five,
selects cue 86 or 85 from the live attachment mode, and waits in phase eight.
Phase six waits for the actor flag, commits mode one, plays cue 171 and stores
countdown 30. After wrap, kind 88 requests animation 21, records sample cue 21
and enters phase 27; kind 89 uses animation 23, sample cue 20 and phase 26.
Their adjustment kinds are 40 and eight respectively, with the definition's
fresh multiplier byte. The sample is stopped at the observed completion stages;
the cleanup phase commits mode zero, requests animation one and returns two.

Each activity worker captures the needs pointer before initializing its result.
Its sample at `+0xE0` is copied through bytes three through six of `unknown_dd`
in the existing 256-byte access view. This is within that view's extent; it does
not extend the smaller partial state type or prove universal effective-type
compatibility of legacy views. Both worker spans contain 372 instruction bytes;
they contain 136 and 132 referenced bytes and twelve zero alignment bytes each.
The function symbols cover 518 and 514 bytes, while their linked sections cover
520 and 516. The EOF directive requests zero section alignment, with no padding
object, original table payload or instruction body embedded in source.

Both begin callbacks allocate a real three-record slot, store the supplied word
kind, read attachment point zero and request animation six. Their route modes
are zero for kinds 64–66 and three for kinds 88/89, both with style one. Point
and route returns remain ignored: both coordinates must be defined whenever a
route copies them, and actor/record/status storage must survive the retained
status pointer through completion or cancellation. A route allocation failure
still leaves the callback returning one. Dispatcher finder results must be live
records. Existing allocator, command, tick, state and world-view compatibility
remains conditional rather than a universal aliasing proof.

The seven controls change each worker's completion result or countdown, each
begin's stored kind, and each dispatcher's selected kind. Defined witnesses use
live cleanup records, or a phase-six actor with its completion flag, or a free
record and valid point/route backing. A full owner cannot witness the changed
begin store. These distinguish return/status or stored state without claiming a
runtime observation. The independent row-nine callbacks are now source-owned
as described below; the kind-66 worker remains original. Existing capacity
checks and the remaining renderer/finalizer work gain no credit.

The only changed existing shared header is a conventional include guard around
`frame.h`. Its original body, fields and APIs are byte-for-byte unchanged. It
prevents duplicate type definitions when the real resource-entry and attachment
include paths meet. It neither hides a type view nor adds an ABI or C-coverage
claim. Matching, layout/API checks, static callback routes and observed runtime
behavior remain separate forms of evidence.

## Row-nine callback closure

Four further C bodies account for 60 complete extent bytes: the constant-return
callback at `080474CC` (4), the separate attachment predicate at `080474D0` (40),
the choice writer at `080474F8` (12), and the empty finish callback at `08047580`
(4). All four match their fixed extents and reject function-specific changed
source controls. The predicate and finish source request only zero section
alignment; neither contains executable assembly.

Definition row nine stores the first callback, choice writer and finish callback
at offsets zero, four and twenty. Its enabled byte remains one. The allocator
copies the choice and finish addresses into the existing state callback slots
at `E8` and `F8`. The first callback returns one, although the visible factory
caller ignores that return. The finish callback performs no operation. The
choice writer stores exactly two bytes, 88 and 89, and returns one.

The separate predicate returns zero when the actor has attachments and state
byte `+60` is one; otherwise it returns one. Its existing attachment-count API
returns a byte. No aligned ROM pointer to this predicate was found in the
bounded whole-ROM word scan, so its compiler match does not establish a live
callback route. Actor attachment storage, state backing and a choice buffer of
at least two bytes remain caller requirements. These are static and compiler
findings, with no new runtime observation.

The four controls change the first callback's return to zero, the predicate's
state comparison to two, the second selected kind to 88, and the empty finish
callback to store optional value one. Live state, an actor with one attachment,
and a two-byte output buffer provide defined witnesses for those respective
changes. The intermediate callback at `08047504` now has the matching constant-
result switch source explained below. The earlier plain-return and artificial-
call hypotheses are not accepted recipes.

The prepared kind-66 byte-local result experiment has now been executed against
current headers. It produces the same 244 bytes and 115 differences as the
word-local candidate. Both omit the original right shift after low-byte
extraction before the zero test. That result closes this local-width hypothesis;
the fixed 248-byte worker remains original. Current renderer and finalizer
candidates also remain outside matching-C totals.

## Row-97 initialization, finish and percentage

Four further ordinary-C bodies own 160 complete extent bytes: the factory
initializer at `08017A68` (92), the separate attachment predicate at `08017FAC`
(40), the finish callback at `08018058` (4), and percentage at `0801805C` (24).
They reuse the existing state, attachment and need-effect object declarations.
All four complete extents
match and reject meaningful changed-source controls; the existing begin,
primary worker and dispatcher remain exact with their own rejected controls.

The initializer reads the signed interpretation of the owner's parameter.
`0x5000` selects requested animation mode three and `0x2800` selects one. Other
values select zero and clear the parameter and optional byte. It writes the
existing `FrameNeedEffectObject.requested_animation` member at object `+103`,
which the published need-effect updater subsequently supplies to
`frame_commit_need_effect`. The initializer returns one. Definition row 97
stores this callback at offset zero; the spawning path supplies the object's
state and optional saved parameter before invoking it. This is a conditional
static route, without a gameplay observation or complete callback-domain claim.

The finish callback is row 97's offset-twenty entry, copied by the allocator
to state `+F8`, and performs no operation. Its four-byte extent contains the
two-byte return and two zero alignment bytes. The independent predicate returns
zero only when the byte attachment count is nonzero and state byte `+60` equals
one. No aligned full-ROM word pointer to this predicate was found; that bounded
scan does not establish unreachability. Its source preserves the state read
after the provider call and requires compatible live owner, actor and attachment
backing. The existing partial-view compatibility limits remain unchanged.

The controls change initializer mode three to two, predicate comparison one
to two, and the empty finish body to store optional value one. Defined witnesses
use parameter `0x5000`, a nonzero attachment count with state byte one, and a live
owner respectively. The first two controls retain their extents; the finish
control grows from four to eight bytes and is rejected in full. The three
positive initialization/predicate/finish spans contain 120 instruction bytes,
twelve referenced literal bytes
and four zero alignment bytes. Alignment directives contain no instructions.

The percentage callback returns byte value 100, or 50 when the signed 16-bit
parameter at state `+70` is zero. The allocator copies definition row 97's
offset-24 pointer to state `+FC`. The already-owned optional-percentage callback
at `0802F30C` supplied the same concrete type/dataflow recipe. A live state with
parameter one witnesses the compiling 100-to-99 control; it rejects by one byte.
The full 24-byte extent contains 22 instruction bytes and two zero alignment
bytes. No generic FC consumer or unique historical typedef is established.

The LR-only leaf prologue follows the pinned compiler's cached far-jump
predicate, rather than an invented call. Its complete RTL has no call and uses
only R0-R2. A diagnostic changing only `-fprologue-bugfix` removes the LR save
and changes 24 bytes to 20; the accepted standard profile remains unchanged.
This explains this conditional leaf's frame without justifying assembly for
the separate constant-return callback. Ordinary inline deferral does not leak
this cache: it exits before reload, and emitted functions reset the flag.

The kind-66 worker remains an unconverted 248-byte body. All five direct
providers already have matching source. A separate bounded test changed only
the private `actor_entry_add` call declaration to a byte return. Its initial
compiler output used a byte-valued call result, but the combine pass still
removed the right shift before the zero test. The final 244-byte candidate
was byte-identical to the existing word-return candidate and retained the same
115 differences. This disproves that return-ABI explanation; no public API was
changed. The eight-byte intermediate callback at `08017FD4` now has the
selector-backed constant-result switch source explained below. Row 97's
enabled byte remains zero, and finite table ownership does not close writable
callbacks or runtime reachability.

## Row-100 installed callbacks

Three further ordinary-C callbacks complete 16 extent bytes around the already
owned kind-71 worker, begin and dispatcher: initialization at `08034F7C` (4),
selection at `08034FA8` (8), and the empty callback at `08035020` (4). Definition
row 100 at `0x63C8C` supplies their pointers at offsets zero, four and twenty.
The allocator copies the latter two into state `+E8` and `+F8`.

Initialization returns one; the factory ignores that result. Selection writes
kind 71 to the first output byte and returns one, without clearing the tail.
Its typed consumer calls E8 before its later enabled check, so the disabled
definition byte does not by itself exclude that route. The descriptive finish
name follows the existing family; the actual F8 consumer invokes it as a
nullable void tick callback. Historical unused argument counts are not uniquely
established by these constant or empty bodies.

All three full extents match with the existing profile. Returning zero,
selecting 70, or adding an optional-byte store each compiles and rejects; the
last control grows from four to eight bytes. The positives contain 14
instruction bytes and two zero alignment bytes. An actual-definition API unit
checks the existing E8/F8 signatures, and an incompatible callback type rejects.
The separate unrooted predicate at `08034F80` and word-returning constant-100
entry at `08035024` now own another 44 C bytes with rejected controls, reusing
the existing sibling predicate recipe. Neither has an established installed
table-callback role; the latter is separate from the empty body's alignment.
The EC callback at `08034FB0` now has the matching source described below. See the
[kind-71 boundary notes](FRAME_ATTACHMENT_JOB_71.md). No runtime selection or
complete callback-domain claim follows from this finite table/source evidence.


## Row 104 control and status path

Nine connected C definitions now own 1,336 extent bytes. The initializer at
`0x080172FC` (28 bytes) conditionally refreshes audio. The begin callback at
`0x08017348` (84) allocates an attachment record, stores its kind, obtains the
attachment point and starts the actor route. The F8 callback at `0x0801739C`
(4) is empty. Refresh at `0x080174A8` (84) independently reads the parameter
around sequence calls: `0xA00`, `0xB00` and `0xC00` select sequences 21, 7 and
22, then the existing audio flag field receives bit eight.

The 400-byte dispatcher at `0x08016F94` is definition row 104's `+16` pointer,
copied to state `+0xF4` and called by the accepted status consumer. Its guarded
57-slot local switch selects four C workers: job 45 at `0x08017124` (164), job
100 at `0x080171C8` (308), modes for jobs 56/57 at `0x080173A0` (136), and
modes for jobs 98/99/101 at `0x08017428` (128). All their direct providers now
have source ownership. Job 45 preserves cancellation for any nonzero running
word. Job 100 retains its need-state pointer while rereading actor/work fields
across provider calls; its timer and sample cadence use the native 150 and
32-tick conditions. The mode workers update the parameter before animation
completion, with the original distinct refresh/commit behavior.

The nine extents comprise 1,062 instruction bytes, 252 referenced literal or
switch bytes and 22 zero-alignment bytes. Source controls reject for every
body. The dispatcher's control changes mode one to zero, which changes the
connected parameter write. An earlier one-to-two mutation is semantically
equivalent in this worker and supplies no control evidence. All actual new
definitions pass the canonical API and target-layout checks; assigning the
two-argument worker to the three-argument mode API rejects.

The common header reuses existing object, record and audio declarations;
no qualifier or layout change supplies the match. The FC slot is null. The
separate, unrooted predicate at `0x08017318` now owns 40 matching C bytes with
a rejected control; no pointer or current direct caller establishes its use.
The installed LR-saving callback at `0x08017340` now has matching C ownership
under the late-collapse explanation below. Twelve source bodies continuously
cover `0x08016F24..0x080174FC` (1,496 bytes), including the separate predicate. Matching these nine bodies therefore does not close the
entire row, its runtime population, callback writers, allocation or object
lifetime domains. Row 104 execution has not been observed.


## Shared rows 42 and 43

Twelve readable C bodies cover the contiguous 1,596 bytes at
`0x08041610..0x08041C4C`. Eleven own the two observed definitions' six non-null
callbacks and the status dispatcher's five direct providers (1,556 bytes).
The separate 40-byte predicate at `0x08041960` has no identified incoming
pointer or direct call. It receives source ownership without an installed-slot
or runtime claim. The existing capacity predicate gains no additional credit;
the FC slots are null.

The dispatcher at `0x08041610` (388 bytes) selects the job-45 worker at
`0x08041794` (172), job 18 at `0x08041840` (260), modes for jobs 56/57 at
`0x08041B1C` (132), modes for jobs 2/5 at `0x08041BA0` (120), and audio refresh
at `0x08041C18` (52). These preserve the actual direction reversal, distinct
need/animation paths and parameter-controlled sequence choices. Shared callback
entries are initializer `0x08041944` (28), action writer `0x08041988` (72), EC
check `0x080419D0` (256), begin `0x08041AD0` (72) and empty F8 tick
`0x08041B18` (4).

The EC check reads the third word and guards a 56-entry jump table; every
entry and the default reach a constant-one return. An ordinary switch over
the action writer's six evidenced kinds (2, 5, 18, 45, 56 and 57) reproduces
this complete compiler-generated table. Returning zero for case two is a real
control and rejects. No table bytes or instruction bodies are embedded in C.
This gives a positive source producer for this constant-result function; it
does not explain the separate eight-byte LR-saving leaf family. Its generic
consumer and unused first-two argument roles remain unidentified.

All twelve first source recipes match, and every meaningful control rejects.
Their extents comprise 1,086 instruction bytes, 488 literal/switch bytes and
22 zero-alignment bytes. Actual definitions pass canonical API and target-layout
checks; incompatible callback assignments reject. These are finite static and
compiler results. Writable targets, runtime row/index populations, object
lifetimes, allocation and gameplay domains remain open.


## Constant-result EC switches and the retained LR save

Forty-one observed-prefix eight-byte EC entries now have matching C
definitions, using each recovered writer and status dispatcher's complete
evidenced action set:

| Definition row | EC entry | Action cases |
| --- | --- | --- |
| 9 | `0x08047504` | 88, 89 |
| 87 | `0x08022124` | 92 through 97 |
| 97 | `0x08017FD4` | 64, 65, 66 |
| 98 | `0x08048640` | 25 |
| 99 | `0x0801DDC4` | 42, 94 |
| 100 | `0x08034FB0` | 71 |
| 104 | `0x08017340` | 45, 56, 57, 98, 99, 100, 101 |
| 1 | `0x08018450` | 29, 45 |
| 11, 12 | `0x0801A3B4` | 12, 23, 60 |
| 44, 45, 49 | `0x080449B0` | 1, 6, 45, 56, 57, 62 |
| 51, 52, 53, 54, 55, 84 | `0x0800CCF8` | 27, 50 |
| 59, 60, 61, 62, 80, 81, 82 | `0x08035830` | 49 |
| 69, 71, 73, 91, 111 | `0x0803AC48` | 45, 61 |
| 79, 86 | `0x08021E24` | 49 |
| 90, 109, 110 | `0x0803A9CC` | 12, 45, 53 |
| 92, 114, 115 | `0x08046238` | 12, 45, 59 |
| 132 | `0x08016568` | 7, 44, 45 |
| 3, 4 | `0x08035C98` | 12, 31, 33, 45 |
| 63, 64, 65, 66, 67, 75 | `0x08013270` | 49, 50 |
| 0 | `0x0800BCEC` | 13, 14 |
| 141 | `0x08036C7C` | 7, 45 |
| 31 | `0x08037814` | 7, 91 |
| 37, 38 | `0x08012DC4` | 79, 80 |
| 89 | `0x08022364` | 45, 90 |
| 18, 20 through 30, 32 through 34, 83, 101, 136, 137 | `0x08016910` | 7 |
| 13 | `0x08016304` | 24 |
| 14, 15, 19 | `0x0801E558` | 60, 63 |
| 16, 17 | `0x08029C14` | 72 |
| 35, 36 | `0x0803D3CC` | 73 |
| 39 | `0x080276C0` | 46 |
| 40 | `0x080338C8` | 43 |
| 50 | `0x0802A9B4` | 87 |
| 56, 58 | `0x08016DB4` | 49 |
| 57 | `0x0800F6E0` | 49 |
| 102 | `0x080468D4` | 48 |
| 88 | `0x080221A4` | 26 |
| 135 | `0x08034D18` | 12 |
| 74 | `0x080179F8` | 8, 9, 10, 11 |
| 131 | `0x08023C20` | 3, 4, 18 |
| 96 | `0x08016770` | 18 |
| 133 | `0x0802BC48` | 16, 17 |

Each source switch returns word one for its cases and default. The original
256-byte EC switch in rows 42/43 independently corroborates this family idiom;
its native third-word guard and all-one table remain in the final code. The
smaller functions retain their actual comparisons through global
allocation/reload. Argument-pointer elimination classifies the not-yet-shortened
conditional branches as possible far jumps and caches that fact. The later
`jump2` cross-jumping pass merges identical return blocks and removes every
comparison. The cached flag still makes the backend save LR, leaving exactly
`PUSH LR; MOV R0,1; POP R1; BX R1`.

One counterfactual compiles the unchanged row-9 source with only the existing
prologue-bugfix flag added: eight bytes become four. All captured headers and
preprocessed input remain identical. This supports the within-function cache
explanation; it is a diagnostic, not an accepted alternate recipe. The earlier
plain-constant and cross-function inline-cache explanations remain disproved.

One additional same-body EC at `0x08016E34` belongs to the unrooted action-75
module outside this observed prefix. Its writer and status independently ground
case 75; it adds no entry to the 48-prefix count.

All forty-two complete-set recipes match on their first attempt, without
instruction assembly, register constraints, added qualifiers or invented calls.
Real controls make one evidenced case return zero: thirty-four compile to 16
bytes and reject by 14; the kind-90 control compiles to 20 and rejects by 18;
seven compile to 24 and reject by 22. The stable verifier
includes extra bytes in rejection. Canonical API, full-ROM/control and progress
gates pass. Together these leaves own 336 C instruction bytes (328 in the
observed prefix) and no assembly, pools or alignment.

For rows 3/4 and the shared header writer, zero is an evidenced buffer sentinel,
so the action cases are respectively 12/31/33/45 and 49/50. Zero remains in the
complete write-value evidence and takes the source's constant-one default.
Unwritten tails and forwarded selection indices remain separate open domains.

Removed case structure and unused first-two formal roles are inferred from the
family and its recovered writers, not uniquely identified historical source.
The source still returns one for every word input. Generic EC delivery, writable
callback targets, valid selection indices and retained-tail domains remain open.
After these forty-one, seven same-body entries in the observed 149-row prefix
still need justified source recipes. Five have unconverted output-writing E8
paths (including a zero-only writer whose delivery is unresolved). Both
no-write selectors at `0x0803505C` and `0x0801335C` now have source but supply
no grounded cases for their EC entries. No speculative recipes were tried.
Byte equality alone does not authorize an arbitrary case list.


## Definition row zero: attachment actions 13/14

Nine ordinary C bodies own the complete interval `0x0800BA60..0x0800BD68`
(776 bytes: 524 instructions, 244 literal/switch bytes and eight zero-alignment
bytes). Installed callbacks own 136 bytes and their connected worker 596.
The separate 40-byte actor-check and four-byte constant-100 leaf have no
established incoming edge; neither is an installed row-zero callback. Its FC
word is null. The copied sorter at `0xB840` remains outside this module.

The writer stores actions 13 and 14 without a terminator or tail initialization;
status accepts those actions. The worker preserves cancellation only when
`running == 1`, captured needs, the complete 55-entry unsigned timer switch,
halfword countdown wrap, route/animation/audio order and definition byte 35.
All seven direct providers already have matching source. Every body has a
rejecting changed-source control, including finish's real kind-zero to kind-one
edit; an earlier write-zero diagnostic is excluded as inconclusive. Actual
definitions and 17 target-layout facts pass API checks, while a wrong callback
assignment rejects. Runtime use, index bounds and callback populations remain
open.


## Further connected attachment modules

| Observed rows | Complete local C interval | Functions / extent bytes |
| --- | --- | ---: |
| 31 | `0x08037584..0x080378B0` | 10 / 812 |
| 37, 38 | `0x08012BD0..0x08012E74` | 9 / 676 |
| 89 | `0x0802224C..0x080223C0` | 8 / 372 |
| Shared job 7, 19 rows listed above | `0x080167B8..0x08016978` | 9 / 448, including 380 already owned |

Each interval includes a separate adjacent actor-check whose incoming edge is
unestablished. The rows 37/38 and shared-job-7 constant-100 neighbors are also
separate unrooted entries. Row 31 instead installs its 24-byte FC callback,
returning 50 for a zero signed parameter and 100 otherwise. These roles come
from the actual table pointers; adjacency does not establish a callback role.

Row 31's selector writes 7 for signed owner parameter `0x6400`, otherwise 91.
Its two workers preserve halfword timer `+0x5E` and unsigned comparisons on the
signed parameter reader's result. Rows 37/38 write 79 and conditionally 80.
Their worker's first source kept the indicator pointer live across a nested
percentage call. Reading the actual percentage first and loading the indicator
afterward restored native order and reduced 440 bytes to the exact 420. A shared
status result also preserves two native worker call sites that the initial
direct-return form merged in `jump2`; no extra operations were added.

Row 89 writes sentinel zero or action 90 after the condition-3 test. Its status
also explicitly sends action 45 to the same worker, independently grounding the
EC cases 45/90 before the trial. The worker treats the signed-byte provider's
result as unsigned for the native greater-than-two completion test. Begin's
single result join restores native block order. Status has a separate confirmed
type cause: this compiler applies ASCII case costs to an integer switch over
0/45/90, choosing pivot 90. An enum expression disables those costs and selects
native pivot 45. A local unsigned 32-bit enum view reproduces all 52 bytes;
the shared record remains a word. Target checks verify width, unsignedness and
round trips for 256, `0x80000000` and `0xFFFFFFFF`, preserving the default for
all unnamed words. Case-order changes were disproved before this type trial.
The enum spelling is supported matching source, not uniquely historical naming.

The shared job-7 writer stores only seven and retains the tail. Six new bodies
own 68 bytes; its existing worker, begin and status were reverified with controls
under the appended declarations and receive no duplicate credit. Across these
modules all actual definitions and target layouts pass API checks, all real
source controls reject, and full-ROM/control and progress gates pass. No added
assembly instructions, register constraints, qualifiers or invented calls supply
the matches. Unique failed sources and useful compiler evidence remain local.
Live backing, provider success, selection indices, complete EC delivery,
writable callback populations and gameplay remain separate open domains.


## Attachment actions 24, 60/63 and 72

| Observed rows | Complete local C interval | Functions / extent bytes |
| --- | --- | ---: |
| 13 | `0x080161CC..0x08016398` | 8 / 460 |
| 14, 15, 19 | `0x0801E270..0x0801E5F4` | 10 / 900 |
| 16, 17 | `0x08029A38..0x08029C8C` | 9 / 596, including 528 already owned |

These modules add 24 definitions / 1,428 C extent bytes: 1,370 instructions,
32 pool bytes and 26 genuine zero-alignment bytes. All source controls reject,
actual definitions and target layouts pass API checks, and full-ROM/control and
progress gates pass. The existing kind-72 worker/begin/status also reverify under
the appended declarations and receive no duplicate credit. The count predicates
and kind-72 constant-100 neighbor remain explicitly unrooted; installed callback
roles come from table words, not adjacency.

Row 13 writes only action 24. Its worker preserves captured needs, the full-word
running-equals-one cancellation, clock 150, cue 41 and commit modes 3/2. The next
already-owned condition worker at `0x08016398` is excluded from the new extent.
Rows 16/17 write only 72; their lifecycle behavior above is unchanged.

Rows 14/15/19 write 60 then 63 and dispatch them to distinct workers. Their F8
callback is a real 132-byte tick, and FC is a 28-byte word result. Signed owner
parameter reads, unsigned halfword countdown wrap/reset, the signed random
threshold, byte-to-signed-byte reverse conversion and the different cancellation
rules are preserved. The FC source initially initialized its result before the
parameter read, reserving the native index register. An explicit read snapshot
alone was disproved. Defining the real result only in the two condition arms
restored native evaluation/register reuse and all 28 bytes without a type or
profile change. Both useful failed sources remain local.

Complete EC action sets were fixed before each single recipe. No assembly
instructions, numeric register constraints, added qualifiers or fabricated
operations supply these matches. Source ownership does not close generic EC/FC
consumers, table capacity, valid actor/record/sample backing, point-output
success, arithmetic domains or runtime selection/gameplay.


## Attachment actions 43, 46 and 73; saved-effect predicate

| Observed rows | Complete local C interval | Functions / extent bytes |
| --- | --- | ---: |
| 35, 36 | `0x0803D214..0x0803D45C` | 9 / 584, including 516 already owned |
| 39 | `0x08027564..0x08027738` | 9 / 468 |
| 40 | `0x08033730..0x08033940` | 9 / 528 |

The corresponding selectors write only 73, 46 or 43, and the status paths
independently dispatch those values. All EC sets were fixed before their
single recipes. The kind-73 worker/begin/status reverify under six appended
declarations without duplicate credit. Job 46 preserves unsigned duration and
elapsed arithmetic, including the signed-byte-times-50 producer converted to
its unsigned storage. Its status initially used a one-case switch that reversed
the native fallthrough blocks; the existing if/join result form restored all
32 bytes. No enum or profile axis was needed for these modules.

Each local count predicate and constant-100 neighbor remains explicitly
unrooted, with null FC words in the inspected rows. The separate predicate at
`0x080336B4` now also has 28 matching C bytes: it compares the saved-effect owner
with the first player slot's object, reusing the same canonical views and byte
result as the accepted inlined predicate in `frame_scene_effect_remove`.
Changing equality to inequality rejects one byte. Its incoming edge remains
unidentified. This fills the source gap between the existing 64-byte spawn and
96-byte remove bodies; combined with row 40, source ownership is continuous
from `0x08033674` through `0x08033940` (716 bytes).

These additions own 25 definitions / 1,092 C extent bytes: 1,034 instructions,
36 pool bytes and 22 genuine zero-alignment bytes. All real controls reject,
actual-definition API/layout checks pass, and the full matching/control and
progress gates pass. No assembly instruction, register constraint or added
qualifier supplies a match. Complete incoming/writable domains, valid state
backing and gameplay remain open.


## Spawn, shared action-49 and no-choice attachments

| Observed rows | Local interval | New C functions / extent bytes |
| --- | --- | ---: |
| 50 | `0x0802A974..0x0802AA78` | 8 / 260 |
| 56, 58 | `0x08016C68..0x08016E28` | 5 / 64; 384 already owned |
| 57 | `0x0800F4DC..0x0800F754` | 4 / 24; 608 already owned |
| 68, 70, 72 | `0x08013330..0x08013390` | 7 / 88; eight EC bytes remain original |
| No installed row identified | `0x08016E28..0x08016F24` | 7 / 180; 72 already owned |

These attachment additions own 31 definitions / 616 extent bytes: 592
instruction bytes, four pool bytes and twenty zero-alignment bytes. Actual
definitions and target layouts pass API checks; every changed-source control
rejects. Full matching/control and progress gates pass. Existing bodies were
reverified where their contracts connect the modules and receive no new credit.

Row 50 writes action 87. Its worker obtains the owner's attachment-zero point,
creates actor 4 with the owner's direction, plays cue 49, and sets the owner
parameter and phase. Its tick stores the genuine narrowed search result after
the commit call. That result lifetime is real here and does not resolve the
separate kind-66 worker. The neighbouring predicate requires two early checks;
combining them reversed the native final branch.

Rows 56/58 and legacy interaction row 57 both write action 49, retaining their
separate worker and ABI families. Row 57's source names retain the existing
`_31` convention. The next entry at `0x0800F754` is the owned animation step;
`0x08016E28` starts the distinct action-75 module. Neither is a constant-100
neighbor of the preceding module. The unrooted action-75 worker follows phases
0, 83 and 1; its already-owned route keeps its unsigned-byte return. No installed
callback or incoming role is inferred from this source grouping.

Rows 68/70/72 use an E8 selector that returns one without writing the choices
buffer, a conventional record allocator/begin and a constant-two status. Its EC
remains original: no action cases are evidenced. The neighbouring count
predicate and constant-100 body likewise have no identified incoming edges.
This module starts at `0x08013330`; the header-job rows' actual F8 pointer is
`0x08012E75`. Complete callback populations, generic EC/FC delivery, live point
and record backing, arithmetic domains and gameplay remain open.


## Attachment palette jobs, scene handoff and timed jobs

| Observed row | Complete local C interval | New functions / extent bytes |
| --- | --- | ---: |
| 74 | `0x0801781C..0x08017A68` | 10 / 588 |
| 88 | `0x08022170..0x0802224C` | 8 / 220 |
| 102 | `0x080466B4..0x0804694C` | 6 / 68; 596 already owned |
| 135 | `0x08034BF4..0x08034DB8` | 9 / 452 |

These four families add 33 C functions / 1,328 extent bytes: 1,240 instructions,
40 literal bytes and 48 native zero-alignment bytes. Actual-definition API and
layout checks pass; every changed-source control rejects, including size-changing
EC, allocation and tick controls. Full matching/control and progress gates pass.
No assembler instructions, numeric register constraints or profile changes supply
these matches.

Row 74 writes 9, then 8 or 11 according to the existing attachment mode, then
10. Its dispatcher independently routes those four actions to three workers.
The workers preserve the different cue/store order while advancing the three
actual palette-selector bytes and reloading the group palette. All ten first
recipes match; the constant-100 neighbour remains explicitly unrooted.

Row 88 writes action 26. Its worker handles phase zero's animation 60 and timer
30, phase six's decrement and scene request 9, and a nonzero running byte's
completion. The initial 96-byte source had 67 differences because it placed the
running arm before the real phase arm. Writing that phase arm first as
`if (!running)` restores native branch order without changing calls or reads.
The initial source/IR remain useful failure evidence.

Row 102 writes 48. Its existing worker, begin and dispatcher reverify under
the six appended declarations without duplicate credit. Row 135 writes 12;
initializer timers 900/0 and parameter `0x0500` feed its periodic worker/tick,
actual needs adjustment, repeated cue-71 handle and animation/state changes.
The worker and all eleven external providers have source. All nine first
recipes match. Its zero-valued FC entry is installed; the separate count
predicate has no identified incoming edge.

The new EC action sets were established from actual selectors and independent
status guards before compilation. Choice tails, generic EC delivery, found/live
records, signed countdown domains, all writers and gameplay remain open. The
separate [header-family tick and initializer](FRAME_NEED_EFFECT_HEADER_JOBS.md)
now close that family's 1,212-byte local interval.


## Sequence, need and default-choice attachments

| Observed family | Local interval | New C functions / extent bytes |
| --- | --- | ---: |
| Row 131 | `0x08023AA0..0x08023D00` | 9 / 608 |
| Row 96 | `0x08016680..0x080167B8` | 7 / 312 |
| Row 133 | `0x0802BC10..0x0802BDAC` | 10 / 412 |
| Shared fallback rows | `0x08035028..0x080350A4` | 7 / 116; eight EC bytes remain original |

These additions own 33 C definitions / 1,448 bytes: 1,352 instructions,
60 literal bytes and 36 native zero-alignment bytes. Actual definitions,
provider declarations and target layouts pass API checks. All genuine source
controls reject, including size changes. Full matching/control and progress
gates pass. No instruction assembly, numeric register constraint or compiler
profile change supplies these matches.

Row 131 always writes action 18, adds 3 when its full mode word differs from
one, and adds 4 when nonzero; it returns success one. Its dispatcher preserves
the actual volatile audio-byte operations when selecting sequences 3/4. The
selector's initial 40-byte recipe differed by six bytes: it initialized the
cursor before the first output store. Assigning that real cursor after storing
18 reproduces native source order. Row 96's independent action-18 family uses
the real attachment count to select need 2 or 3, then tests the timer provider's
low byte. That ordinary normalization does not explain kind 66's missing shift.

Row 133 writes 16/17 and independently dispatches both. Its second worker uses
the canonical game-state root and actual word/byte pending-selection views.
Acquiring that real root before the transition call caused ten differences in
116 bytes; assigning it after the call restores all bytes without a new alias,
type, qualifier or operation. Both useful initial failures remain retained.
The action-3/4/18 and 16/17 selectors write no zero terminator; choice-tail and
consumer domains remain separate.

The fallback selector writes nothing. Its status recognizes record kind 40,
but the generic chooser intercepts common choices 40/34 before F0; those writes
do not supply a grounded EC case set. EC `0x08035060` stays original and
uncompiled. Its constant-100 neighbour at `0x080350A0` is installed as FC by
rows 10/103: the actual byte-result/state-argument declaration replaces an
initial private word/void guess before publication. The separate predicate
remains unrooted. This differs from the 13 published four-byte default-100
neighbours with no aligned ROM pointer in a bounded full-ROM scan.

Generic EC delivery, full table/writable populations, found/live record backing,
serialized indices, signed arithmetic and scheduling/gameplay remain open.
