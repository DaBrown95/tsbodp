#include "display_menu_results.h"
#include "scene_link_menu.h"
#include "frame_render_effect.h"
#include "frame_transient_effect.h"

void display_menu_shutdown(void)
{
    struct FrameObject *object = g_need_effect_player;
    unsigned char previous =
        g_display_menu_relation_state.values.baseline;
    unsigned char current = (unsigned char)display_menu_read_relation(
        &g_display_menu_relation_state.values,
        g_display_menu_state.definition);
    int difference;
    unsigned char narrowed_difference;

    transition_run_second(63, 0);
    display_release_object_list(&g_frame_primary_list);
    display_reset_palette_jobs();
    difference = (signed char)previous - (signed char)current;
    narrowed_difference = (unsigned char)difference;
    frame_clear_transient_effects();
    frame_clear_render_effects();
    frame_release_transient_definition_tiles(0, 6);
    frame_release_transient_definition_tiles(0, 7);
    frame_release_transient_definition_tiles(0, 4);
    frame_release_transient_definition_tiles(0, 5);
    transition_object_set_state(object, 28);
    frame_set_variant_state(object, 0);
    object->motion_storage.bytes[24] = narrowed_difference;
    if (g_scene_request.unknown_10 == 3)
        scene_clear_retained_display();
}
