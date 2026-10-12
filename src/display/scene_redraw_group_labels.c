#include "display_scene_redraw.h"
void display_scene_redraw_group_labels(unsigned char group)
{
    unsigned char next;
    const char *text;
    if (g_display_scene_objects[13])
        g_display_scene_objects[13]->flags = (g_display_scene_objects[13]->flags & ~1) | 2;
    if (g_display_scene_objects[14])
        g_display_scene_objects[14]->flags = (g_display_scene_objects[14]->flags & ~1) | 2;
    if (g_input_pressed[g_input_config.local_player] & 0x40) {
        next = 1;
        if (group > 0) { next = group; group = next - 1; }
    } else if (group == 5) { next = 5; group = 4; }
    else next = group + 1;
    display_text_select_font(3, 0, 0);
    text = display_scene_lookup_text(g_display_scene_group_text_ids[group]);
    g_display_scene_objects[13] = display_scene_stage_080282d4(0xbf, &text);
    transition_object_set_state((void *)g_display_scene_objects[13], 8);
    text = display_scene_lookup_text(g_display_scene_group_text_ids[next]);
    g_display_scene_objects[14] = display_scene_stage_080282d4(0xc0, &text);
    transition_object_set_state((void *)g_display_scene_objects[14], 8);
}
