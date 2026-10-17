#include "frame.h"
#include "view_math.h"
#include "display.h"

int frame_fixed_reciprocal(int denominator)
{
    return (int)((unsigned int)display_divide(0x10000, denominator) << 16);
}
asm(".align 2,0");
