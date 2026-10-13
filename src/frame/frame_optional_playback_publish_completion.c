#include "frame_optional_playback.h"
void frame_optional_playback_publish_completion(struct FrameNeedEffectState *owner)
{
 if(((struct FrameOptionalPlaybackState *)owner)->completed){
  unsigned char direction;
  ((struct FrameOptionalPlaybackState *)owner)->completed=0;
  direction=((struct FrameActorObject *)owner->object)->direction;
  if(direction==3||direction==5){
   frame_commit_need_effect(owner->object,3);
   if(owner->kind==44&&((struct FrameOptionalPlaybackState *)owner)->parameter==512)frame_commit_need_effect(owner->object,4);
  }else frame_commit_need_effect(owner->object,1);
 }
}
