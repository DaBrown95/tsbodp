#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "view_math.h"
unsigned char frame_direction_toward(struct FrameObject *object,struct FrameObject *target) { struct FramePoint first,second,delta; frame_point_to_integer(&object->position,&first);frame_point_to_integer(&target->position,&second);delta.x=second.x-first.x;delta.y=second.y-first.y;return frame_direction_from_velocity(delta); }
asm(".align 2, 0");
