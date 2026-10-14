#include "scene_map_selection.h"
#include "display_motion.h"
#include "save_stream.h"
#include "resource_conditions.h"
#include "frame_scene_motion.h"
#include "display_palette_lifecycle.h"
#include "input.h"

void scene_map_selection_step(void)
{
    if (g_input_current[g_input_config.local_player]&0x20) {
        scene_map_selection_collapse_details();
        if (g_display_scene_frame_objects[0]->position.x>0x50000
            && g_display_background_system.backgrounds[0].position_x<=(int)(g_scene_map_selection_limits[g_scene_map_selection_mode].first<<16))
            frame_set_position(g_display_scene_frame_objects[0], g_display_scene_frame_objects[0]->position.x-0x20000, g_display_scene_frame_objects[0]->position.y);
        else if (g_display_scene_frame_objects[0]->position.x>0x780000
            && g_display_background_system.backgrounds[0].position_x>=(int)(g_scene_map_selection_limits[g_scene_map_selection_mode].last<<16))
            frame_set_position(g_display_scene_frame_objects[0], g_display_scene_frame_objects[0]->position.x-0x20000, g_display_scene_frame_objects[0]->position.y);
        else if (g_display_background_system.backgrounds[0].position_x>(int)(g_scene_map_selection_limits[g_scene_map_selection_mode].first<<16)) {
            display_set_background_scroll_target(0, g_display_background_system.backgrounds[0].position_x-0x20000, g_display_background_system.backgrounds[0].position_y, 1);
            display_set_background_scroll_target(1, g_display_background_system.backgrounds[1].position_x-0x20000, g_display_background_system.backgrounds[1].position_y, 1);
            display_set_background_scroll_target(2, g_display_background_system.backgrounds[2].position_x-0x20000, g_display_background_system.backgrounds[2].position_y, 1);
            frame_set_position(g_display_scene_frame_objects[1], g_display_scene_frame_objects[1]->position.x+0x20000, g_display_scene_frame_objects[1]->position.y);
        }
    } else if (g_input_current[g_input_config.local_player]&0x10) {
        scene_map_selection_collapse_details();
        if (g_display_scene_frame_objects[0]->position.x<=0xe8ffff
            && g_display_background_system.backgrounds[0].position_x>=(int)(g_scene_map_selection_limits[g_scene_map_selection_mode].last<<16))
            frame_set_position(g_display_scene_frame_objects[0], g_display_scene_frame_objects[0]->position.x+0x20000, g_display_scene_frame_objects[0]->position.y);
        else if (g_display_scene_frame_objects[0]->position.x<=0x77ffff
            && g_display_background_system.backgrounds[0].position_x<=(int)(g_scene_map_selection_limits[g_scene_map_selection_mode].first<<16))
            frame_set_position(g_display_scene_frame_objects[0], g_display_scene_frame_objects[0]->position.x+0x20000, g_display_scene_frame_objects[0]->position.y);
        else if (g_display_background_system.backgrounds[0].position_x<(int)(g_scene_map_selection_limits[g_scene_map_selection_mode].last<<16)) {
            display_set_background_scroll_target(0, g_display_background_system.backgrounds[0].position_x+0x20000, g_display_background_system.backgrounds[0].position_y, 1);
            display_set_background_scroll_target(1, g_display_background_system.backgrounds[1].position_x+0x20000, g_display_background_system.backgrounds[1].position_y, 1);
            display_set_background_scroll_target(2, g_display_background_system.backgrounds[2].position_x+0x20000, g_display_background_system.backgrounds[2].position_y, 1);
            frame_set_position(g_display_scene_frame_objects[1], g_display_scene_frame_objects[1]->position.x-0x20000, g_display_scene_frame_objects[1]->position.y);
        }
    } else if (g_input_current[g_input_config.local_player]&0x40) {
        scene_map_selection_collapse_details();
        if (g_display_scene_frame_objects[0]->position.y>0x80000)
            frame_set_position(g_display_scene_frame_objects[0], g_display_scene_frame_objects[0]->position.x, g_display_scene_frame_objects[0]->position.y-0x20000);
    } else if (g_input_current[g_input_config.local_player]&0x80) {
        scene_map_selection_collapse_details();
        if (g_display_scene_frame_objects[0]->position.y<=0x98ffff)
            frame_set_position(g_display_scene_frame_objects[0], g_display_scene_frame_objects[0]->position.x, g_display_scene_frame_objects[0]->position.y+0x20000);
    } else if (g_input_pressed[g_input_config.local_player]&1) {
        if ((unsigned char)scene_map_selection_collapse_details()) {
            unsigned char index = scene_map_selection_entry_under_cursor();
            if (index != 255)
                scene_map_selection_select_entry(index, 0);
        }
    } else if (g_input_pressed[g_input_config.local_player]&2) {
        if ((unsigned char)scene_map_selection_collapse_details())
            scene_submit_default_request(11);
    }
    {
        unsigned char index = scene_map_selection_entry_under_cursor();
        if (index!=255 && g_scene_map_selection_hovered==255) {
            scene_map_selection_select_entry(index, 1);
            g_scene_map_selection_hovered = index;
        } else if (index==255 || index!=g_scene_map_selection_hovered) {
            g_scene_map_selection_hovered = 255;
            if (g_display_scene_frame_objects[2] && g_scene_map_selection_palette_block<=11) {
                display_remove_palette_block(g_scene_map_selection_palette_block);
                g_display_scene_frame_objects[2]->flags &= ~1U;
            }
        } else if (g_display_scene_frame_objects[2]->flags&1) {
            int target = g_display_background_system.backgrounds[0].target_x;
            int current = g_display_background_system.backgrounds[0].position_x;
            int x = g_scene_map_selection_points.rows[g_scene_map_selection_hovered].x<<16;
            if (!target)
                target = current;
            frame_set_position(g_display_scene_frame_objects[2], x-target, g_display_scene_frame_objects[2]->position.y);
        }
    }
}

asm(".align 2, 0");
