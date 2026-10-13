#include "save_world_scene_selection.h"
#include "save_world_initialization.h"

unsigned char save_world_scene_in_selected_row(unsigned int scene,
                                               unsigned int option)
{
    unsigned char base = (unsigned char)option;
    unsigned char result = 0;
    if (base) {
        switch (scene) {
        case 6:
            if (g_save_world_condition_source.row <= 1)
                result = 1;
            break;
        case 4:
            if (g_save_world_condition_source.row == 2)
                result = 1;
            break;
        case 9:
            if (g_save_world_condition_source.row == 4)
                result = 1;
            break;
        case 14:
            if (g_save_world_condition_source.row == 3)
                result = 1;
            break;
        default:
            result = 0;
        }
    } else {
        switch (scene) {
        case 16: case 17: case 18:
            if (g_save_world_condition_source.row <= 1)
                result = 1;
            break;
        case 23: case 24: case 25:
            if (g_save_world_condition_source.row == 2)
                result = 1;
            break;
        case 39: case 40:
            if (g_save_world_condition_source.row == 4)
                result = 1;
            break;
        case 46: case 47: case 48:
            if (g_save_world_condition_source.row == 3)
                result = 1;
            break;
        default:
            result = 0;
        }
    }
    return result;
}
