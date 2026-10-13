#include "frame_optional_playback.h"
#include "audio_vblank.h"
void frame_optional_playback_select_sequence(struct FrameNeedEffectState *owner)
{
 unsigned char id;
 if(((struct FrameOptionalPlaybackState *)owner)->parameter==256){
  if(frame_random_secondary_range(0,1)==0)id=68;
  else id=69;
 }else id=70;
 audio_select_sequence(id);
 g_audio_control.flags|=8;
}
asm(".align 2, 0");
