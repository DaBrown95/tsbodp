# Audio-options scene path

Nine connected C functions cover 1,556 original extent bytes. The audited scene
phase table's row six contains the initialization, input and shutdown pointers
`0x0802FB85`, `0x0802FD79` and `0x08030065`. The other four scene functions draw
rows, change a live level, choose a destination and move the selection. Two
separate game-audio wrappers complete the indexed-channel clearing edges. Names
follow these observed uses and remain inferred; this is static and source-match
evidence, without a gameplay claim.

| ROM extent | Function | Bytes |
| --- | --- | ---: |
| `0x2FB84` | `scene_audio_options_initialize` | 500 |
| `0x2FD78` | `scene_audio_options_step` | 108 |
| `0x2FDE4` | `scene_audio_options_draw_row` | 356 |
| `0x2FF48` | `scene_audio_options_change_level` | 284 |
| `0x30064` | `scene_audio_options_shutdown` | 48 |
| `0x30094` | `scene_audio_options_choose` | 96 |
| `0x300F4` | `scene_audio_options_change_row` | 116 |
| `0x4135C` | `audio_game_clear_indexed_channels` | 24 |
| `0x41374` | `audio_game_clear_indexed_channels_alternate` | 24 |

## State and dispatch

The phase table begins at `0x0805797C`, with three four-byte callback pointers
per row. The active request view at `0x03004350` supplies the word at `+0x0C`
used as the selected row. Initialization sets it to zero. The previous request
at `0x03004370` supplies a return kind: its first word is retained for kinds
five and eleven, otherwise its scene word at `+8` is used. The observed RAM
views are two level bytes at `0x03001E38`, a cue handle word at `0x03001E3C`,
a saved sequence byte at `0x03001E40` and a return-kind halfword at
`0x03001E42`. These declarations do not establish a complete allocation or
ownership model for the intervening storage.

Initialization divides the game-audio sequence volume by 25 into level zero
and the sample volume by 12 into level one. The BIOS divide provider remains
explicit low-level glue and gains no C credit here. The four-byte entry at
`0x0804C8C8` contains `SVC 0x06` followed by `BX LR`, accepting the observed
`R0`/`R1` operands and returning `R0`. Its quotient name follows the division
uses in the callers; no BIOS arithmetic corner cases were tested in this batch.
The next entry at `0x0804C8CC` separately moves the service's `R1` result into
`R0` and remains unconverted. Except when the previous
kind is thirteen, the current sequence ID is saved before selecting it again.
The setup configures backgrounds one, zero and two, chooses the text-bank
background, loads the palette and ranges, creates five scene objects and draws
all four rows. The existing serialized background/table entries remain data,
not reconstructed source or public assets.

Input reads the local player's pressed halfword and tests buttons in order:
bit zero chooses a destination; `0xC0` changes the row; `0x30` changes a level;
bit one returns to kind five or eleven. The row helper uses the existing local
vertical-input provider over zero through three, redraws the old and new rows,
replaces cue two, and moves the first scene object. Its observed position is
`x = 40` for rows zero/one and `x = 64` otherwise, with `y = 81 + 16 * row`,
converted to fixed-point coordinates. The word selection and byte local-player
arguments preserve the original widths.

Choosing row two submits kind twelve, mode zero and the saved return kind.
Choosing row three submits kind thirteen with the same mode/scene, then replaces
cue one. Rows zero and one do not submit a request. The wider meanings of kinds
twelve and thirteen are not established by this batch.

## Drawing and live audio

Each label uses resource text `row + 18`, tile base `row * 100 + 1` and
`y = 83 + 16 * row`. Rows zero/one center at `x = 96`; other rows use `x = 120`.
The selected row uses font palette three, otherwise zero. The row drawing
provider's style one centers text horizontally. For the two level rows, the
value is drawn 80 pixels farther right. Zero and ten select text resources 207
and 209; other values use the existing number formatter and a 32-byte local
buffer. The value rectangle is cleared before drawing.

The drawing path manipulates bit zero of existing scene-object flags at
`+0x0C`. Row zero uses object slots one/two and row one uses three/four. The
initializer's initial flag tests use level one for slots one/two and level zero
for slots three/four, before the four-row redraw. Those distinct accesses are
retained. Their visual consequences and the resource-defined object placement
have not been tested here.

The live-level handler accepts selected rows zero/one and uses the two observed
limit bytes, both ten, at `0x080694E0`. It stores the input helper's resulting
level byte, then converts it to a game-audio volume. Row zero uses 255 for ten,
otherwise 25 times the level. A transition to zero stops the sequence; a
transition from zero first sets the volume, saves the sequence ID, writes the
sentinel 255 into the control, then reselects the saved ID. Other cases set the
sequence volume directly. Row one uses 128 for ten, otherwise 12 times the
level; a transition to zero clears indexed channels before setting sample
volume. The setter inputs are explicitly narrowed to the observed low byte.
All four labels are redrawn and cue zero is replaced afterward.

Shutdown runs the second transition, clears background zero, releases the
primary object list, resets display/palette jobs and scene-object slots, then
clears indexed audio channels. Both 24-byte game wrappers call the already
reconstructed `audio_clear_indexed_channels` only when sample volume is nonzero.
Their identical bodies occupy separate original entries; neither restores
volume. The older shutdown caller's address alias is retained with the same
void ABI.

## Source and verification limits

The seven unconstrained functions match in ordinary C. The drawing function
uses one scoped word binding to `R0` for the real centered-text style argument
of its first draw call. It is consumed as the fifth argument and expires before
the call returns. The second draw is unbound. Removing the first binding keeps
the length but changes allocation throughout the function; retaining only the
first gives the complete match. No synthetic initialization or unused traffic
is used.

The live-level handler uses two scoped `R0` bindings for the actual initial
request pointer and initial level-table pointer. The first supplies the
selection snapshot; the second supplies its level byte. Both expire before the
horizontal-input call and subsequent global reads remain fresh. Index-first
integer address addition retains the original operand order. Natural pointer
forms preserve those roots across the call and emit 280 bytes; the matched
form emits all 284 bytes. These source constraints do not claim the original
compiler flags or source spelling.

All original pools and alignment are part of the comparison. Initialization
ends at the independent input prologue `0x2FD78`; the input extent includes its
pools and two zero bytes before drawing. Drawing owns its interspersed pools
through `0x2FF48`. The live-level extent ends at shutdown `0x30064`; shutdown,
choice and row-change extents end at `0x30094`, `0x300F4` and `0x30168`.
The two audio wrappers each own their literal and alignment, with independent
entries at `0x4135C`, `0x41374` and the following `0x4138C`.

Every new function has an actual changed-source negative control. Current
provider/caller rechecks cover 41 existing functions and 4,180 bytes, with no
duplicate C credit. The seven actual division relocation importers consist of
the new initializer and six existing tile-copy, movement, clock-formatting,
percentage and need-effect consumers. Changing the wrapper's service number
from six to seven rejects the full four-byte glue comparison. Thus this batch
adds nine matching C functions and 1,556 C extent bytes, plus four explicit
assembly-glue bytes separately. Useful
failed natural-address, statement-order and constraint-minimization attempts
remain in ignored reports. The UI limit table is evidence for intended slider
limits, not a proof of every possible initial audio option or arbitrary
selection/index domain. Resource-string capacities, object allocation success,
background dimensions and scene-kind semantics remain unresolved. Whole-ROM
equality, mapped extents, this source match and runtime behavior are separate
claims.
