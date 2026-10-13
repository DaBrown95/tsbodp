#include "frame_optional_choice_context.h"

unsigned char frame_object_has_zero_id(struct FrameObject *object)
{
    unsigned char result = 0;
    if (object->id == 0)
        result = 1;
    return result;
}
asm(".align 2, 0");
