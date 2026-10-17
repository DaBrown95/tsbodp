#include "frame_shared_optional_jobs.h"
unsigned int frame_shared_optional_dispatch(struct FrameNeedEffectState *owner,struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record(owner,actor);
 switch (job->kind) {
 case 61:return frame_shared_optional_timed_step(owner,job);
 case 45:return frame_shared_optional_indicator_step(owner,job);
 }
 return 0;
}
