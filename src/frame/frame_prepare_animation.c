#include "frame.h"
void frame_prepare_animation(struct FrameObject *object)
{
    object->next_position = object->animation_source->next_position;
    object->display_layer = object->animation_source->display_layer;
    if (object->sharing_flags & 4)
        object->next_position.y += 0x10000;
    else if (object->sharing_flags & 8)
        object->next_position.y -= 0x10000;
}
