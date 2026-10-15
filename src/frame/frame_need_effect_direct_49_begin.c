#include "frame_need_effect_direct_49.h"
#include "display_actor_interaction.h"
unsigned int frame_need_effect_direct_49_begin(struct FrameNeedEffectState *owner,struct FrameObject *actor,unsigned int kind){
 struct FrameActorAttachmentRecord *job=frame_allocate_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,actor);
 struct FramePoint point;unsigned char result;
 if(job){
  job->kind=kind;
  frame_attachment_position(owner->object,0,&point);
  frame_begin_actor_route(actor,&point,&job->status,5,1);
  frame_request_animation((struct FrameCommandObject *)actor,6);
  result=1;
 }else result=0;
 return result;
}
