#include "display.h"

unsigned int display_read_status_bit0(void)
{
    return DISPLAY_REG16(0x04000004) & 1;
}
