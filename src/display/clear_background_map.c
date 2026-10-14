#include "display_background_clear.h"

void display_clear_background_map(unsigned int index)
{
    display_fill_background_map(index, 0, 0);
}
asm(".align 2, 0");
