#include "frame_optional_effect_activity_jobs.h"
unsigned int frame_optional_effect_activity_begin(struct FrameNeedEffectState *owner,struct FrameObject *actor,unsigned int kind)
{
 struct FramePoint point;
 struct FrameActorAttachmentRecord *job=frame_allocate_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,actor);
 if(job) {
  job->kind=kind;
  ((struct FrameOptionalEffectActivityWork *)owner)->saved_position=actor->position;
  frame_attachment_position(owner->object,1,&point);
  frame_begin_actor_route(actor,&point,&job->status,3,1);
  frame_request_animation((struct FrameCommandObject *)actor,6);
  return 1;
 }
 return 0;
}
