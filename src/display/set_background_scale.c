#include "display_motion.h"
void display_set_background_scale(unsigned int index, short scale)
{
    g_display_background_system.backgrounds[index].scale = scale;
    g_display_background_system.backgrounds[index].flags |= 8;
}
