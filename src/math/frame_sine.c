#include "frame.h"
#include "view_math.h"
int frame_sine(int phase)  {
    unsigned char value=phase;
    unsigned char quadrant=value>>6;
    if(quadrant&1)value=128-value;
    if(quadrant&2)return -g_view_phase_table[value-128];
    return g_view_phase_table[value];
}
asm(".align 2, 0");
