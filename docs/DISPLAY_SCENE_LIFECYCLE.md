# Scrolling scene object and tile lifecycle

Ten connected functions add 460 bytes of matching C. Every complete linked
extent matches at its original address, including pools and alignment, and
all ten actually compiled changed-source controls reject. This closes the
label factory and resource handoff used by the [scene selector](DISPLAY_SCENE_SETUP.md),
its pointer-table cleanup and scene shutdown, and the text object's connection
to the already reconstructed tile allocator.

| Function | ROM address | Verified bytes |
| --- | --- | ---: |
| `display_scene_create_label` | `0x080282D4` | 76 |
| `display_scene_refresh_item` | `0x08028320` | 24 |
| `display_scene_retire_object_slot` | `0x08028338` | 40 |
| `display_scene_clear_object_slots` | `0x08028360` | 24 |
| `display_release_object_list` | `0x08001188` | 48 |
| `display_scene_close` | `0x0800F368` | 36 |
| `display_scene_clear_detail_background` | `0x0800F38C` | 16 |
| `display_allocate_text_object` | `0x080450A0` | 124 |
| `display_allocate_object_tiles` | `0x08001304` | 40 |
| `display_release_tile_bytes_immediately` | `0x08047904` | 32 |

## Connected calls and partial data views

The label factory calls the reconstructed text allocator, installs the shared
`frame_scene_object_tick` callback, assigns subtype `0x13B` and the supplied
ID, sets variant zero, and positions the label through the reconstructed
`frame_set_centered_integer_position`. It uses the same eight-byte position
table at `0x08057ACC` as `frame_create_scene_object`. The item refresh selects
a 16-byte variant resource by the object's subtype from the same table at
`0x08058154` and calls `frame_set_animation_record`. Neither wrapper adds
resource-index checks or handles an allocation failure.

The text allocator calls the still-unconverted `frame_allocate_object(24)`.
It sets flags to nine, forced visibility to one, the observed tile-size bit
to zero, OAM layer/palette to zero, the ten-bit tile field from the allocated
index, and the two attribute bits at `0xD1:6..7` to one. It calls the still-
unconverted text update at `0x080451A8`. The existing `FrameObject` view's
halfword tile field matches this assignment naturally; the separate wider
`FrameOam` field view produced a nonmatching register copy. This is evidence
for the compiler's access view, not proof of the original declaration.

The pointer-table aliases `g_display_scene_objects` and
`g_display_scene_frame_objects` both address `0x030043B0`. The first exposes
the selector's small object prefix; the second uses the frame object's
resource fields. Their declarations remain unsized. Creation observes fifteen
slots; the clear routine writes slots zero through sixteen, establishing a
17-slot accessed prefix without proving the complete allocation. Retirement
clears flag mask one, sets mask two on a nonnull selected object, then clears its
slot. Its supplied index is unchecked. Clearing the table alone does not
destroy the referenced objects.

Linked-object release captures each object's next pointer before calling
`frame_remove_object`. After the walk, including for an empty list, it sets
`g_frame_release_immediately` at `0x030017CC` to one and calls `frame_schedule`
on the primary list at `0x030024F0` with display updates enabled. It does not
restore the old flag or set it before the initial walk. This preserves the
existing deferred-removal versus immediate-removal behavior and the following
schedule pass. Scene close calls transition family two with selector `0x3F`,
uses this release path, resets the display, calls the explicit unconverted
palette lifecycle routine at `0x080117BC`, then clears the pointer slots.

The object tile wrapper forwards the object's byte count and tile-size bit to
`display_allocate_tile_bytes` and stores the low halfword result as its index,
including the allocator's failure value. The immediate release wrapper shifts
the byte count by five or six for nonzero/zero tile-size flags, narrows the
count to a halfword, and calls the reconstructed allocated-mask release at
`0x080479E4`. Its immediate target is distinct from the deferred free-mask
handoff at `0x08047A3C`. These dependencies connect text layout and scene
objects to the copied ARM allocator and frame/VBlank transfer path; the text
layout and drawing bodies themselves remain unconverted.

## Comparison evidence and limits

The ignored receipt index is
`reports/agents/display_audio/background_motion/scene/redraw/lifecycle-ready.json`.
The public sources and their literal header closures were compiled after
promotion. Controls change subtype `0x13B` to `0x13A` (72 bytes versus 76,
50 differing/missing/extra bytes), resource index by one, retirement flag two
to four, clear-loop upper index sixteen to fifteen, release mode one to two,
transition selector `0x3F` to `0x3E`, and the background-clear index zero to
one. The latter six controls each reject by one byte. The text allocator's
flags nine to seventeen reject by two bytes; increasing the tile byte argument
by 32 rejects by 26 bytes; inverting the tile-size branch rejects by one byte.

All ten bodies use ordinary semantic C without fixed register constraints.
The tile allocation/release wrappers and pool-free background clear have
explicit zero-filled alignment directives, two bytes each, kept separate from
their C bodies. There are no embedded instruction bodies or output patches.
Earlier pointer, bitfield, count-type and ordering failures, raw comparisons
and source/header snapshots remain local. Extent matching, integrated full-ROM
equality and runtime/gameplay behavior remain separate claims.
