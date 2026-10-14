#include "scene_text_bank.h"
void scene_text_bank_shutdown(void)
{
    if (g_scene_previous_request.unknown_00 == 0)
        transition_run_second(63, 1);
    else
        transition_run_second(63, 0);
    display_release_object_list(&g_frame_primary_list);
    display_clear_text_slots();
    display_reset();
}
asm(".align 2,0");
