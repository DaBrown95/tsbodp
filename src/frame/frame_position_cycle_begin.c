#include "frame_position_cycle_jobs.h"
unsigned int frame_position_cycle_begin(struct FrameNeedEffectState *owner,struct FrameObject *actor,unsigned int kind)
{
 struct FramePoint point;
 struct FrameActorAttachmentRecord *job=frame_allocate_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,actor);
 if (job) {
  job->kind=kind;
  frame_attachment_position(owner->object,2,&point);
  frame_begin_actor_route(actor,&point,&job->status,0,1);
  ((struct FrameAttachmentSavedPosition *)owner)->position=job->actor->position;
  frame_request_animation((struct FrameCommandObject *)actor,6);
  return 1;
 }
 return 0;
}
asm(".align 2, 0");
