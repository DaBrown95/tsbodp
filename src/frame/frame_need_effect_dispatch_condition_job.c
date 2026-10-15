#include "frame_need_effect_condition_jobs.h"
#include "frame_need_effect_optional_jobs.h"
#include "resource_conditions.h"
#include "frame_actor_social.h"

unsigned int frame_need_effect_dispatch_condition_job(struct FrameNeedEffectState *owner,struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,actor);
 switch (job->kind) {
 case 7:return frame_step_condition_need_job(owner,job);
 case 44:return frame_step_condition_wait_job(owner,job);
 case 45:return frame_step_condition_parameter_job(owner,job);
 }
 return 0;
}
