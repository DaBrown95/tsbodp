#include "scene_relation_grid.h"

void scene_relation_grid_refresh_entries(void)
{
    unsigned int index, slot_offset;
    struct FrameObject **slot;

    index = 0;
    slot = g_display_scene_frame_objects;
    slot_offset = 0;
    for (; index < 6; slot++, slot_offset += sizeof(struct FrameObject *), index++) {
        unsigned int entry = index + g_scene_request.parameter;
        if (index > 2)
            entry += 9;
        entry = g_scene_relation_grid_indices[entry];
        if (entry <= 23) {
            if (display_menu_relation_initialized(&g_display_menu_relation_values, entry))
                (*slot)->unknown_0a = entry + 239;
            else
                (*slot)->unknown_0a = 226;
            {
                /* This real array address dies in the addition, before the call.
                 * The resulting slot remains live across refresh_item. */
                register unsigned int array_base __asm__("r0") =
                    (unsigned int)&g_display_scene_frame_objects;
                struct FrameObject **refresh_slot =
                    (struct FrameObject **)(slot_offset + array_base);
                display_scene_refresh_item(*refresh_slot);
                (*refresh_slot)->flags |= 1;
            }
        } else {
            (*slot)->flags &= ~1u;
        }
    }
}
asm(".align 2,0");
