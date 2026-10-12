#include "display_motion.h"
void display_set_background_angle_step(unsigned int index, unsigned short step)
{
    g_display_background_system.backgrounds[index].angle_step = step;
    g_display_background_system.backgrounds[index].flags |= step ? 2 : 8;
}
__asm__(".align 2, 0");
