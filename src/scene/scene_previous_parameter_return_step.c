#include "input.h"
#include "scene_request_queue.h"

void scene_previous_parameter_return_step(void)
{
    if (g_input_pressed[g_input_config.local_player] & 1)
        resource_submit_scene(1, 0, g_scene_previous_request.parameter);
}
