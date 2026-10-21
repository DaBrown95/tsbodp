#include "save_world_view_resources.h"
#include "scene_view_frame.h"
#include "display_map_fill.h"

/* Incoming callers and any unused formals remain unknown. The selected
 * background and reached rectangle spans require valid initialized backing. */
void scene_view_draw_panel_mode_unrooted_343ec(unsigned int mode)
{
    unsigned int height, row;

    switch (mode) {
    case 0:
        height = 6;
        row = 15;
        display_fill_background_constant_rectangle(
            g_scene_view_resource_background, 9, 14, 22, 1, 0);
        break;
    case 1:
    case 3:
        height = 7;
        row = 14;
        break;
    case 2: {
        unsigned int clear_height = 22;
        height = 6;
        row = 15;
        display_fill_background_constant_rectangle(
            g_scene_view_resource_background, 9, 14, 22, clear_height, 0);
        break;
    }
    case 4:
        height = 6;
        display_fill_background_constant_rectangle(
            g_scene_view_resource_background, 9, 15, 22, height, 0);
        return;
    default:
        return;
    }
    scene_view_draw_frame(9, row, 22, height);
}

asm(".align 2, 0");
