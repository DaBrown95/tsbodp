#include "display_motion.h"
void display_set_background_position_y(unsigned int index, int y)
{
    g_display_background_system.backgrounds[index].position_y = y;
    g_display_background_system.backgrounds[index].flags |= 0x40;
}
