#include "display_map.h"

void display_reload_background_map(unsigned int index)
{
    struct DisplayMapState *background = &g_display_map_states[index];
    const struct DisplayStoredMap *map = background->stored_map;
    register int width __asm__("r6");
    int height;
    unsigned int value;
    register const struct DisplayStoredMap *height_map __asm__("r3");
    value = map->width;
    width = 32;
    if (value < 32) width = value;
    value = *(const volatile unsigned short *)&map->height;
    height = 32;
    height_map = map;
    if (value < 32) height = height_map->height;
    display_copy_map_rectangle(width, height, 0, 0, map->width,
        background->stored_map->tiles, 0, 0, 32, background->buffer);
    background->flags |= 0x20;
}
