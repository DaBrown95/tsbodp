#include "frame.h"
#include "view_math.h"
int resource_scale_value(short value)  {
    int magnitude=(value<<8)&0x7fffff;
    if(value<0)magnitude=-magnitude;
    return magnitude;
}
asm(".align 2, 0");
