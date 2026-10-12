#include "frame.h"
#include "view_math.h"
void view_copy_point(const struct FramePoint *source,struct FramePoint *output)  {
    output->x=source->x;
    output->y=source->y;
}
asm(".align 2, 0");
