#include "scene_relation_grid.h"
#include "save_world_display.h"

void scene_relation_grid_draw_relation(struct FrameObject *object,
    unsigned int tile, struct SceneRelationGridTextPoint point,
    unsigned int entry)
{
    int relation = display_menu_read_relation(&g_display_menu_relation_values, entry);
    /* Each low-halfword conversion lives in R1 only until the scale call. */
    if (relation > 0) {
        register unsigned int percent __asm__("r1") = (unsigned int)save_world_ratio_percent(relation, 100) << 16;
        percent >>= 16;
        frame_set_animation_frame((struct FrameTickObject *)object,
            (FrameU8)(save_world_scale_percent(10, percent) + 10));
    } else {
        register unsigned int percent __asm__("r1") = (unsigned int)save_world_ratio_percent(relation, -100) << 16;
        percent >>= 16;
        frame_set_animation_frame((struct FrameTickObject *)object,
            (FrameU8)(10 - save_world_scale_percent(10, percent)));
    }
    display_text_select_font(0, 0, -1);
    display_text_number_field_zero(relation);
    display_text_draw_line(tile, point.x, point.y,
        display_scene_lookup_text(6222), 2);
    display_text_copy_field_zero((const char *)g_scene_relation_grid_world.bytes);
}

asm(".align 2,0");
