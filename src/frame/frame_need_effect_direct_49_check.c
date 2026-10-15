#include "frame_need_effect_direct_49.h"
#include "display_actor_interaction.h"
unsigned int frame_need_effect_direct_49_check(struct FrameNeedEffectState *owner,struct FrameObject *actor){
 if(frame_count_actor_attachments(actor) && owner->unknown_60[0] == 1)return 0;
 return 1;
}
asm(".align 2, 0");
