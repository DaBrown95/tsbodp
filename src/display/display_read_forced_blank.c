#include "display.h"

unsigned short display_read_forced_blank(void)
{
    return DISPLAY_REG16(0x04000000) & 0x80;
}
