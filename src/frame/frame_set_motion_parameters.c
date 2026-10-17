#include "frame.h"

void frame_set_motion_parameters(struct FrameObject *object,
    const unsigned int parameters[3])
{
    __builtin_memcpy((unsigned char *)object + 0x40, parameters, 12);
}
asm(".align 2,0");
