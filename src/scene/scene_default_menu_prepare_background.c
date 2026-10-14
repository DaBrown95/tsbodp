#include "scene_default_menu.h"

void scene_default_menu_prepare_background(void)
{
    display_show_background(1, g_scene_default_menu_control2);
    display_fill_background(1, 0);
    display_load_background(1, &g_scene_default_menu_slot_background, 1, 0, 0, 0);
    display_load_background_dma(1,
        g_scene_default_menu_slot_text_backgrounds[display_text_selected_bank()],
        501, 0, 11, 1);
    display_show_background(2, g_scene_default_menu_control_detail);
    display_load_background_dma(2, &g_scene_default_menu_detail_background,
        455, 0, 0, 0);
    display_show_background(0, g_scene_default_menu_control0);
    display_load_resource_palette(&g_scene_default_menu_palette, 0);
    g_scene_request.unknown_10 = 1;
    g_scene_default_menu_selector = frame_create_scene_object(167, 313, 1, 1);
}
