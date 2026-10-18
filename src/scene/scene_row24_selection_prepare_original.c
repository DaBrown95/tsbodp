#include "scene_row24_selection_private.h"

void scene_row24_selection_prepare_original(void)
{
    const char *text;

    g_display_scene_frame_objects[0] = frame_create_scene_object(194, 10, 1, 1);
    text = display_scene_lookup_text(271);
    g_display_scene_frame_objects[11] = display_scene_create_label(205, &text);
    transition_object_set_state(g_display_scene_frame_objects[11], 8);
    g_display_scene_frame_objects[3] = frame_create_scene_object(197, 305, 2, 0);
    g_display_scene_frame_objects[4] = frame_create_scene_object(200, 306, 3, 0);
    g_display_scene_frame_objects[5] = frame_create_scene_object(201, 307, 4, 0);
    g_display_scene_frame_objects[6] = frame_create_scene_object(202, 308, 5, 0);
    g_display_scene_frame_objects[7] = frame_create_scene_object(203, 309, 6, 0);
    g_display_scene_frame_objects[8] = frame_create_scene_object(204, 310, 7, 0);
    g_display_scene_frame_objects[9] = frame_create_scene_object(199, 311, 8, 0);
    g_display_scene_frame_objects[10] = frame_create_scene_object(198, 312, 9, 0);
    scene_row24_selection_create_labels();
    scene_row24_selection_draw_content_original();
}
