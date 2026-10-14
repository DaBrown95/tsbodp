# Defaults menu phase path

Names describe the observed defaults, option-byte, drawing and request operations.
They are provisional. The fixed USA/Europe revision-0 ROM has the callback triple
`08045995 / 08045B71 / 08045F85` at `080579B8`, which is flat phase-table row 5
from base `0805797C` with a 12-byte stride. This row numbering is separate from
the activity-definition table. The published dispatcher uses three
`void (*)(void)` callbacks; actual definition diagnostics check these compatible
types and the 12-byte, alignment-4 row representation.

The connected recovered candidates cover seven complete extents: initialization
`45994 / 476`, stepping `45B70 / 124`, row drawing `45EAC / 88`, shutdown
`45F84 / 48`, background preparation `45DEC / 192`, slot entry `45BEC / 172`
and acceptance `45F04 / 128`, totaling 1,228 C bytes. Each comparison includes
the complete original literal pools and alignment at its fixed address. These
bodies use ordinary C without register annotations, volatile substitutes or
additional guards. The supported compiler configuration reproduces the bytes;
it does not uniquely identify the historical source or compiler options.

Initialization calls the recovered world reset and copies the four observed
default bytes into the option storage. It checks the four saved validity bytes
and the first byte at offset 16 of each 40-byte record to enable option 1. These
accesses use the existing 204-byte, alignment-4 save-state representation with
records at offset 20 and validity bytes at offset 180. The external option array
has no claimed complete capacity. The initializer converts the incoming mode
word to zero or one for the phase field, snapshots the request kind into the
existing selector word, and preserves the original flag masks and link clear.

Previous request kinds 6, 19, 7 and 10 take the slot-background path. Other kinds
prepare the introductory background and text. The background helpers retain
the original resource pointers, tile coordinates, controls and palette loads;
resource names identify their use rather than decoded asset content. The two
sampled text-bank pointers in each table are a bounded ROM prefix. The bank
index, resource ownership and complete table capacity remain unchecked. The
selector-object result is stored without a new allocation guard.

Phase zero accepts pressed bits in mask 9 to transition into the slot display.
Phase one first tests mask 9 for acceptance, then mask 240 for the original
selection helper. Other phase values perform no action. The player index still
comes from the existing byte at offset 49 and indexes the four declared pressed
halfwords without a new bounds check. Acceptance preserves requests 19, 7, 6
and 10 for selections zero through three. Other selections submit no request
while retaining the cue and random-seed operations. Row drawing retains
unsigned coordinate arithmetic and passes the resulting words to the existing
signed-coordinate drawing interface; arbitrary row and conversion domains are
not established by the bounded checks.

The initializer's copy counter and record counter have separate real lifetimes.
Its explicit zero/nonzero mode assignments recover the original branch order.
The row drawer loads an unselected option before choosing its color, and the
stepper forms the directional mask inside the branch that consumes it. These
source scopes reproduce the native value phases without extra surviving reads.

Three connected bodies remain original and receive zero recovered-C credit:
selection `45C98 / 340`, stage `3E3A8 / 120` and object setup `3D45C / 356`.
The existing `scene_stage_0803e3a8` name is reused. The last two overwrite incoming
argument registers before use, supporting the retained void interfaces without
claiming complete behavior. Selection is preserved as an explicit original
call; its closest ordinary source still differs in register and constant
lifetimes. Its option search and all original unchecked assumptions remain.

Private verification covers seven actual changed-source controls, strict
declaration diagnostics and the current 36 accepted direct providers. Actual
definition checks exercise request, input and save widths and offsets, callback
types, full-word drawing and the existing font-fill interface. Seven genuine
omitted declarations reject in the strict profile. Six omissions preserve their
legacy bytes; omitting the pointer-returning constructor changes legacy bytes
and is recorded as a mismatch.

The finite interpreter checks 161 original, compiled and changed-source cases,
with 85 control divergences and four interpreter/input rejection controls.
Nested execution includes the recovered menu bodies, world reset, game-value
setter, heap clear and actor-entry preparation, plus unchanged original reset
and padded-copy helpers. Display, audio, transition, allocation and the three
unconverted menu children use explicit abstract hooks. Fixtures initialize
aligned numeric memory and bound rows and players to zero through three and
text banks to the two sampled entries. Caller-saved registers are poisoned and
callee-saved registers and stack restoration are checked. These observations
do not prove arbitrary capacities, opaque-child behavior, hardware, save-format
validity, protocol correctness or gameplay. Interpreter rejection is not a
claim of a corresponding hardware fault.
