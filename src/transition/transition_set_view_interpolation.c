#include "view_effects.h"

void transition_set_view_interpolation(unsigned int value, unsigned char index)
{
    g_resource_view_motion[index].interpolate = value;
}
