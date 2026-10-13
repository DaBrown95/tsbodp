#include "frame_optional_choice_apply.h"

void frame_optional_choice_apply_special(void)
{
    unsigned int first = 0, second = 0;

    if (condition_is_complete(4, 0, 2) && g_optional_choice_budget_world.budget > 29)
        first = 1;
    if (condition_is_complete(4, 0, 3)
        && display_menu_read_relation_average(&g_display_menu_relation_state) > 39)
        second = 1;
    if (!first)
        g_need_effect_choice_text[0] = 1143;
    else if (!second)
        g_need_effect_choice_text[0] = 1144;
    else if (!condition_is_complete(4, 0, 1)) {
        g_need_effect_choice_text[0] = 1145;
        resource_set_triple(4, 0, 1);
        g_optional_choice_budget_world.budget -= 30;
    }
    frame_activate_actor_scene_request();
}
