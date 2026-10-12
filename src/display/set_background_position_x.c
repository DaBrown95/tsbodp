#include "display_motion.h"
void display_set_background_position_x(unsigned int index, int x)
{
    g_display_background_system.backgrounds[index].position_x = x;
    g_display_background_system.backgrounds[index].flags |= 0x40;
}
