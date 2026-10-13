#include "frame_optional_choice_apply.h"

void frame_optional_choice_apply_failure(void)
{
    g_need_effect_choice_text[0] = 500;
    g_actor_scene_request.object = frame_create_scene_object(193, 112, 15, 0);
    frame_activate_actor_scene_request();
}
asm(".align 2, 0");
