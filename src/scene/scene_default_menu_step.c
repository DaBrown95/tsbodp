#include "scene_default_menu.h"

void scene_default_menu_step(void)
{
    switch (g_scene_request.unknown_10) {
    case 0:
        if (g_input_pressed[g_input_config.local_player] & 9) {
            transition_run_second(63, 0);
            scene_default_menu_enter_slots();
            transition_run_first(63, 0);
        }
        break;
    case 1:
        {
            unsigned short pressed = g_input_pressed[g_input_config.local_player];

            if (pressed & 9)
                scene_default_menu_accept();
            else {
                unsigned int masked = 240;

                masked &= pressed;
                if (masked)
                    scene_default_menu_change_selection();
            }
        }
        break;
    }
}
