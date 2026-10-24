#include "display.h"

static inline unsigned short palette_pattern(unsigned int color,
                                              unsigned int pattern)
{
    register unsigned int sum asm("r0") = color + pattern;
    return sum;
}

static inline void fill_character_halfwords(unsigned short fill,
                                           void *destination,
                                           unsigned int bytes)
{
    display_cpu_copy(&fill, destination, (bytes >> 1) | 0x01000000);
}

void display_fill_background_tile(unsigned int index, unsigned short tile,
                                  unsigned short input_color)
{
    register unsigned int color asm("r4") = input_color;
    register unsigned char control asm("r3") =
        *(unsigned char *)&g_background_states[index];
    unsigned int bytes = ((control >> 7) + 1) << 5;
    unsigned char *destination = (unsigned char *)(0x06000000 +
        ((((unsigned int)control << 28) >> 30) << 14) + bytes * tile);
    unsigned int pattern;

    if (!(control & 0x80)) {
        color &= 15;
        pattern = (color << 12) + (color << 8) + (color << 4);
    } else {
        color &= 255;
        pattern = color << 8;
    }
    color = palette_pattern(color, pattern);
    fill_character_halfwords(color, destination, bytes);
}
