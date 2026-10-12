#include "display_motion.h"
void display_set_background_scale_step(unsigned int index, unsigned short step)
{
    g_display_background_system.backgrounds[index].scale_step = step;
    g_display_background_system.backgrounds[index].flags |= step ? 4 : 8;
}
__asm__(".align 2, 0");
