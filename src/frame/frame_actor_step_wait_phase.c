#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_direct_move.h"
void frame_actor_step_wait_phase(struct FrameObject *object)
{
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 7:case 11:
  if(--((struct FrameActorDirectMoveWork *)object)->timer==-1)frame_set_variant_state(object,3);
  break;
 case 8:break;
 case 5:transition_object_set_state(object,1);break;
 }
}
asm(".align 2, 0");
