#include "display_menu_pages.h"

void display_menu_show_hint(unsigned char enabled)
{
    if (enabled) {
        const unsigned short *map;
        g_display_menu_objects.hint->flags |= 1;
        map = display_load_background(1, &g_display_menu_hint_resource,
                                      407, 14, 1, 3);
        g_display_menu_state.unknown_00 =
            407 + display_read_map_tile(map + 2, 3, 3, map[0]);
        g_display_menu_state.unknown_28 = 1;
    } else {
        g_display_menu_objects.hint->flags &= ~1;
        display_fill_background_constant_rectangle(1, 1, 3, 17, 10, 572);
        g_display_menu_state.unknown_28 = 0;
    }
}
asm(".align 2, 0");
