# Attachment job 25: selection, routing and parameter progress

This connected path reconstructs seven C functions covering 584 bytes, including
original literal pools and alignment. Five reconstructed callbacks are installed
in the observed need-effect definition row 98. The dispatcher leads to the
456-byte update at `0x08048444`, and that update calls the eight-byte signed
fixed-word need reader at `0x0802B9A8`. These functions connect the existing
attachment allocator, routing, animation, need adjustments, parameter indicator
and audio providers. They do not constitute a complete attachment subsystem.

The definition root is `0x08062E7C`, with a 36-byte stride. Row 98 at
`0x08063C44` supplies initialization `0x0804860D`, selection `0x08048639`,
acceptance `0x08048641`, beginning `0x08048649`, dispatch `0x08048691` and
finishing `0x080486B1`. The separate accepted capacity callback is
`0x0802F349`. The acceptance function at `0x08048640` now has eight matching
C bytes from the [selector-backed constant-result switch](FRAME_NEED_TARGET_SELECTION.md#constant-result-ec-switches-and-the-retained-lr-save).
The earlier plain-return source omits its LR-saving prologue and is not accepted. The unreferenced predicate at `0x08048610` (40 bytes) and constant-100
leaf at `0x080486B4` (four bytes) also remain original. The latter is a real
leaf, not alignment belonging to the empty finishing callback. Only the actual
two zero bytes at `0x080486B2` belong to that callback's four-byte extent.

The definition-row index and attachment-record kind have separate roles.
`owner->kind` selects the 36-byte definition row; the selected record kind is
25. The record's signed phase/countdown word is at offset 8, running byte at
12 and routing status word at 16 in the retained 24-byte record view. The
existing owner prefix supplies its object pointer at 84. A local work view
reads the indicator pointer at 88; a separate actor view reads its signed
countdown at 88. Both are 92-byte access prefixes, without a claim about full
storage or ownership. The actor's need-state pointer comes from offset 96.
The reader exposes the observed eight signed need words through a separate
32-byte prefix; unchecked incoming index validity remains unproved.

Beginning preserves allocation failure as result zero. Success stores the
incoming word kind, obtains the owner's attachment position, begins a route
with the actual status-field address, requests animation 6 and returns one.
Dispatch checks the stored job kind for 25 and returns the main update's word
result, otherwise zero. The initializer and selector return one; finishing is
the installed empty callback. Their provisional callback declarations follow
the installed call roles; unused incoming values alone do not establish a
unique original signature.

The main update uses observed phases 0, 8, 63 and 1. A running byte equal to
one forces phase 1. Phase 0 selects the low-need animation/cue path or creates a
parameter indicator and begins animation 25/26 according to the signed social
word comparison with `0x05000000`. It sets the actor countdown to 150.
Phase 8 waits for flag `0x400000`, then requests animation 1 and clears the
need countdown. Phase 63 adjusts needs with kind 12 and definition byte 35,
updates the parameter indicator and advances the social parameter, or counts
down when its signed parameter byte is ten. A signed need word at index 2
at or below `0x13FFFFFF` also ends the phase. Phase 1 requests animation 1,
commits state 2 and conditionally finishes the retained indicator. Its return
is two; other paths return one. Gameplay meanings of these numbers remain
provisional.

The actual signed-parameter provider returns an `LDRSB` result as an int.
Its observed result range is therefore -128..127, so adding one to the retained
previous value does not overflow int in this connected call graph. The separate
signed countdown decrement still requires defined-source input bounds; native
wrapping at `INT_MIN` is a different claim. In phase 63 the indicator setter is
called without a null guard when the parameter differs from ten. Valid indicator,
resource and sequence storage and a nonzero narrowed division denominator are
necessary preconditions; nullable creation and nullable phase-1 cleanup do not
establish those preconditions for a later update.

Ordinary C matches all seven bodies, without register bindings or instruction
transcriptions. A shared function-scope previous-parameter value reproduces the
original value lifetimes across phases. The percentage is calculated before
loading the retained indicator pointer for the setter; a nested argument
expression reverses that real producer order and changes the compiler output.
The dispatcher retains a joined result assignment rather than introducing
additional calls or padding. Raw failed sources and complete comparisons remain
local. Alignment directives express only the observed zero tails.

Normal and strict positive/changed-source pairs compare complete extents.
Eighteen existing direct providers are separately recompiled with their source
controls. Target-compiler diagnostics check 26 physical facts and seven actual
definition APIs; seven deliberately wrong headers reject. Four actual omitted
declarations remain byte-identical with the legacy profile and reject under
strict declarations. These checks, static transfer resolution, finite execution,
whole-ROM matching and publication are separate evidence layers. None alone
establishes runtime or gameplay behavior.

The held pre-interface canonical finite bridge replayed 957 initialized bounded cases against the
original, compiled and actual changed-source bodies, with 691 control
divergences and thirteen deliberately rejected model/input cases. Positive
cases execute the seven new bodies and eighteen accepted helpers. Actual
controls additionally execute the accepted fixed-multiply helper, for 26 bodies
across both roles; an unreached need-value sibling is excluded from that count.
All 256 signed-parameter byte values are exercised. Two additional cases,
`INT_MIN` actor countdown and a negative signed attachment-coordinate shift,
are numeric native comparisons with no bounded C behavior claim. Eighteen
bridge integrity guards reject changed pins, models, bodies, inputs, metadata,
roles or ABI qualifications. A mapped neighboring countdown word is explicitly
rejected as an extra need-array element. The finite model uses initialized
aligned memory, call effects and abstract service outcomes; it does not prove
resource capacity, unrestricted pointers, hardware behavior or gameplay.


The actual shared callback interfaces require a separate correction. The
need-effect allocator copies definition fields +4, +12, +16 and +20 into state
slots E8, F0, F4 and F8 respectively. Both converted E8 callers ignore the
reconstructed selectors' word return. The three converted F0 roles now agree
on a word result and word kind with need-effect-owner and actor pointers; real
choice operands still come from byte loads. The two callers which observe
only the result's low byte retain explicit byte conversion. The F4 dispatcher
uses the real need-effect-owner pointer type. F8 receives one owner argument;
the empty row98 finish therefore has one formal, with no unused actor formal.
These declarations follow the reconstructed targets and observed call roles,
not a claim about every unconverted target or historical source spelling.

The held seven-source predecessor retains its original 26 physical checks,
seven self-interface checks, eighteen bridge guards and 957-case model as
separate evidence. Those self-interface checks did not detect the incompatible
shared caller declarations. The successor tests 35 actual reconstructed
provider definitions against their shared caller fields, twelve physical facts
and seven field interfaces; eight genuine wrong return, kind, pointer-tag or
argument-count declarations reject. The complete current literal importer
closure has 182 existing bodies. Joined with the seven new bodies it supplies
189 distinct normal positive/control pairs, and 46 connected bodies also have
strict pairs. Ten existing C sources and nine existing headers are repaired
without additional C credit; only the seven new bodies contribute 584 bytes.

The producer-owned finite successor freshly replays 957 initialized cases and
691 actual controls. It explicitly changes the sole direct finish fixture to
one owner argument. Thirteen model/input failures and the two numeric-only
overflow/shift cases remain separately classified. This reuses the earlier
source model and interpreter; it is not a newly independent model. Complete
call-transfer byte proofs and actual field/provider diagnostics complement that
bounded source-model evidence. E4 capacity callbacks and other unchanged
provisional roles are not made universally correct by this scoped repair.
