#include "scene_row24_selection_private.h"

void scene_row24_selection_refresh_original(void)
{
    const char *text;
    unsigned int scene, value;

    g_display_scene_frame_objects[12]->flags =
        (g_display_scene_frame_objects[12]->flags & ~1U) | 2;
    g_display_scene_frame_objects[13]->flags =
        (g_display_scene_frame_objects[13]->flags & ~1U) | 2;
    g_display_scene_frame_objects[0]->id = g_scene_request.scene + 197;
    frame_set_variant_state(g_display_scene_frame_objects[0], 58);
    text = display_scene_lookup_text(
        g_scene_row24_selection_first_text_ids[g_scene_request.scene]);
    g_display_scene_frame_objects[12] = display_scene_create_label(206, &text);
    transition_object_set_state(g_display_scene_frame_objects[12], 8);
    value = g_contact_action_world.values[
        g_scene_row24_selection_value_permutation[scene = g_scene_request.scene]];
    text = display_scene_lookup_text(
        g_scene_row24_selection_second_text_ids[scene] + value);
    g_display_scene_frame_objects[13] = display_scene_create_label(207, &text);
    transition_object_set_state(g_display_scene_frame_objects[13], 8);
    scene_row24_selection_draw_content_original();
}
