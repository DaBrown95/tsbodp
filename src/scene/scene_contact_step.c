#include "input.h"
#include "scene_contact_menu.h"
void scene_contact_step(void)
{
    unsigned int player = g_transition_view_context.current_view;
    struct SceneContactCursor *cursor =
        (struct SceneContactCursor *)g_transition_view_context.views[player].object;
    switch (g_scene_contact_state->phase) {
    case 0:
        if (g_input_pressed[player] & 11) {
            transition_run_second(63, 0);
            g_scene_contact_state->phase = 1;
        }
        break;
    case 1:
        scene_contact_start_activity();
        g_scene_contact_state->phase = 2;
        break;
    case 2:
        display_time_update_scene_countdown();
        scene_contact_refresh_value();
        if (g_scene_contact_state->scene <= 1)
            scene_contact_original_step_primary();
        else
            scene_contact_original_step_secondary();
        if (cursor && cursor->state == 5)
            break;
        if (g_frame_flags & 16)
            break;
        if ((g_scene_contact_state->flags & 1) ||
            ((g_scene_contact_definitions[g_scene_contact_state->scene].flags & 1) &&
             (unsigned char)display_time_equal(&g_display_countdown,
                                                &g_resource_selector_clock, 31))) {
            g_scene_contact_state->phase = 3;
            g_scene_request.unknown_14 = 20;
            scene_contact_apply_need_adjustments();
        }
        break;
    case 3:
        if (--g_scene_request.unknown_14 == (unsigned int)-1) {
            if ((unsigned char)scene_contact_test_progress())
                g_scene_contact_state->phase = 4;
            else
                g_scene_contact_state->phase = 6;
        }
        break;
    case 4:
        scene_contact_shutdown();
        scene_contact_show_completion();
        g_scene_contact_state->phase = 5;
        transition_run_first(63, 0);
        break;
    case 5:
        if (g_input_pressed[player] & 11)
            g_scene_contact_state->phase = 6;
        break;
    case 6:
        g_scene_contact_state->result = 3;
        if (g_scene_previous_request.unknown_00 == 1) {
            frame_add_game_value(g_scene_contact_state->amount);
            display_time_step_world(
                &g_scene_contact_definitions[g_scene_contact_state->scene].elapsed);
            scene_contact_mark_conditions();
            resource_submit_scene(1, 0, g_scene_contact_return_argument);
        } else if (g_scene_contact_state->return_mode) {
            resource_submit_scene(10, 1, 0);
        } else {
            scene_submit_default_request(5);
        }
        break;
    }
    if (g_scene_contact_state->return_mode)
        scene_contact_original_service_mode();
}
