#include "frame_need_effect.h"
#include "frame_attachment_unrooted_42_94.h"

unsigned int frame_unrooted_attachment_check_1dd80(struct FrameNeedEffectState *owner,
                                                  struct FrameObject *actor)
{
 if(frame_count_actor_attachments(actor) && owner->unknown_60[0] == 1)return 0;
 return 1;
}
asm(".align 2, 0");
