#include "frame_actor_runtime.h"
#include "frame_transient_effect.h"
void frame_set_variant_state(struct FrameObject *,unsigned char);
void frame_actor_state_28(struct FrameObject *object)
{
 if(((struct FrameActorObject *)object)->variant_state==0) {
  frame_spawn_counter_effect(((struct FrameActorObject *)object)->indicator,*(signed char *)((char *)object+0x64));
  transition_object_set_state(object,16);
  frame_set_variant_state(object,2);
 }
}
asm(".align 2, 0");
