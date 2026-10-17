#include "frame.h"
#include "view_math.h"
#include "display.h"

int frame_fixed_divide(int numerator, int denominator)
{
    return display_divide((int)((unsigned int)numerator << 16), denominator);
}
asm(".align 2,0");
