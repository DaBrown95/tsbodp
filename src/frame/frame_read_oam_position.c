#include "frame_tick.h"

void frame_read_oam_position(struct FrameObject *base,
                                          struct FramePoint *point)
{
    struct FrameTickObject *object = (struct FrameTickObject *)base;
    point->x = object->display.oam.x;
    point->y = object->display.oam.y;
}
