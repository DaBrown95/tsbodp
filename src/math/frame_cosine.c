#include "frame.h"
#include "view_math.h"
int frame_cosine(int phase)  {
    unsigned char value=phase;
    unsigned char quadrant;
    int result;
    value+=64;
    quadrant=value>>6;
    if(quadrant&1)value=128-value;
    if(quadrant&2)result=-g_view_phase_table[value-128];
    else result=g_view_phase_table[value];
    return result;
}
asm(".align 2, 0");
