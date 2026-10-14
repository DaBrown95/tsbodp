# Contact activity definition five

This path reconstructs 30 connected C functions covering 4,736 bytes, plus an
explicit eight-byte BIOS remainder wrapper with zero C credit. It follows the
initializer and controller through board population, input selection, recursive
matching, removal timers, falling and compaction, follow-up replacements and
final scoring. Names describe observed roles and are provisional.

| Function suffix | ROM offset | Complete extent |
| --- | ---: | ---: |
| initialize | 32EF4 | 108 |
| step | 32048 | 500 |
| reset | 32F60 | 52 |
| set_selection | 32F94 | 68 |
| refresh | 32FD8 | 80 |
| selection_finished | 33148 | 48 |
| reset_selection | 32580 | 128 |
| has_adjacent_pair | 32474 | 268 |
| clamp_selection | 32B14 | 76 |
| begin_end | 3223C | 140 |
| update_selection | 322C8 | 172 |
| remove_marked_cells | 32C38 | 132 |
| create_followup | 32A5C | 184 |
| advance | 32848 | 404 |
| rebuild_cells | 326E0 | 148 |
| compact_columns | 32774 | 212 |
| create_root | 329DC | 128 |
| reset_timers | 3310C | 60 |
| set_timer | 330C0 | 76 |
| assign_timer | 3307C | 68 |
| refresh_timer | 33028 | 84 |
| step_root | 3320C | 48 |
| set_cell_frame | 3323C | 80 |
| step_cell | 32B60 | 216 |
| apply_selection | 32600 | 224 |
| populate | 32374 | 256 |
| create_cell | 33178 | 148 |
| set_cell_timer | 3328C | 60 |
| step_followup | 32CBC | 356 |
| replace_cell | 32E20 | 212 |

All offsets above use the `scene_contact_activity_five_` name prefix. Complete
extents include the literal pools, switch tables and original zero alignment.
The timer updater at 33028 owns 84 bytes and the five-kind timer step at 32FD8
owns 80 bytes; their earlier provisional mapping omitted two alignment bytes.

## Entry and object ownership

The 28-byte definition at 080595E8 is row five of the table at 0805955C. Its first
two words name initializer 08032EF5 and controller 08032049. The accepted secondary
activity initializer/controller call these as `void(void)`. The accepted scene
initializer allocates 420 bytes and the object allocator provides 320-byte slots.
Allocation failure remains unchecked in the reconstructed source.

The root, cell and follow-up factories install callbacks 0803320D, 08032B61 and
08032CBD respectively. All use the scheduler's actual
`void(struct FrameObject *)` callback. The complete known local graph is now C;
underlying frame, input, heap, random, display, palette and audio services remain
separate accepted providers or explicit bounded behavior hooks. This does not
establish a complete game inventory or a gameplay result.

## Physical access views

The [activity header](../include/scene_contact_activity_five.h) describes an
observed 420-byte state with alignment four. The grid's first index corresponds
to X/column, and its second to Y/row; `cells.rows` names its two-dimensional
storage view, rather than changing those axis roles.

| Offset | Observed state role |
| ---: | --- |
| 0 | root object pointer |
| 12 / 14 | signed score / unsigned combo-count halfwords |
| 19 / 21 | option and common flags bytes |
| 24 | 64 object pointers, four bytes each |
| 280 | five eight-byte timer records; signed timer and separate word |
| 320 | 64 grid bytes with equivalent 8 by 8 and flat views |
| 384 / 392 | eight signed column heights / eight pending-shift bytes |
| 400 / 404 / 408 / 412 | selected column / selected row / column count / selected count words |
| 416 | signed settlement-row byte |

The word at timer-record offset four is incremented during population. Its full
lifecycle is not inferred. Heights and settlement row require signed reloads;
the count at 412 is incremented by the recursive walk, rather than being a boolean.
Cell expiration consumes combo offset 14 with LDRH, multiplies its unsigned value,
and increments the halfword. The score at 12 is passed to the score service as a
signed halfword. Those are distinct type domains.

The object access prefix is 220 bytes/alignment four within the 320-byte slot.
It reaches next/previous at 0/4, id/subtype at 8/10, flags at 12, position at 24,
velocity at 40, acceleration at 48, destination at 56, phase/cell at 77/78,
unsigned timer at 88, scheduler callback at 136 and frame byte at 216. Cell uses
78 as a grid index; follow-up uses the same byte as its own update state.
The D1/D5 bitfield views preserve the observed contact, double-size, layer and
palette accesses. They are role prefixes, not recovered original type names.

