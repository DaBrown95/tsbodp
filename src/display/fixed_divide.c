#include "display_palette_curve.h"

int display_fixed_divide(short numerator, short denominator)
{
    return (short)((numerator * 256) / denominator);
}

__asm__(".align 2, 0");
