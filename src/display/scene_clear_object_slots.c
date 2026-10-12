#include "display_scene_lifecycle.h"
void display_scene_clear_object_slots(void)
{
    unsigned int i;
    for (i = 0; i <= 16; ++i)
        g_display_scene_frame_objects[i] = 0;
}
