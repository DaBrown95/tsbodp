#include "display_motion.h"
void display_set_background_velocity(unsigned int index, int x, int y)
{
    g_display_background_system.backgrounds[index].velocity_x = x;
    g_display_background_system.backgrounds[index].velocity_y = y;
    g_display_background_system.backgrounds[index].flags |= 1;
}
