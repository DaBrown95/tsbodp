#include "scene_timed_notice.h"
void scene_timed_notice_step(void)
{
    if ((game_step_counter_slot(0) &&
         (g_input_current[g_input_config.local_player] & 0x30f)) ||
        game_step_counter_slot(1)) {
        scene_submit_default_request(4);
    }
}
asm(".align 2, 0");
