#include "scene_contact_activity_four.h"

void scene_contact_activity_four_load_palettes(void)
{
    int i;

    for (i = 0; i <= 6; ++i)
        display_load_palette_alternate(
            g_scene_contact_activity_four_items[i].palette, (15 - i) << 4, 16);
}
