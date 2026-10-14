#include "scene_contact_menu.h"
unsigned int scene_contact_test_progress(void)
{
    unsigned int result = 0;
    if (g_scene_contact_state->option <= 3) {
        unsigned int first, second, scene, option, threshold_first, threshold_second;
        const struct SceneContactRequirement *requirements;
        first = frame_read_signed_parameter(&g_scene_contact_parameter_storage,
            g_scene_contact_resources[g_scene_contact_state->scene].fields.requirements->first_parameter);
        second = frame_read_signed_parameter(&g_scene_contact_parameter_storage,
            g_scene_contact_resources[g_scene_contact_state->scene].fields.requirements->second_parameter);
        scene = g_scene_contact_state->scene;
        requirements = g_scene_contact_resources[scene].fields.requirements;
        option = g_scene_contact_state->option;
        threshold_first = requirements->first_thresholds[option];
        threshold_second = requirements->second_thresholds[option];
        if (g_scene_previous_request.unknown_00 == 1 &&
            g_scene_contact_state->amount >=
                g_scene_contact_resources[scene].fields.costs[option] &&
            first >= threshold_first && second >= threshold_second) {
            result = 1;
            g_scene_contact_parameter_storage.values[scene] = option + 1;
        }
    }
    return result;
}
