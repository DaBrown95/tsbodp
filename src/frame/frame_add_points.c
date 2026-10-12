#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
void frame_add_points(const struct FramePoint *first,const struct FramePoint *second,struct FramePoint *result) { result->x=first->x+second->x;result->y=first->y+second->y; }
