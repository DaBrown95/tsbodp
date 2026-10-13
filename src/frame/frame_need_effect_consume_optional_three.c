#include "frame_need_effect_optional_completion.h"
unsigned int frame_need_effect_consume_optional_three(struct FrameNeedEffectState *owner)
{
 if(owner->optional==3) {
  unsigned short *parameter=&owner->parameter;
  unsigned int old=*parameter;
  int value=*(short *)parameter;
  if(value>128) {
   *parameter=old-128;
   return 0;
  }
 }
 owner->optional=0;
 owner->parameter=0;
 return 1;
}
