# Definition row seven: actor phases, timed effects and round status

This connected group reconstructs the initializer, three creators, the installed
primary and timed-effect updates, three animation helpers, the round-status
drawer and the definition's empty scene step. Its eleven C functions own the
continuous 2,480-byte ROM interval `0x08047A94..0x08048444`, including original
literal pools and zero alignment. The unrelated attachment handler starting at
`0x08048444` is outside this group. The empty scene step is included because the
same definition row installs it; it is four bytes including two zero alignment
bytes, and does not stand for an unconverted body.

The table at `0x0805955C` has an observed eight-row definition prefix. Row seven
at `0x08059620` installs initializer `0x08047A95` and scene step `0x08048211`.
The initializer creates the main actor and status object and draws the current
round label. The main creator installs `0x08047D1D` at object offset 136;
its update's entry comparison bounds the local jump table to phases zero through
ten. The timed effect creator installs `0x08048281` at the same offset.
All creators store the accepted before-step provider `0x08001AE1` at offset 152.
These are static transfers and exact compiler matches, not observations of
hardware execution or gameplay.

The primary update connects pressed input, phase and frame transitions, effect
creation, audio activity/cues, round score and completion. It clears pending
animation updates after applying the observed masks, and uses the existing
object byte at offset 76 as a completion-bonus latch. In the shared actor view
that byte is provisionally named `actor_id`; its role in this activity differs
from that name's usual interpretation. The phase byte is at 78, pending updates
at 79, the signed countdown word at 88 and previous animation frame at 218.
The helper uses the sequence's halfword frame count at offset 6. Frame helpers
and audio/display providers retain their separately verified declarations and
addresses.

The activity state uses an observed 36-byte prefix of the existing 420-byte
scene allocation: primary pointer 0, signed score 12, unsigned round 14, option 19,
flags 21, status pointer 24, sample handle 28, press count 32 and failure count 33.
The role-specific flag prefix covers 216 bytes; the countdown access view covers 92.
Neither prefix claims a complete original structure, ownership or allocation
capacity. Pinned target-compiler diagnostics check physical offsets, widths,
signedness and four-byte alignment and the actual eleven definitions' APIs.
The existing 320-byte object allocation and target header views remain unchanged.

The option records start at `0x08084104`. Five 36-byte records fit the observed
prefix before the next animation header at `0x080841B8`. Each has four eight-byte
round records and a countdown byte at 32. The round helper accesses label 0,
thresholds 1/2/3 and reward 4. This establishes a local physical prefix; arbitrary
incoming selector validity is unproved. The existing appearance prefix at
`0x03003970` supplies group 0 and variant 2, sharing the physical root already
observed by the row-six primary appearance view. This group uses a local role
alias and does not change existing declarations. ROM part-table roots are distinct
`0x08D74234`, `0x08D745B4` and `0x08D743F4`; the third table additionally selects
by the activity option. Palette and background symbols refer to unchanged local
ROM resources and do not reproduce their contents in source.

Ordinary C matches ten bodies. The three animation helper interfaces retain
word-valued animation/state inputs and the advancing helper separately narrows
its threshold at entry; effect selection has an incoming byte formal. These
views follow the observed call transfers, with narrowing at the existing
provider calls rather than at invented earlier boundaries. The primary update uses one actual local register
binding: the value in `r1` loads the failure count at `0x080481E2`, becomes the
remaining count, multiplies by option plus one, and becomes the tenfold bonus.
Its last consumer transfers it to the call argument at `0x080481F4`; the value
is dead before the score call at `0x080481F6`. No call crosses this lifetime.
Removing the binding produces 1,264 bytes with 32 differences instead of the
original 1,268 bytes. A predecessor combining the initial subtraction in the
bound initializer leaves three different bytes; splitting the actual load and
subtraction phases matches. Earlier dual nominal-pointer source and direct-score
attempts are retained with raw compiler and comparison evidence. The binding
consumes a real source value and is not an instruction-body transcription.

The world byte at offset32 is provisionally named `gender` in the local view:
that inference comes only from selecting paired cue IDs 222/224 and 223/225,
and its gameplay meaning remains unproved. The retreat helper retains this
byte read even though both branches choose
the same audio cue. The ordinary compiler preserves that read from the actual
branch expressions. The status drawer consumes the formatted-number pointer as
its local text value before copying it into the text field; a nested expression
predecessor removes the native pointer transfer. The original zero tails at the
empty step and three small helpers use explicit alignment directives. No output
patches, masks, copied instruction bodies, added volatile reads or guessed filler
are used.

Normal and strict positive/changed-source pairs compare the complete extents.
Four real missing-declaration controls still match with the permissive legacy
profile and reject under strict declarations. Ten deliberately wrong role/API
headers reject in target-compiler diagnostics. The connected accepted providers
are separately recompiled with their retained source controls. All of this is compiler/static evidence. Separate finite checks execute all
eleven new bodies and eight accepted helpers in 2,092 initialized cases, with
555 actual changed-source divergences and six deliberately rejected interpreter
or input cases. Allocation, animation, audio and display outcomes remain
explicit abstract hooks. Two additional `INT_MIN` countdown cases are classified
as numeric native diagnostics and receive no bounded C claim. Canonical source
and byte correspondence, independent review and the full-ROM gate are separate
requirements. Signed-short score narrowing is
target-specific, and decrementing `INT_MIN` is excluded from defined-source
behavior. Input, allocation, pointer validity and resource capacity are not
proved merely by a byte match.
