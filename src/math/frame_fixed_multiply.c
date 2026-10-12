#include "frame.h"
#include "view_math.h"
int frame_fixed_multiply(int first,int second)  {
    return ((first/64)*(second/64))/16;
}
asm(".align 2, 0");