Subtype is a real unsigned halfword. Rebuilding the grid reads its low byte
through a permitted character representation access. An earlier small union
hypothesis had different alignment under the old compiler, shifted later fields
and failed matching; it is not used. Grid row/flat views cover the same 64 bytes.

The option prefix at 0806969C contains five observed four-byte records: subtype
count at zero, combo reward at one, final reward at two and follow-up chance at
three. The following animation starts at 080696B0. The old compiler gives the
ordinary four-byte byte-field aggregate alignment four; that is a compiler fact,
not proof of the original source declaration. Five cell palette pointers at
080696C0 precede five 16-byte cell-animation records at 080696D4. Program bytecode
is referenced, not embedded in these C sources. Unchecked indices beyond these
observed prefixes remain unresolved.

## Selection and settlement

Population initializes column heights and the five timers, then creates 64
cells. The accepted bounded RNG produces a subtype within the chosen option's
count. BIOS quotient and remainder map each linear cell index to its two axes;
the constructor uses the corresponding 16-pixel spacing and initial offsets.
Both slot storage and the object's own index are retained.

Pressed A resets marks and starts a recursive four-neighbor walk from the
selected column/row. Matching uses the grid byte's high nibble. Each visited
cell receives a depth-dependent timer, increments selected count, and shifts its
grid byte before recursion, preventing ordinary revisits. Incoming kind/delay
words are explicitly narrowed to byte values; this matches the current callers
and native entry truncations without a conflicting narrow prototype.

A selection of one or fewer cells is cleared. Otherwise marked objects leave the
active slot table, enter phase four and use their timers before the animation and
combo-score updates. Phase one marks expired cells for removal. Phase fourteen
clamps motion at the destination and stops acceleration above the observed
velocity threshold. Equal-neighbor detection and selection clamping have names
that reflect those actual operations, rather than the earlier generic result
and finish labels.

Settlement scans rows downward, records empty-cell shifts, schedules vertical
motion, rebuilds positions into the grid, then compacts surviving columns. The
counter uses both its previous value and stored decremented value. Completing
settlement decides between another selection, a follow-up object and final
reward/sequence selection.

The follow-up object waits for timer wrap to -1, replaces nearby cells and rebuilds
the board. Its replacement loop executes the real palette and animation updates,
then transitions through the finishing animation and removal flag. Separately
consumed neighbor indices and scene-state loads recover the original producer
order; the follow-up callback needs no register binding.

## BIOS and remaining compiler constraints

The existing four-byte quotient wrapper at 0804C8C8 and new eight-byte remainder
wrapper at 0804C8CC invoke BIOS service six. The latter returns R1 through R0 and
includes its original zero alignment. Both remain explicit low-level assembly
with zero C coverage. Finite checks model the signed mathematical service; they
do not run the BIOS or establish hardware behavior.

Only final reward doubling requires two source register variables. Its actual
positive limit uses R0 and its consumed countdown uses R1, both within a call-free
loop. Their live ranges do not overlap in R0. Removing either binding fails the
full 140-byte match in both normal and strict profiles. No instruction body,
extra traffic, output patch or unexplained padding is substituted. Other bodies
use ordinary C and zero section-alignment directives where required.

## Verification limits

All 30 new functions have complete positive and changed-source controls under
normal and strict declaration profiles. The 25 current connected providers add
2,664 previously accepted C bytes to the proof context, with no new credit.
Physical layout/type checks compile the actual definitions, and wrong widths,
signedness, callback arity and parameter domains are rejected.

Four preserved finite packets contain 2,937 initialized cases, 1,160 genuine
changed-source divergences, 16 interpreter/input rejections and eight composition
chains. Later packets execute every local body and six accepted providers,
including real population, construction, recursive selection and follow-up
chains. They check memory, call effects, returns and callee-save/stack behavior.
Thirteen oversized-subtype cases are numeric native/API diagnostics; they do not
establish valid C resource-array bounds. All other fixture claims retain their
stated initialized-memory, coordinate, shift and allocation preconditions.

Underlying allocation, random, display, palette, audio and animation effects
remain explicit finite hooks where their actual bodies are not executed. No
whole-game, hardware-interleaving or protocol claim follows. Original data stays
local, and the full ROM still includes explicit unconverted regions. The next
connected work lies in adjacent activity definitions and the shared renderer and
finalizer; their current failed source attempts receive no C credit.
