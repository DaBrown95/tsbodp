#include "frame_need_effect_optional_completion.h"
unsigned int frame_need_effect_consume_optional_two(struct FrameNeedEffectState *owner)
{
 if(owner->optional==2) {
  unsigned short *parameter=&owner->parameter;
  unsigned int old=*parameter;
  int value=*(short *)parameter;
  if(value>51) {
   *parameter=old-51;
   return 0;
  }
 }
 owner->optional=0;
 owner->parameter=0;
 return 1;
}
