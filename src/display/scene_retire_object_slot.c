#include "display_scene_lifecycle.h"
void display_scene_retire_object_slot(unsigned int index)
{
    struct FrameObject **base = g_display_scene_frame_objects;
    struct FrameObject **slot = base + index;
    if (*slot) {
        (*slot)->flags = ((*slot)->flags & ~1) | 2;
        *slot = 0;
    }
}
