#include "frame.h"
#include "view_math.h"
void view_subtract_point(const struct FramePoint *first,const struct FramePoint *second,struct FramePoint *output)  {
    output->x=first->x-second->x;
    output->y=first->y-second->y;
}
asm(".align 2, 0");
