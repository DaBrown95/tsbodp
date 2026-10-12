#include "display_motion.h"
void display_set_background_rotation(unsigned int index, unsigned short angle, unsigned short step)
{
    g_display_background_system.backgrounds[index].angle = angle;
    g_display_background_system.backgrounds[index].angle_step = step;
    g_display_background_system.backgrounds[index].flags |= step ? 2 : 8;
}
