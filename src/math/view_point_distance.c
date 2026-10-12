#include "frame.h"
#include "view_math.h"
static inline void subtract(const struct FramePoint *a,const struct FramePoint *b,struct FramePoint *out) {
    out->x=a->x-b->x;
    out->y=a->y-b->y;
}
static inline int absolute(int value) {
    if(value<0)value=-value;
    return value;
}
unsigned int view_point_distance(struct FramePoint first,struct FramePoint second)  {
    struct FramePoint delta;
    subtract(&first,&second,&delta);
    delta.x=absolute(delta.x);
    delta.y=absolute(delta.y);
    return delta.x>delta.y?delta.x+((delta.y*3)>>3):delta.y+((delta.x*3)>>3);
}
asm(".align 2, 0");
