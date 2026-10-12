#include "display_motion.h"
void display_set_background_velocity_x(unsigned int index, int x)
{
    g_display_background_system.backgrounds[index].velocity_x = x;
    g_display_background_system.backgrounds[index].flags |= 1;
}
