#include "display.h"

void display_set_forced_blank(void)
{
    DISPLAY_REG16(0x04000000) |= 0x80;
}
