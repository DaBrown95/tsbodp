#include "frame_need_effect_direct_49.h"
#include "display_actor_interaction.h"
unsigned int frame_need_effect_direct_49_dispatch(struct FrameNeedEffectState *owner,struct FrameObject *actor){
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,actor);
 unsigned int result;
 if(job->kind==49)result=frame_need_effect_direct_49_step(owner,job);else result=0;
 return result;
}
