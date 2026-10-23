#include "resource_actor_selection.h"
#include "frame_random.h"

unsigned char resource_select_actor(unsigned int scene, unsigned int actor)
{
    if (resource_actor_selection_available(scene, actor)) {
        int relation = display_menu_read_relation(
            &g_resource_selection_relation_view.values, 13);
        if (relation == -128)
            relation = 0;
        relation += 100;
        relation /= 2;
        if (frame_random_range(0, relation) <= 2) {
            if (resource_selection_has_kind_0804573c()) {
                g_resource_selection_relation_view.selection_requested = 1;
                return 4;
            } else {
                resource_remove_random_selectable_actor_entry();
                g_resource_selection_relation_view.selection_requested = 1;
                return 2;
            }
        }
    }
    return 0;
}

asm(".align 2, 0");
