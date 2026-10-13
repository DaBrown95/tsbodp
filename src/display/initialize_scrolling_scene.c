#include "display_scene_setup.h"
void display_initialize_scrolling_scene(void)
{
    unsigned int control;
    const struct BackgroundResource *palette;
    g_display_scene_request_state.mode = 0;
    display_set_mode(0);
    display_enable_layers(0x1000);
    display_show_background(3, g_display_scrolling_layer_control2);
    display_show_background(1, g_display_scrolling_layer_control1);
    display_fill_background(1, 0);
    control = g_display_scrolling_layer_control0;
    display_show_background(0, control);
    display_fill_background(0, 0);
    display_text_set_background_control(control);
    display_load_background(3, &g_display_scrolling_resource3, 0, 1, 0, 0);
    display_load_background(1, &g_display_scrolling_resource1, 1, 2, 0, 0);
    palette = &g_display_scrolling_palette;
    display_load_resource_palette(palette, 0);
    display_load_palette_alternate((const unsigned char *)palette + 2, 0, 16);
    display_set_background_velocity(3, 0x10000, 0x10000);
    g_display_scene_request_state.scene = 0;
    g_display_scene_request_state.parameter = 0;
    g_display_scene_byte1 = 0;
    g_display_scene_byte0 = 0;
    display_scene_stage_0800f168();
    display_scene_stage_0800f034(0);
    display_scene_redraw_details(0);
    g_display_scene_byte2 = 0;
    display_scene_stage_0800f478();
    g_display_scene_owner_link.owner->flags &= ~1;
    g_display_scene_request_state.unknown_10 = 0;
    g_display_scene_request_state.unknown_14 = 4;
}
