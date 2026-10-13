#include "frame_optional_playback.h"
unsigned int frame_optional_playback_context_available(struct FrameNeedEffectState *owner,struct FrameObject *object)
{
 if(frame_count_actor_attachments(object)&&((struct FrameOptionalChoiceContextState *)owner)->attachment_mode==1)return 0;
 return 1;
}
asm(".align 2, 0");
