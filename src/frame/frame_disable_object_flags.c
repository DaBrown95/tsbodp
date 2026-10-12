#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
void frame_disable_object_flags(struct FrameObject *object,unsigned int flags) {object->flags&=~flags;}
