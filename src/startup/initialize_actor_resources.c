#include "frame_actor_initialization.h"

void startup_initialize_actor_resources(void)
{
    frame_initialize_actor_need_states();
    frame_initialize_need_effect_pool();
    frame_reset_need_effect_selection();
    frame_search_initialize_buffers();
}
asm(".align 2, 0");
