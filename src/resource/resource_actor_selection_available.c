#include "resource_actor_selection.h"
#include "resource_conditions.h"
#include "save_world_scene_selection.h"

unsigned char resource_actor_selection_available(unsigned int scene,
                                                 unsigned int actor)
{
    if (g_resource_selection_world.stage > 1 &&
        !(unsigned char)condition_group_complete(4, 4) &&
        !g_resource_selection_world.requested &&
        scene <= 14 && actor > 14 &&
        (unsigned char)save_world_scene_in_selected_row(actor, 0) &&
        resource_count_selectable_actor_entries() != 0)
        return 1;
    return 0;
}

asm(".align 2, 0");
