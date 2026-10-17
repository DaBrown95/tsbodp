#include "frame_need_effect_secondary_header_jobs.h"
unsigned int frame_dispatch_secondary_header_attachment_job(struct FrameNeedEffectState *owner,struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record(owner,actor);
 switch(job->kind){
 case 50:return frame_step_secondary_header_attachment_job_50(owner,job);
 case 27:return frame_step_secondary_header_attachment_job_27(owner,job);
 }
 return 0;
}
