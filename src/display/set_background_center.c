#include "display_motion.h"
void display_set_background_center(unsigned int index, short x, short y)
{
    g_display_background_system.backgrounds[index].center_x = x;
    g_display_background_system.backgrounds[index].center_y = y;
    g_display_background_system.backgrounds[index].flags |= 8;
}
