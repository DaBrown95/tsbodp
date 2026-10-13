#include "display_menu_relation_resource.h"
#include "display_menu_scene.h"
#include "display_scene_setup.h"

void display_menu_load_relation_resource(void)
{
    unsigned char flags = display_menu_relation_flags(&g_display_menu_relation_values,
                                                    g_display_menu_state.definition);
    if (flags & 8)
        display_load_background(3, &g_display_menu_relation_resource8, 258, 12, 0, 0);
    else if (flags & 4)
        display_load_background(3, &g_display_menu_relation_resource4, 258, 12, 0, 0);
    else if (flags & 1)
        display_load_background(3, &g_display_menu_relation_resource1, 258, 12, 0, 0);
    else if (flags & 2)
        display_load_background(3, &g_display_menu_relation_resource2, 258, 12, 0, 0);
    else
        display_load_background(3, g_display_menu_relation_resources[g_display_menu_state.definition],
                                258, 12, 0, 0);
}

asm(".align 2, 0");
