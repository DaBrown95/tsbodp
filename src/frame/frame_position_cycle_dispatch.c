#include "frame_position_cycle_jobs.h"
unsigned int frame_position_cycle_dispatch(struct FrameNeedEffectState *owner,struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record(owner,actor);
 unsigned int result;
 if(job->kind==49)result=frame_position_cycle_step(owner,job);else result=0;
 return result;
}
