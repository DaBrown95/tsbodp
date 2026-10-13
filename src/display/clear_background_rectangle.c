#include "display_time_hud.h"

void display_clear_background_rectangle(unsigned int index, int x, int y,
                                         int width, int height)
{
    display_fill_background_constant_rectangle(index, x, y, width, height, 0);
}
asm(".align 2, 0");
