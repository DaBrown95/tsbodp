#include "display.h"

void display_clear_forced_blank(void)
{
    DISPLAY_REG16(0x04000000) &= 0xff7f;
}
