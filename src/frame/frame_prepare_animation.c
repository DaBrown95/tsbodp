#include "frame.h"
void frame_prepare_animation(struct FrameObject *object)
{
    object->next_position.word = object->animation_source->next_position.word;
    object->display_layer = object->animation_source->display_layer;
    if (object->sharing_flags & 4)
        object->next_position.word.y += 0x10000;
    else if (object->sharing_flags & 8)
        object->next_position.word.y -= 0x10000;
}
