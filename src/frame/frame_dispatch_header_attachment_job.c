#include "frame_need_effect_header_jobs.h"
#include "display_actor_interaction.h"
unsigned int frame_dispatch_header_attachment_job(struct FrameNeedEffectState *owner,struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record(owner,actor);
 switch(job->kind){
 case 49:return frame_step_header_attachment_job_49(owner,job);
 case 50:return frame_step_header_attachment_job_50(owner,job);
 }
 return 0;
}
