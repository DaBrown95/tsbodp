#include "frame_optional_effect_activity_jobs.h"
unsigned int frame_optional_two_activity_step(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 unsigned int result=1;
 if(job->running==1)job->timer=1;
 switch((unsigned int)job->timer) {
 case 0:
  frame_set_actor_direction(job->actor,g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction]);
  frame_request_animation((struct FrameCommandObject *)job->actor,27);
  job->timer=48;
  ((struct FrameOptionalEffectActivityWork *)owner)->sample=audio_play_animation_cue(71);
  ((struct FrameActorStateWork *)job->actor)->timer=0;
  break;
 case 48:
  ((struct FrameActorStateWork *)job->actor)->timer=(int)((unsigned int)((struct FrameActorStateWork *)job->actor)->timer+1u);
  if(((struct FrameActorStateWork *)job->actor)->timer==43) {
   ((struct FrameOptionalEffectActivityWork *)owner)->sample=audio_play_animation_cue(71);
   ((struct FrameActorStateWork *)job->actor)->timer=0;
  }
  frame_adjust_actor_needs(((struct FrameActorObject *)job->actor)->actor_state,52,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if((unsigned char)frame_need_effect_consume_optional_two(owner)==1) {
   audio_game_stop_sample(((struct FrameOptionalEffectActivityWork *)owner)->sample);
   frame_request_animation((struct FrameCommandObject *)job->actor,14);
   ((struct FrameOptionalEffectActivityWork *)owner)->sample=audio_play_animation_cue(26);
   job->timer=4;
  }
  break;
 case 4:
  frame_adjust_actor_needs(((struct FrameActorObject *)job->actor)->actor_state,52,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if(job->actor->flags&0x400000)job->timer=1;
  break;
 case 1:
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  result=2;
  audio_game_stop_sample(((struct FrameOptionalEffectActivityWork *)owner)->sample);
  break;
 }
 return result;
}
