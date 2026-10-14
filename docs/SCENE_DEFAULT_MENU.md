# Defaults menu phase path

Names describe the observed defaults, option-byte, drawing and request operations.
They are provisional. The fixed USA/Europe revision-0 ROM has the callback triple
`08045995 / 08045B71 / 08045F85` at `080579B8`, which is flat phase-table row 5
from base `0805797C` with a 12-byte stride. This row numbering is separate from
the activity-definition table. The published dispatcher uses three
`void (*)(void)` callbacks; actual definition diagnostics check these compatible
types and the 12-byte, alignment-4 row representation.

The initial recovered cohort covers seven complete extents: initialization
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
Phase one first tests mask 9 for acceptance, then mask 240 for the recovered
selection helper. Other phase values perform no action. The player index still
comes from the existing byte at offset 49 and indexes the four declared pressed
halfwords without a new bounds check. Acceptance preserves requests 19, 7, 6
and 10 for selections zero through three. Other selections submit no request
while retaining the cue and random-seed operations. Row drawing retains
unsigned tile and vertical-position arithmetic; the vertical word is passed to
the existing signed drawing formal. Arbitrary row and conversion domains are
not established by the bounded checks.

The initializer's copy counter and record counter have separate real lifetimes.
Its explicit zero/nonzero mode assignments recover the original branch order.
The row drawer loads an unselected option before choosing its color, and the
stepper forms the directional mask inside the branch that consumes it. These
source scopes reproduce the native value phases without extra surviving reads.

The connected successor recovers all three former original menu children:
selection `45C98 / 340`, stage `3E3A8 / 120` and endpoint initialization
`3D45C / 356`. It also recovers their actual callback setter `3E420 / 12`,
clock callback `3E4CC / 32` and two-byte clear `3A53C / 20`. These six complete
extents add 880 C bytes, bringing the related phase and endpoint path to thirteen
functions and 2,108 C bytes. The numeric `scene_stage_0803e3a8` name remains
provisional. Its existing scene-initialization caller keeps that name. The menu
initializer and stepper change only their same-address setup and selection call
aliases; their original source controls are preserved.

The initial cohort verification covers seven actual changed-source controls, strict
declaration diagnostics and the current 36 accepted direct providers. Actual
definition checks exercise request, input and save widths and offsets, callback
types, full-word drawing and the existing font-fill interface. Seven genuine
omitted declarations reject in the strict profile. Six omissions preserve their
legacy bytes; omitting the pointer-returning constructor changes legacy bytes
and is recorded as a mismatch.

The initial finite interpreter checks 161 original, compiled and changed-source cases,
with 85 control divergences and four interpreter/input rejection controls.
Nested execution includes the recovered menu bodies, world reset, game-value
setter, heap clear and actor-entry preparation, plus unchanged original reset
and padded-copy helpers. At that receipt boundary, display, audio, transition, allocation and the three
then-unconverted menu children used explicit abstract hooks. Those immutable
receipts remain predecessor evidence; they are not relabeled as execution of
the newly recovered children. Fixtures initialize
aligned numeric memory and bound rows and players to zero through three and
text banks to the two sampled entries. Caller-saved registers are poisoned and
callee-saved registers and stack restoration are checked. These observations
do not prove arbitrary capacities, opaque-child behavior, hardware, save-format
validity, protocol correctness or gameplay. Interpreter rejection is not a
claim of a corresponding hardware fault.


# Selection and endpoint successor

`scene_default_menu_change_selection` snapshots the previous selection word,
uses the actual vertical-input provider and repeats while the selected option
byte is zero. It redraws the previous and current rows, positions the selector
and replaces the retained cue handle. A zero enabled-option set, or a disabled
selection without a vertical change, can retain the search indefinitely. There
is no new escape, guard or option initialization. The observed option prefix
has four bytes; the external array still has no complete capacity claim.

The first draw argument is the unsigned tile allocation `21 + 30 * row`; the
actual pixel X is 120 and pixel Y is `91 + 16 * row`. A real two-word local keeps
the tile and vertical values together. A separate four-byte, alignment-4 union holds the old
row word, then the returned text pointer after the last row read. Each member is
written before its reads; there is no inactive-member read or pointer/integer
conversion. The font helper gives its actual font, palette and fill values
separate assignment phases. Ordinary C reproduces both calls without register
annotations. The drawing style naturally remains live across the two calls.
Failed scalar, type and constrained predecessors remain preserved locally.

`link_initialize_endpoint` forms the observed queue and record pointers, clears
specific words and bytes, and performs five twelve-byte zero fills through the
existing BIOS wrapper. It installs `link_tick_clock`, updates specific register
halfwords, clears the two observed random-related bytes and preserves the final
identifier and recording masks. `link_reset_random_bytes` is only a name for
those two byte stores, not a claim that it resets the complete random generator.
The BIOS wrapper is existing explicit glue and adds no C or new glue credit.

The shared endpoint access prefix is 172 bytes with alignment four. It has two
embedded twelve-byte event records, two arrays of four record pointers, and two
arrays of four twelve-byte records. The prefix size and offsets follow actual
accesses at the word-aligned root `03002CB0`; full storage capacity and ownership
remain unproved. The callback word at offset eight has the compatible
`unsigned int (*)(void)` view for the installed clock provider. The mapped
indirect caller supplies no explicit arguments and ignores the returned value;
the provider itself still computes and returns a word. Other possible callback
targets and the complete serial driver are not reconstructed by this path.

The clock callback increments an unsigned word. Values at most ten after the
increment return one; larger values clear the word and return zero. Unsigned
wrap at the largest word value is retained. This does not establish an interrupt
rate or protocol meaning. The stage body preserves its flag masks, conditional
interrupt-enable clearing and halfword stores. Register lvalues use volatile
halfword access at the observed addresses. Finite MMIO evidence uses explicit
numeric register storage and compares source/native read and write order; it
does not model hardware, interrupt concurrency or safe asynchronous use.

The private public-shaped successor proves six new bodies and all seven current
menu-header importers, the existing scene initializer and eight actual selection
providers. Twenty-two normal positive/control pairs and eight strict pairs
preserve full native extents, pools and alignment. Actual-definition diagnostics
check 47 physical facts and nineteen API assignments, including the real phase
callback row, local union and endpoint field. Seventeen wrong declarations,
offsets, widths or alignments reject. Five real omitted function declarations
leave legacy bytes identical and reject under strict declarations.

The successor's models replay 1,299 initialized bounded cases: 1,104 selection
cases with the actual input and position bodies, and 195 endpoint cases with
the actual setter and two-byte clear. Three additional selection cases inject
explicit abstract post-draw word writes to test the final selection reload and
fallback; they do not claim the real drawer performs those writes or extend the
option-array capacity. Across these 1,302 defined cases, the actual source
controls diverge in 1,244 cases. Eighty-eight separate searches exhaust the
finite budget without changing the source. Eleven interpreter/input failure
controls are separate from hardware faults. The same preserved source models
are freshly replayed against the proposed bytes; no second independent model
or general rendering, audio, serial-protocol, save-format or gameplay proof is
claimed.
