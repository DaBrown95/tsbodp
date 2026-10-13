#include "frame_optional_choice_apply.h"

void frame_optional_choice_install_value(unsigned char kind)
{
    unsigned int object_id;

    switch (kind) {
    case 0:
        g_need_effect_choice_text[0] = 1148;
        object_id = 263;
        break;
    case 2:
        g_need_effect_choice_text[0] = 1147;
        object_id = 264;
        break;
    case 3:
        g_need_effect_choice_text[0] = 1146;
        object_id = 265;
        break;
    default:
        goto activate;
    }
    g_actor_scene_request.object = frame_create_scene_object(193, object_id, 15, 0);
activate:
    frame_activate_actor_scene_request();
}
asm(".align 2, 0");
