#include "display.h"

void display_sprite_dimensions(unsigned int group, unsigned int variant,
    struct DisplayPoint *dimensions)
{
    const unsigned char *table = g_display_sprite_dimensions;
    unsigned int offset = variant * 12 + group * 48;
    dimensions->x = *(const int *)(table + offset);
    table += 4;
    dimensions->y = *(const int *)(table + offset);
}
