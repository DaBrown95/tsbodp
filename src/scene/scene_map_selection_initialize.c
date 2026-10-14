#include "scene_map_selection.h"
#include "display_motion.h"
#include "save_stream.h"
#include "resource_conditions.h"
#include "frame_scene_motion.h"
#include "display_palette_lifecycle.h"

void scene_map_selection_initialize(void)
{
    display_set_mode(0);
    display_enable_layers(0x1000);
    display_show_background(0, g_scene_map_selection_control0);
    display_fill_background(0, 0);
    display_load_background_dma(0, &g_scene_map_selection_background0, 0, 0, 0, 0);
    display_show_background(1, g_scene_map_selection_control1);
    display_load_background_dma(1, &g_scene_map_selection_background1, 452, 0, 0, 0);
    display_show_background(2, g_scene_map_selection_control2);
    display_fill_background(2, 0);
    display_load_background_dma(2, &g_scene_map_selection_background2, 1, 0, 0, 0);
    display_show_background(3, g_scene_map_selection_control3);
    display_fill_background(3, 0);
    display_load_background_dma(3, &g_scene_map_selection_background3, 238, 0, 0, 0);
    display_set_background_position(3, 0, 0x100000);
    display_load_palette((const unsigned char *)&g_scene_map_selection_background0+2, 0, 256);
    display_load_palette_alternate(g_display_menu_palette_data, 0, 16);
    g_scene_map_selection_hovered = 255;
    g_scene_map_selection_mode = 0;
    if ((g_save_stream_state.header.words[6]&2) && (unsigned char)condition_is_active(3, 0, 0))g_scene_map_selection_mode = 3;
    else if (g_save_stream_state.header.words[6]&2)g_scene_map_selection_mode = 2;
    else if ((unsigned char)condition_is_active(3, 0, 0))g_scene_map_selection_mode = 1;
    scene_map_selection_initialize_objects();
    display_set_background_scroll_target(0, g_display_background_system.backgrounds[0].position_x+(g_scene_map_selection_origin_x<<16), g_display_background_system.backgrounds[0].position_y, 1);
    display_set_background_scroll_target(1, g_display_background_system.backgrounds[1].position_x+(g_scene_map_selection_origin_x<<16), g_display_background_system.backgrounds[1].position_y, 1);
    display_set_background_scroll_target(2, g_display_background_system.backgrounds[2].position_x+(g_scene_map_selection_origin_x<<16), g_display_background_system.backgrounds[2].position_y, 1);
    transition_run_first(63, 0);
}

asm(".align 2, 0");
