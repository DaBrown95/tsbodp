#include "display_scene_redraw.h"
void display_scene_create_objects(void)
{
    signed char i;
    const char *text;
    g_display_scene_objects[0] = (void *)frame_create_scene_object(0xb1, 0xb, 1, 1);
    g_display_scene_objects[1] = (void *)frame_create_scene_object(0xb3, 0xa, 1, 1);
    g_display_scene_objects[2] = (void *)frame_create_scene_object(0xb4, 0x10d, 2, 1);
    g_display_scene_objects[2]->flags &= ~1;
    g_display_scene_objects[3] = (void *)frame_create_scene_object(0xb5, 0x10c, 2, 1);
    g_display_scene_objects[4] = (void *)frame_create_scene_object(0xb6, 0x10d, 2, 1);
    g_display_scene_objects[5] = (void *)frame_create_scene_object(0xb7, 0x10c, 2, 1);
    for (i = 3; i >= 0; --i)
        g_display_scene_objects[i + 6] = (void *)frame_create_scene_object(i + 0xb8, 0xe2, i + 3, 0);
    display_text_select_font(3, 0, 0);
    text = display_scene_lookup_text(0x24);
    g_display_scene_objects[10] = display_scene_stage_080282d4(0xbc, &text);
    transition_object_set_state((void *)g_display_scene_objects[10], 8);
    text = g_display_scene_text_state.buffer;
    g_display_scene_objects[11] = display_scene_stage_080282d4(0xbd, &text);
    transition_object_set_state((void *)g_display_scene_objects[11], 8);
    display_scene_stage_0801b1cc(g_display_scene_text_state.text_id);
    text = display_scene_lookup_text(0x25);
    g_display_scene_objects[12] = display_scene_stage_080282d4(0xbe, &text);
    transition_object_set_state((void *)g_display_scene_objects[12], 8);
    text = display_scene_lookup_text(g_display_scene_group_text_ids[0]);
    g_display_scene_objects[13] = display_scene_stage_080282d4(0xbf, &text);
    transition_object_set_state((void *)g_display_scene_objects[13], 8);
    text = display_scene_lookup_text(g_display_scene_group_text_ids[1]);
    g_display_scene_objects[14] = display_scene_stage_080282d4(0xc0, &text);
    transition_object_set_state((void *)g_display_scene_objects[14], 8);
}
