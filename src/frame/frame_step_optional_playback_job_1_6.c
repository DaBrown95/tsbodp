#include "frame_optional_playback.h"
unsigned int frame_step_optional_playback_job_1_6(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job,unsigned int variant)
{
 switch((unsigned int)job->timer){
 case 0:
  job->timer=51;
  frame_set_actor_direction(job->actor,g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction]);
  frame_request_animation((struct FrameCommandObject *)job->actor,58);
  if(!variant)((struct FrameOptionalPlaybackState *)owner)->parameter=256;
  else ((struct FrameOptionalPlaybackState *)owner)->parameter=512;
  break;
 case 51:
  if(job->actor->flags&0x400000){
   job->timer=1;
   frame_optional_playback_play_cue(owner);
   frame_optional_playback_select_sequence(owner);
   if(owner->kind==44){
    struct FrameObject *object=owner->object;
    short direction=((struct FrameActorObject *)object)->direction;
    if(direction==3||direction==5){
     if(!variant)frame_commit_need_effect(object,3);
     else frame_commit_need_effect(object,4);
    }
   }
  }
  break;
 }
 if(job->timer==1)return 2;
 return 1;
}
