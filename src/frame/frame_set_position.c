#include "frame_constructor.h"

void frame_set_position(struct FrameObject *object, int x, int y)
{
    object->position.x = x;
    object->position.y = y;
    object->next_position.x = x;
    object->next_position.y = y;
}

asm(".align 2, 0");
