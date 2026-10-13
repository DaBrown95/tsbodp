#include "frame_optional_playback.h"
unsigned int frame_initialize_optional_playback_context(struct FrameNeedEffectState *owner)
{
 if(owner->optional!=1){
  short parameter=((struct FrameOptionalPlaybackState *)owner)->parameter;
  if(parameter==256||parameter==512){
   ((struct FrameOptionalPlaybackState *)owner)->completed=1;
   frame_optional_playback_select_sequence(owner);
  }
 }
 return 1;
}
