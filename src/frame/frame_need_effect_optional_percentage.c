#include "frame_need_effect_optional_completion.h"
unsigned char frame_need_effect_optional_percentage(struct FrameNeedEffectState *owner)
{
 unsigned char result=100;
 if(owner->optional==2) {
  unsigned int value=owner->parameter>>8;
  if(result>value)result=result-value;
  else result=0;
 }else if(owner->optional==1) {
  if((short)owner->parameter>0)result=50;
 }
 return result;
}
asm(".align 2, 0");
