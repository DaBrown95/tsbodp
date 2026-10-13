#include "frame_need_effect_optional_completion.h"
unsigned int frame_need_effect_step_parameter(struct FrameNeedEffectState *owner,void *state,unsigned int index,struct FrameObject *indicator)
{
 unsigned int result=0;
 unsigned int value=frame_read_signed_parameter(state,index);
 if(value<=9) {
  frame_set_attachment_parameter_indicator(indicator,(unsigned char)frame_read_parameter_percentage(state,index));
  frame_update_attachment_parameter(state,index,indicator);
  if(frame_read_signed_parameter(state,index)==value+1)result=1;
 }else result=1;
 return result;
}
asm(".align 2, 0");
