#include "display_text_raster.h"

void display_text_flip_tile(void *buffer)
{
    unsigned char *left = buffer, *right;
    int rows, pairs;
    if (g_display_text_state.wide_color == 1) {
        rows = 8;
        do {
            right = left + 7;
            pairs = 4;
            do {
                unsigned char a = *left, b = *right;
                *left = b;
                *right = a;
                ++left;
                --right;
            } while (--pairs > 0);
            left += 4;
        } while (--rows > 0);
    } else {
        rows = 8;
        do {
            right = left + 3;
            pairs = 2;
            do {
                unsigned int a = *left;
                unsigned int swapped_a = (a >> 4) | (a << 4);
                unsigned int b = *right;
                unsigned int swapped_b = (b >> 4) | (b << 4);
                *left = swapped_b;
                *right = swapped_a;
                ++left;
                --right;
            } while (--pairs > 0);
            left += 2;
        } while (--rows > 0);
    }
}
