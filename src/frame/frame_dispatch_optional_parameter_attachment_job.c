#include "frame_need_effect_optional_completion.h"
unsigned int frame_dispatch_optional_parameter_attachment_job(struct FrameNeedEffectState *owner,struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record(owner,actor);
 switch(job->kind) {
 case 55:return frame_step_optional_parameter_attachment_job(owner,job);
 case 7:return frame_step_optional_attachment_kind_7(owner,job);
 }
 return 0;
}
