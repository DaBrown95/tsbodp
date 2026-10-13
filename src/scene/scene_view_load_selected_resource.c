#include "save_world_view_resources.h"
#include "display.h"
#include "heap.h"

void display_fill_background_rectangle(unsigned int, int, int, int, int,
    unsigned short);

void scene_view_load_selected_resource(unsigned int background, int x, int y,
    unsigned int tile, unsigned int palette,
    const struct SceneViewResourceSelection *selection)
{
    /* The original writes bytes two through thirty-one only. */
    unsigned short palette_buffer[16];
    unsigned short first_tile = tile;
    unsigned short palette_bank = palette;
    const struct BackgroundResource * const *group =
        g_scene_view_resource_groups[selection->prefix.fields.group];
    const unsigned char *palette_source;

    display_load_background_resource_dma(background,
        group[selection->prefix.fields.variant], first_tile);
    display_fill_background_rectangle(background, x, y, 4, 4,
        (palette_bank << 12) | first_tile);
    palette_source = (const unsigned char *)group[selection->prefix.fields.variant] + 2;
    if ((selection->prefix.word & 0x00ff00ff) == 0x00030000) {
        heap_copy((unsigned char *)palette_buffer + 2,
            palette_source + ((selection->prefix.fields.first << 5) + 2), 14);
        heap_copy((unsigned char *)palette_buffer + 16,
            palette_source + ((selection->prefix.fields.second << 5) + 16), 8);
        heap_copy((unsigned char *)palette_buffer + 24,
            palette_source + ((selection->third << 5) + 24), 8);
    } else {
        heap_copy((unsigned char *)palette_buffer + 2,
            palette_source + ((selection->prefix.fields.first << 5) + 2), 18);
        heap_copy((unsigned char *)palette_buffer + 20,
            palette_source + ((selection->prefix.fields.second << 5) + 20), 12);
    }
    display_load_palette(palette_buffer, palette_bank << 4, 16);
}
asm(".align 2, 0");
