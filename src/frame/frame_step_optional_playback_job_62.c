#include "frame_optional_playback.h"
unsigned int frame_step_optional_playback_job_62(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 struct FrameObject *actor=job->actor;
 struct FrameActorNeedState *needs=((struct FrameActorObject *)actor)->actor_state;
 /* Timer comparisons partition the full unsigned word into 0, 8 and 50. */
 unsigned int phase=(unsigned int)job->timer;
 if(phase==8)goto phase8;
 if(phase<=8){
  if(phase==0)goto phase0;
  goto done;
 }
 if(phase==50)goto phase50;
 goto done;
phase0:
  if(frame_attachment_need_is_low(needs,6)==1){
   frame_set_actor_direction(job->actor,4);
   frame_request_animation((struct FrameCommandObject *)job->actor,85);
   if(g_frame_interaction_settings.attachment_mode==0)audio_play_animation_cue(137);
   else audio_play_animation_cue(136);
   job->timer=8;
  }else{
   job->timer=50;
   frame_set_actor_direction(job->actor,g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction]);
   frame_request_animation((struct FrameCommandObject *)job->actor,8);
   ((struct FrameOptionalPlaybackActorTimer *)job->actor)->timer=150;
   frame_optional_playback_play_cue(owner);
   frame_optional_playback_select_sequence(owner);
  }

 goto done;
phase50:
  { const unsigned char *definitions=(const unsigned char *)g_frame_need_effect_definitions;
   unsigned int offset=owner->kind*36;
   struct DisplayNeedEffectDefinitionView *definition=(struct DisplayNeedEffectDefinitionView *)(offset+(unsigned int)definitions);
   frame_adjust_actor_needs(needs,33,definition->unknown_23);
  }
  if(!(unsigned char)frame_step_attachment_need_timer(job,needs,6,&((struct FrameOptionalPlaybackActorTimer *)job->actor)->timer)){
   job->timer=1;
   frame_request_animation((struct FrameCommandObject *)job->actor,1);
  }

 goto done;
phase8:
  if(actor->flags&0x400000){
   job->timer=1;
   frame_request_animation((struct FrameCommandObject *)actor,1);
   frame_clear_attachment_need_countdown(needs);
  }

done:
 if(job->timer==1)return 2;
 return 1;
}
