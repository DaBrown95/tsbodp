#include "view_effects.h"
unsigned int transition_get_view_mode(unsigned char index)  {
    return g_resource_view_motion[index].mode;
}
