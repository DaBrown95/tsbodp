#include "frame.h"
#include "view_math.h"
#include "display.h"

int frame_bios_fixed_divide(int numerator, int denominator)
{
    return (int)((unsigned int)display_bios_div(
        (int)((unsigned int)numerator << 6), denominator >> 6) << 4);
}
