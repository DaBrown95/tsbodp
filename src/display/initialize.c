#include "scene_display.h"

void display_initialize(void)
{
    DISPLAY_REG16(0x04000000) = 0;
    display_set_mode(0);
}
