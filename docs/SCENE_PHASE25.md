# Scene phase row 25

The observed 12-byte row at ROM `0x57AA8` installs begin `0x0804694D`,
step `0x08046A69` and end `0x08046D8D`. The step callback directly calls
the object setup at `0x08046B8D`. Names are provisional; the existing callback
consumer uses `void (void)`, and historical unused formals remain unestablished.

| Source owner | ROM range | Extent | Instructions | Literals | Switch data | Alignment |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| `scene_phase25_initialize` | `0x4694C..0x46A68` | 284 | 234 | 48 | 0 | 2 |
| `scene_phase25_step` | `0x46A68..0x46B8C` | 292 | 214 | 52 | 20 | 6 |
| `scene_phase25_initialize_objects` | `0x46B8C..0x46D8C` | 512 | 444 | 64 | 0 | 4 |
| `scene_phase25_shutdown` | `0x46D8C..0x46DD0` | 68 | 56 | 12 | 0 | 0 |
| Total | `0x4694C..0x46DD0` | 1,156 | 948 | 176 | 20 | 12 |

These four extents were already mapped. Source ownership adds no newly
discovered executable code or runtime/gameplay evidence. The fixed historical
319,640-byte comparison remains separate from the current mapped denominator.

## Actual behaviour and interfaces

The initializer configures backgrounds, selects a palette bank from the existing
resource-game-state byte, and draws text resource 303 through the seven-argument
`display_text_draw` interface. Both the text pointer and remaining limit are
addressed and may change at that call. The direct draw provider at `0x1A7C8`
is already owned; its downstream rasterizer at `0x1AA78` remains unconverted.
The callback starts transition 63, clears the request phase and timer, and saves
the current sample-volume byte to `0x03002248`.

The step callback advances transient effects, dispatches only phases 0 through
4, and performs a fresh full-word timer increment after the dispatch. Confirm
input starts the object setup and cue 180. The later phases test variant state
11, set slot 1's `flags |= 1` at timer 20, start slot 0's position move at timer 30, and submit
request `(1, 4, 6)`. The halfword timer store/reload at the move is preserved.

The setup uses the existing actor, scene-player, transient-effect, background
and scene-object owners. Its two ordinary pointer captures correspond to the
actual native flags/size/enabled and direction phases. Later pointer observations
remain fresh. No binding, qualifier, calling-convention or provider-type change
is introduced. Allocation and resource preparation retain the original call and
store order, including the nullable transient effect and transition 63.

The shutdown starts the second transition, clears indexed audio channels and
passes the **current** options byte at `AudioGameOptions + 8` to the sample-volume
setter. It does not read the initializer's saved byte, so this path establishes
no restoration of that snapshot. It conditionally destroys the transient effect,
releases the primary object list and resets display, palette jobs and object slots.

## Conditional domains

Actual providers and separate compilation contexts establish the local
interfaces. They do not prove all possible incoming states or writes. In
particular:

- The initializer's background palette is 512 bytes. Its bank expression stays
  within that palette for state indices 0 through 12; the unsigned-byte field
  alone does not establish this bound. This is the same byte as appearance-prefix
  offset 1 at `g_frame_scene_player_group`, read by the existing group palette
  provider. Both accesses use existing compatible unsigned-byte storage views.
  Text selection, variable resource tails,
  live text/limit backing and loop progress remain premises.
- `FrameScenePlayerGroup` is an existing partial mode view. Palette and binding
  providers consume a readable seven-byte appearance prefix; its one-byte
  `sizeof` is not an allocation-size claim. Actor allocation is 320 bytes while
  the current partial actor view covers 312. The nullable transient allocation
  is 72 bytes.
- The setup needs scene-object slots 0 and 1. The existing shutdown slot-clearing
  provider writes slots 0 through 16, requiring 17 writable slots. Allocation,
  object/list lifetimes, animation and resource indices, direction tables,
  transient groups, input-player selection and later writers remain conditional.
- Row 25 and the five-case switch identify these local edges. Complete selector,
  writable callback, backing and executable-target populations remain open.

## Qualification

All four definitions pass normal and strict compilation with the shared header.
The eight genuine controls change font 12 to 11, cue 180 to 181, variant 56 to 55
and transition 63 to 62; each rejects the complete extent by one byte. Actual
unchanged definitions of 43 direct providers retain their current normal
positive/control proofs and separate compilation contexts; no new provider
strict result is claimed. The setup is one of the four freshly qualified
definitions. The downstream original text rasterizer receives no source credit.

Strict checks caught missing includes for the existing DMA and second-transition
declarations in the two new callbacks. Adding the existing canonical provider
header repairs their actual declaration contexts without changing provider
headers, interfaces or emitted bytes. Earlier incomplete contexts are retained
as failed diagnostics. Independent source, native extent, interface and control
review precedes adoption. The coherent `make progress` gate verifies all current
source replacements and controls, fixed-ROM equality, inventory and treemap.
