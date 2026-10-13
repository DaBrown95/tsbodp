#include "frame_optional_playback.h"
unsigned int frame_select_optional_playback_attachment_kind(struct FrameNeedEffectState *owner,unsigned char *out)
{
 if(!(unsigned char)frame_need_effect_optional_one_ready(owner)){
  short parameter=((struct FrameOptionalPlaybackState *)owner)->parameter;
  if(parameter==0)*out=57;
  else{
   *out=56;
   out[1]=62;
   if(owner->kind==44){
    if(parameter!=256)out[2]=1;
    else out[2]=6;
   }
  }
 }else *out=45;
 return 1;
}
asm(".align 2, 0");
