#include "frame.h"
#include "view_math.h"
unsigned char view_direction_angle(struct FramePoint delta)  {
    unsigned short angle;
    delta.x>>=16;
    delta.y>>=16;
    angle=view_bios_arctan2((short)delta.x,(short)delta.y);
    return (((((unsigned int)angle<<5)+0x800)>>16)+8)&0x1f;
}
asm(".align 2, 0");
