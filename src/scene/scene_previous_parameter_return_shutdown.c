#include "scene_previous_parameter_return.h"

void scene_previous_parameter_return_shutdown(void)
{
    transition_run_second(63, 0);
    display_release_object_list(&g_frame_primary_list);
    display_reset();
    display_reset_palette_jobs();
    g_resource_game_state.actor.unknownf4[0x746 - 0xf4] = 7;
}
