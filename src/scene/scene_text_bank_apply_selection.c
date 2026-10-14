#include "scene_text_bank.h"
void scene_text_bank_apply_selection(void)
{
    display_text_select_bank(g_scene_request.parameter);
    save_stream_update_header_option();
    save_stream_suspend_audio();
    save_stream_commit_header();
    save_stream_resume_audio();
    if (g_scene_previous_request.unknown_00 == 0)
        scene_submit_default_request(3);
    else
        resource_submit_scene(g_scene_previous_request.unknown_00, 1,
                              g_scene_previous_request.scene);
}
asm(".align 2,0");
