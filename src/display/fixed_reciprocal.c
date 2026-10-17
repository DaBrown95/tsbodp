#include "display_palette_curve.h"
#include "display.h"

int display_fixed_reciprocal(short denominator)
{
    return (short)display_divide(0x10000, denominator);
}
asm(".align 2,0");
