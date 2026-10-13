#include "save_world_view_resources.h"
#include "display.h"

void scene_view_load_fixed_resource(unsigned int background, unsigned int tile,
    unsigned int palette)
{
    register unsigned short limited_palette asm("r3");
    limited_palette = palette;
    {
        unsigned int narrowed = limited_palette;
        g_scene_view_resource_background = background;
        g_scene_view_resource_tile = tile;
        g_scene_view_resource_palette = narrowed;
        display_load_background_resource(background, &g_scene_view_fixed_resource,
            g_scene_view_resource_tile, narrowed);
    }
}
