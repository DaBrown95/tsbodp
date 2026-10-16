#include "display.h"
#include "frame.h"
#include "view_math.h"

int display_matrix_sine(int phase)
{
    return (short)(frame_sine((unsigned char)phase) >> 8);
}

/* Two original zero alignment bytes precede the next function. */
asm(".align 2, 0");
