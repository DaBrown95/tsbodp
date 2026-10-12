#include "display_scene_navigation.h"
void display_scene_update_page_controls(void)
{
    if (!g_display_scene_byte2)
        g_display_scene_objects[4]->flags &= ~1;
    else
        g_display_scene_objects[4]->flags |= 1;
    {
        int page = g_display_scene_byte2;
        register unsigned char count asm("r1") = g_display_scene_byte0;
        register int limit asm("r0") = ((count + 3) >> 2) - 1;
        if (page == limit)
            g_display_scene_objects[5]->flags &= ~1;
        else
            g_display_scene_objects[5]->flags |= 1;
    }
}
