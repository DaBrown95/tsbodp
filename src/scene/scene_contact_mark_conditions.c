#include "scene_contact_menu.h"
void scene_contact_mark_conditions(void)
{
    switch (g_scene_contact_state->scene) {
    case 0:
        if (g_contact_action_world.values[g_scene_contact_state->scene])
            resource_set_triple(0, 4, 1);
        if (g_contact_action_world.values[g_scene_contact_state->scene] > 1)
            resource_set_triple(1, 5, 3);
        resource_set_triple(0, 4, 0);
        break;
    case 2:
        resource_set_triple(1, 4, 0);
        if (g_contact_action_world.values[g_scene_contact_state->scene])
            resource_set_triple(1, 5, 3);
        break;
    case 3:
    case 7:
        if (g_contact_action_world.values[3] + g_contact_action_world.values[7] > 1)
            resource_set_triple(2, 5, 2);
        break;
    case 4:
    case 6:
        if (g_contact_action_world.values[4] + g_contact_action_world.values[6] > 2)
            resource_set_triple(3, 5, 2);
        break;
    case 1:
    case 5:
        if (g_contact_action_world.values[5] + g_contact_action_world.values[1] > 2)
            resource_set_triple(4, 5, 1);
        break;
    }
}
