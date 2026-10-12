#include "display_motion.h"
void display_set_background_scale_limits(unsigned int index, short minimum, short maximum)
{
    g_display_background_system.backgrounds[index].minimum_scale = minimum;
    g_display_background_system.backgrounds[index].maximum_scale = maximum;
}
