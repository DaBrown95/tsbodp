#include "frame.h"
#include "scene_link_menu.h"

void scene_link_menu_initialize(void)
{
    struct SceneRequest *request = &g_scene_request;
    struct FrameObject *object;
    unsigned int control;
    unsigned char row;

    request->scene = 0;
    request->unknown_10 = 0;
    display_set_mode(0);
    display_enable_layers(0x1000);
    display_show_background(0, g_scene_link_menu_background0_control);
    display_show_background(1, g_scene_link_menu_background1_control);
    display_fill_background(0, 0);
    display_fill_background(1, 0);
    control = g_scene_link_menu_background2_control;
    display_show_background(2, control);
    display_fill_background(2, 0);
    display_text_set_background_control(control);
    display_text_select_font(3, 0, -1);
    display_load_background(0, &g_scene_link_menu_background0, 0, 1, 0, 0);
    display_load_background(1, &g_scene_link_menu_background1, 0, 2, 0, 0);
    display_load_resource_palette(&g_display_menu_palette_resource, 0);
    display_set_background_velocity(0, 65536, 65536);
    object = frame_create_scene_object(176, 314, 1, 1);
    g_display_scene_frame_objects[0] = object;
    object->flags &= ~0x10;
    display_text_draw_line(385, 120, 4, display_scene_lookup_text(212), 1);
    row = 0;
    do {
        scene_link_menu_draw_row(row, request->scene);
        ++row;
    } while (row <= 5);
    if (g_link_flags & 0x8000)
        scene_link_menu_draw_status();
    transition_run_first(63, 0);
}
asm(".align 2,0");
