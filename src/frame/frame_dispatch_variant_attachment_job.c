#include "frame_actor_attachment_parameters.h"
unsigned int frame_dispatch_variant_attachment_job(struct FrameNeedEffectState *owner,struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,actor);
 return frame_step_variant_attachment_job(owner,job);
}
asm(".align 2, 0");
