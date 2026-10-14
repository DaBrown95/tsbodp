# Scene 11 menu and link handoff

Nine connected C functions reconstruct 2,688 extent bytes at their original
USA/Europe revision-0 ROM addresses. The scene's initializer, input callback and
shutdown connect background setup, text drawing, local input, recorded link events
and the existing display/object/audio cleanup paths. `scene_link_menu` is an
inferred name for this coordination; no extracted menu text or assets are published.

| Function | ROM address | Extent bytes |
| --- | --- | ---: |
| `scene_link_menu_initialize` | `0x08031458` | 296 |
| `scene_link_menu_step` | `0x08031580` | 220 |
| `scene_link_menu_shutdown` | `0x08031D64` | 64 |
| `scene_link_menu_draw_status` | `0x08031E48` | 124 |
| `scene_link_menu_accept` | `0x0803165C` | 740 |
| `scene_link_menu_change_row` | `0x08031940` | 720 |
| `scene_link_menu_cancel` | `0x08031C10` | 340 |
| `scene_link_menu_draw_row` | `0x08031DA4` | 164 |
| `display_enable_background` | `0x0800D5C8` | 20 |

The existing phase table at `0x0805797C` contains row 11's three Thumb pointers
`0x08031459`, `0x08031581` and `0x08031D65`. The reconstructed begin, step and end
dispatchers index that same table. This establishes a static incoming connection,
not a runtime trace or the meaning of every row. Each replacement includes its
complete pools and alignment: initialization ends at the input entry, the input
body has two zero alignment bytes before the independent `0x0803165C` entry,
shutdown ends at the row drawer, and the status drawer ends at the independent
`BX LR` leaf at `0x08031EC4`. That four-byte leaf, including its own alignment,
remains original.

## State and connected behavior

Initialization clears the request words at offsets 8 and 16, configures display
mode 0 and three backgrounds, installs the background-2 control in the text raster
state, selects font 3, loads two background resources and the existing menu palette,
then sets background 0's velocity to `(65536, 65536)`. It creates an object with
kind 176 and subtype 314, stores it in shared scene-object slot zero and clears its
flag `0x10`. The returned pointer is unchecked, matching the original accesses.
It draws text ID 212 and calls the connected row drawer six times, using an
unsigned byte counter. The observed six iterations do not prove the resource
tables' capacities or valid arbitrary row arguments.

The existing six-word `SceneRequest` view at `0x03004350` is retained. Its word at
offset 8 is used here as a selected row; word 16 controls the menu input state, and
shutdown writes the full word `-1` at offset 12. These are overlapping access roles,
not newly established storage ownership or a complete state layout. The three
control words at `0x08069570..0x08069578` and two background resource roots remain
read-only symbols with unknown bounds. The palette resource and object-pointer
table reuse their already established aliases and addresses.

If the game flag `0x20` is set, the step calls the existing link coordinator and
explicitly consumes its low return byte before comparing with one. A completed
handoff clears the same game flag, changes request word 16 from two to zero if
needed, and redraws status. Otherwise it records kind 1 with payload word zero,
then tests link flags `0x2000` and `0x4000` separately. If both are set, it submits
kind 1 in mode 2 with the existing world argument and clears those two flags after
the call. The established volatile link-word declaration preserves the original
separate reads; this is not an independent concurrency or hardware-behavior proof.

Only the first four bytes of the aligned eight-byte event payload are initialized.
The second word is transported through the existing by-value interface without
new initialization. The accepted kind-1 recorder ignores both payload words and
initializes its own record to zero; the second input word remains unwritten here.
This documents the observed native storage and selected-callee access; it does not claim a defined
second-word value, portable behavior for all uses, or runtime safety. The matching
source preserves that limitation rather than inventing a payload value.

When request word 16 is not two, the callback reads the local player's pressed
halfword into a word value. Bit 0 calls the accept provider; bits 6 or 7
call the row-change provider; bits 1 or 2 call the cancel
provider. The last test keeps an ordinary scoped mask result, matching the native
temporary without extra reads or register constraints. The local-player index
and underlying providers remain unchecked in this callback.

The status drawer first clears a background-2 rectangle, then selects text ID
222 when link flag `0x8000` is set and ID 223 otherwise. Both paths select font 3,
color 3 and draw at `(120, 136)`. Shutdown runs transition `(63, 12)`, releases the
primary object list, resets display and palette jobs, clears scene-object slots and
the alternate indexed audio channels, then clears retained display only when the
queued request kind is five. The provider names and bodies stay canonical at their
existing addresses.

## Verification and remaining boundary

The four callbacks compile without register bindings, added guards, extra memory
traffic or output normalization. Their actual changed-source controls alter the
row-loop limit, cancel mask, cleanup condition and status flag; all are rejected
by full-byte comparison. The action batch below adds five current positives and
real controls. Thirty-four connected accepted providers and phase dispatchers,
covering 2,528 bytes, also pass fresh positives and their existing real controls.
They and the four 704-byte callbacks add no new coverage in this batch. The 43
proof pairs retain 172 native object/linked artifacts and 56 current literal
header snapshots. A separate declaration diagnostic adds 20 native artifacts
without changing the acceptance compiler profile. Allocated sections, symbols,
original addresses, complete pools and source/header pins are checked separately
from the full-ROM build.

