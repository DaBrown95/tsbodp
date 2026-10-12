#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
void frame_clear_animation_pending(struct FrameObject *object) { object->flags&=~0x10; }
