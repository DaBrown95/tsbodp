#include "frame_optional_playback.h"
#include "scene.h"
unsigned int frame_step_optional_playback_job_56_57(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job,unsigned int variant)
{
 switch((unsigned int)job->timer){
 case 0:
  {unsigned char result=(unsigned char)frame_need_effect_try_optional(owner);
   if(result)return 2;
   frame_set_actor_direction(job->actor,g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction]);
   frame_request_animation((struct FrameCommandObject *)job->actor,58);
   if(!variant)((struct FrameOptionalPlaybackState *)owner)->parameter=256;
   else ((struct FrameOptionalPlaybackState *)owner)->parameter=result;
   job->timer=51;
   audio_play_animation_cue(177);
  }
  break;
 case 51:
  if(job->actor->flags&0x400000){
   if(!variant){
    struct FrameObject *object=owner->object;
    unsigned char direction=((struct FrameActorObject *)object)->direction;
    if(direction==3||direction==5)frame_commit_need_effect(object,3);
    else frame_commit_need_effect(object,1);
    frame_optional_playback_play_cue(owner);
    frame_optional_playback_select_sequence(owner);
   }else{
    frame_commit_need_effect(owner->object,2);
    audio_select_sequence(scene_audio_for_period(g_scene_context.period));
   }
   job->timer=1;
  }
  break;
 }
 if(job->timer==1)return 2;
 return 1;
}
