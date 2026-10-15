#include "frame_need_effect_condition_jobs.h"
#include "frame_need_effect_optional_jobs.h"
#include "resource_conditions.h"
#include "frame_actor_social.h"

unsigned int frame_need_effect_begin_condition_job(struct FrameNeedEffectState *owner,struct FrameObject *actor,unsigned int kind)
{
 struct FramePoint point;
 struct FrameActorAttachmentRecord *job=frame_allocate_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,actor);
 if (job) {
  job->kind=kind;
  frame_attachment_position(owner->object,0,&point);
  frame_begin_actor_route(actor,&point,&job->status,4,1);
  frame_request_animation((struct FrameCommandObject *)actor,6);
  return 1;
 } else return 0;
}
