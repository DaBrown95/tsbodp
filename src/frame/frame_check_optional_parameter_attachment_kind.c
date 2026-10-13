#include "frame_need_effect_optional_completion.h"
unsigned int frame_check_optional_parameter_attachment_kind(struct FrameNeedEffectState *owner,struct FrameObject *actor,unsigned int kind)
{
 switch(kind) {
 case 7:break;
 case 55:
  if((unsigned int)frame_read_signed_parameter(g_frame_actor_social_probe,1)>9)return 0;
  break;
 }
 return 1;
}
asm(".align 2, 0");
