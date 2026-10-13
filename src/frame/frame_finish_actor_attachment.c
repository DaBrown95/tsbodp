#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_attachment.h"
void frame_finish_actor_attachment(struct FrameActorAttachmentRecord *record)
{
 struct FrameObject *actor=record->actor;
 if(actor->id==0) {
  transition_object_set_state(actor,23);
  frame_set_variant_state(record->actor,0);
 } else {
  transition_object_set_state(actor,((struct FrameActorObject *)actor)->default_state);
  frame_set_variant_state(record->actor,7);
 }
 frame_cancel_actor_route(record->actor);
}
asm(".align 2, 0");
