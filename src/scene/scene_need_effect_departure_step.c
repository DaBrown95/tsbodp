#include "frame_need_effect_departure.h"

void scene_need_effect_departure_step(void)
{
    if ((g_input_pressed[g_input_config.local_player] & 1) || g_scene_request.scene)
        resource_submit_scene(13, 0, g_scene_previous_request.unknown_00);
}