The following independent four-byte leaf stays original. Palette interpolation,
map writing and the higher save loader also remain separate unconverted frontiers.
These matches prove compilation/link equality for the stated extents, not gameplay
or a complete inventory of the game. The direct action path below is a further
connected 1,984-byte source boundary; useful failed predecessors remain private.

## Direct menu actions and row presentation

This connected batch closes the accept, row-change, cancel and row-drawing
providers called by the scene-11 callbacks, plus their background-enable wrapper.
It adds five complete C extents totaling 1,984 bytes. Combined with the four
704-byte callbacks, this path covers nine functions and 2,688 bytes; this is a
connected source boundary, not a complete UI, network or game inventory.

| Function | ROM address | Extent bytes |
| --- | --- | ---: |
| `scene_link_menu_accept` | `0x0803165C` | 740 |
| `scene_link_menu_change_row` | `0x08031940` | 720 |
| `scene_link_menu_cancel` | `0x08031C10` | 340 |
| `scene_link_menu_draw_row` | `0x08031DA4` | 164 |
| `display_enable_background` | `0x0800D5C8` | 20 |

The accept, change and cancel extents end at their next independent entries.
The row drawer ends at the existing status drawer, and the 20-byte enable wrapper
ends at the accepted hide wrapper. All five own their complete literal pools;
none requires a trailing allocation beyond its function symbol. The accept jump
table at `0x0803177C` is data inside its 740-byte extent. Its six destinations,
in index order, are `0x08031794`, `0x0803179C`, `0x080317A4`, `0x080317C4`,
`0x080317AC` and `0x080317D0`. Those targets establish that row three submits kind
six, while row four writes eleven to the word at `0x03004340` and submits kind
seven. The physically earlier case-four body does not change that index order.
An earlier semantic draft reversed these two cases and is retained as a failed
attempt. The new selector-word name is neutral; only this full-word write and
fixed address are established.

The row drawer selects font three with color three for the selected row and zero
otherwise, then reads request word 16. Mode one chooses text IDs `row + 210`,
tile `64 * (row + 1) + 1` and coordinates `(120, 22 * row + 44)`. Other modes choose
text IDs `row + 213`, tile `64 * row + 1` and y position `22 * row + 28`, or
`22 * row + 64` when game flag `0x20` or link flag `0x8000` is set. Text and object
pointers remain unchecked. The callers' observed rows do not establish arbitrary
row validity or resource-table capacities.

Accept in mode one either returns to mode zero and redraws six rows, reenables
background one, sets object-slot zero's flag one and resets palette jobs, or
submits default request five when the parameter is zero. In the other mode,
rows zero through two submit default requests 22, 18 and 24. Row three submits
kind six in mode zero using request word zero. Row four performs the selector
write and submits kind seven in mode one. Row five enters mode one with parameter
one, hides background one, clears the object's flag one, draws text 219 and the
two choices, then loads the already accepted palette-range configuration at
`0x08052E30`. Every path plays cue one; no default switch arm is added.

Row change uses the accepted local vertical-pressed helper with the actual local
player byte. Mode one updates parameter between zero and one, and the other mode
updates the selected-row word between zero and five. It redraws the old and new
rows. After the second redraw, a fresh selected-row snapshot controls the cursor
position: x is `121 * 65536`, and y is `33 * 65536 + row * 22 * 65536` for rows at
most five, otherwise `33 * 65536`. This integer representation follows the native
16.16 coordinate calculations; no additional range check is inserted.

Cancel in mode one performs the same six-row return and palette-job reset.
Otherwise, with link flag `0x8000` clear, game flag `0x20` changes the request mode
to two and redraws status; without that game flag it submits kind one in mode two
with the existing world word. With link flag `0x8000` set it plays cue three.
All paths then play cue two. Link flag reads retain the existing volatile storage
view; these static accesses do not prove concurrency or gameplay behavior.

The enable wrapper forms the background layer mask from the complete unsigned
index argument and calls the existing layer-enable provider, matching its original
20 bytes. The observed call here uses index one. Neither the source nor native
body adds a valid-index guard, and no portable behavior for arbitrary shift counts
is claimed.

## Source and verification limits for the action batch

Accept, cancel and the enable wrapper are ordinary C without register bindings.
Row change and the standalone row drawer retain one real unsigned mode value in
callee-saved R6. It is assigned after the font call, supplies the mode-one draw
style and may live across the real text lookup and draw calls. The inline helper's
same binding in row change is local to each meaningful draw phase. No caller-saved
bound value survives a call, and there are no extra reads, dummy initialization,
output normalization or synthetic constraints. Unbound alternatives and the unsafe
tile-binding predecessor remain private and excluded.

Each new replacement has an actual changed-source control: row-limit reduction,
input upper-bound reduction, cue change, y-offset change and layer-mask change.
Every control differs by one byte over the full owned extent. Fresh canonical
caller/header positives and actual controls cover the complete five extents and
fixed Thumb addresses. A separate implicit-declaration warning-as-error diagnostic
compile is recorded outside the unchanged acceptance compiler profile. Runtime behavior, text meanings, object/table capacities,
network completion and the independent following leaf remain outside these claims.
