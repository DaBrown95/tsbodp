#include "display_motion.h"
void display_offset_background_position(unsigned int index, int x, int y)
{
    g_display_background_system.backgrounds[index].position_x += x;
    g_display_background_system.backgrounds[index].position_y += y;
    g_display_background_system.backgrounds[index].flags |= 0x40;
}
