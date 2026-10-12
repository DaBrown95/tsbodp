#include "display_motion.h"
void display_set_background_angle(unsigned int index, unsigned short angle)
{
    g_display_background_system.backgrounds[index].angle = angle;
    g_display_background_system.backgrounds[index].flags |= 8;
}
