#include "display_menu.h"
#include "display_menu_effects.h"
#include "scene_request.h"

void display_menu_step_result_effects(void)
{
    unsigned char code = g_display_menu_state.codes[g_scene_request.scene];

    if (code == 3) {
        if (g_scene_request.unknown_14 % 5 == 0)
            display_menu_show_change(5);
    } else if ((unsigned char)(code - 4) <= 1) {
        if (g_scene_request.unknown_14 % 5 == 0)
            display_menu_show_change(4);
    }
}
