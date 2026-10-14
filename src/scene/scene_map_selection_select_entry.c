#include "scene_map_selection.h"
#include "display_motion.h"
#include "save_stream.h"
#include "resource_conditions.h"
#include "frame_scene_motion.h"
#include "display_palette_lifecycle.h"

void scene_map_selection_select_entry(unsigned int index_arg, unsigned int preview_arg)
{
    unsigned char index = index_arg;
    unsigned char preview = preview_arg;
    if (!preview) {
        const char *text;
        if (g_display_scene_frame_objects[0]->position.y>0x500000)
            display_set_background_scroll_target(3, 0, 0, 4);
        else display_set_background_scroll_target(3, 0, 0x700000, 4);
        display_text_select_font(3, 0, 0);
        text = display_scene_lookup_text(index+176);
        if (g_display_scene_frame_objects[0]->position.y>0x500000)
            g_display_scene_frame_objects[3] = display_scene_create_label(164, &text);
        else g_display_scene_frame_objects[3] = display_scene_create_label(165, &text);
        ((struct FrameSceneMotionObject *)g_display_scene_frame_objects[3])->timer = 4;
        transition_object_set_state(g_display_scene_frame_objects[3], 14);
        frame_set_variant_state(g_display_scene_frame_objects[3], 56);
    }
    g_display_scene_frame_objects[2]->unknown_0a = 277+index;
    g_display_scene_frame_objects[2]->id = 137+index;
    g_display_scene_frame_objects[2]->display_palette = g_scene_map_selection_palette_configs[index].bank;
    display_scene_refresh_item(g_display_scene_frame_objects[2]);
    g_display_scene_frame_objects[2]->flags |= 1;
    if (g_display_background_system.backgrounds[0].target_x)
        frame_set_position(g_display_scene_frame_objects[2],
            (g_scene_map_selection_points.rows[index].x<<16)-g_display_background_system.backgrounds[0].target_x,
            (g_scene_map_selection_points.rows[index].y<<16)-g_display_background_system.backgrounds[0].position_y);
    else frame_set_position(g_display_scene_frame_objects[2],
            (g_scene_map_selection_points.rows[index].x<<16)-g_display_background_system.backgrounds[0].position_x,
            (g_scene_map_selection_points.rows[index].y<<16)-g_display_background_system.backgrounds[0].position_y);
    if (g_scene_map_selection_hovered==255) {
        unsigned char bank = g_scene_map_selection_palette_configs[index].bank;
        g_scene_map_selection_palette_block = display_create_palette_sequence(bank<<4,
            g_scene_map_selection_palette_configs[index].count, 10, 0, 29,
            g_scene_map_selection_palettes[g_scene_map_selection_palette_configs[index].resource]+bank*16, 2);
        if (bank==1) {
            g_display_scene_frame_objects[0]->display_palette = 15;
            display_scene_refresh_item(g_display_scene_frame_objects[0]);
        } else {
            g_display_scene_frame_objects[0]->display_palette = 1;
            display_scene_refresh_item(g_display_scene_frame_objects[0]);
        }
    }
}

asm(".align 2, 0");
