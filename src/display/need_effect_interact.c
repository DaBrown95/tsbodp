#include "display_need_effect_update.h"

void frame_need_effect_interact(struct FrameObject *first, struct FrameObject *second)
{
    frame_need_effect_stop_at_position(first);
    frame_need_effect_stop_at_position(second);
}
