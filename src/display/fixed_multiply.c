#include "display_palette_curve.h"

int display_fixed_multiply(short left, short right)
{
    register int product asm("r0");
    int rounded;
    product = left * right;
    rounded = product;
    if (product < 0)
        rounded += 255;
    return (short)(rounded >> 8);
}
