# Scene 11 menu and link handoff

Four connected ordinary C functions reconstruct 704 extent bytes at their original
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
It draws text ID 212 and calls the still-original row drawer six times, using an
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
halfword into a word value. Bit 0 calls the original accept provider; bits 6 or 7
call the original row-change provider; bits 1 or 2 call the original cancel
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

All four sources compile without register bindings, added guards, extra memory
traffic or output normalization. Their actual changed-source controls alter the
row-loop limit, cancel mask, cleanup condition and status flag; all are rejected
by full-byte comparison. The 28 directly connected accepted providers and phase
dispatchers, covering 2,040 previously accepted bytes, also pass fresh positives
and their existing real controls. They add no new coverage. The 32 proof pairs
retain 128 native object/linked artifacts and 53 current literal header snapshots;
allocated sections, symbols, original addresses, complete pools and source/header
pins are checked separately from the full-ROM build.

The row drawer at `0x08031DA4` and accept/change/cancel providers at `0x0803165C`,
`0x08031940` and `0x08031C10` remain explicit original dependencies. A row-drawer
candidate has three register differences; an apparently closer tile-register
binding omitted the original save/restore and is excluded. Their raw attempts are
retained privately, with no source credit. Palette interpolation, map writing and
the higher save loader also remain separate unconverted frontiers. These matches
prove compilation/link equality for the stated extents, not gameplay or a complete
inventory of the game.
