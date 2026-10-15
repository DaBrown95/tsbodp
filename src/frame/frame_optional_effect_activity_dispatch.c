#include "frame_optional_effect_activity_jobs.h"
unsigned int frame_optional_effect_activity_dispatch(struct FrameNeedEffectState *owner,struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,actor);
 switch((enum FrameOptionalEffectActivityKind)job->kind) {
 case FRAME_OPTIONAL_ACTIVITY_EFFECT:return frame_optional_effect_activity_step(owner,job);
 case FRAME_OPTIONAL_ACTIVITY_TWO:return frame_optional_two_activity_step(owner,job);
 case FRAME_OPTIONAL_ACTIVITY_INDICATOR:return frame_optional_indicator_activity_step(owner,job);
 }
 return 0;
}
asm(".align 2, 0");
