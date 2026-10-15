#include "frame_optional_effect_activity_jobs.h"
unsigned int frame_optional_effect_activity_step(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 struct FrameActorNeedState *needs=((struct FrameActorObject *)job->actor)->actor_state;
 switch((unsigned int)job->timer) {
 case 0:
  {
   struct FramePoint point;
   frame_attachment_position(owner->object,0,&point);
   frame_begin_actor_route(job->actor,&point,&job->status,4,1);
   frame_request_animation((struct FrameCommandObject *)job->actor,6);
   job->timer=21;
  }
  break;
 case 21:
  ((struct FrameOptionalEffectActivityWork *)owner)->effect=frame_create_actor_effect(owner->object,2,4,0);
  if(((struct FrameActorObject *)owner->object)->direction<=3)frame_set_actor_direction(job->actor,1);
  else frame_set_actor_direction(job->actor,5);
  if(((struct FrameActorObject *)owner->object)->direction==3||((struct FrameActorObject *)owner->object)->direction==7) {
   if(((struct FrameOptionalEffectActivityWork *)owner)->effect)((struct FrameActorObject *)((struct FrameOptionalEffectActivityWork *)owner)->effect)->oam.flip_x=1;
  }
  job->timer=22;
  frame_request_animation((struct FrameCommandObject *)job->actor,48);
  ((struct FrameActorStateWork *)job->actor)->timer=150;
  ((struct FrameOptionalEffectActivityWork *)owner)->sample=audio_play_animation_cue(163);
  break;
 case 22:
  frame_adjust_actor_needs(needs,20,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if(!(unsigned char)frame_step_attachment_need_timer(job,needs,1,&((struct FrameActorStateWork *)job->actor)->timer)) {
   job->timer=23;
   audio_game_stop_sample(((struct FrameOptionalEffectActivityWork *)owner)->sample);
   frame_request_animation((struct FrameCommandObject *)job->actor,6);
   frame_begin_actor_route(job->actor,&((struct FrameOptionalEffectActivityWork *)owner)->saved_position,&job->status,4,1);
  }
  break;
 case 23:
  if(((struct FrameOptionalEffectActivityWork *)owner)->effect) {
   audio_play_animation_cue(165);
   transition_object_set_state(((struct FrameOptionalEffectActivityWork *)owner)->effect,1);
   ((struct FrameOptionalEffectActivityWork *)owner)->effect=0;
  }
  job->timer=1;
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  break;
 }
 if(job->timer==1) {
  frame_need_effect_try_optional(owner);
  frame_need_effect_accumulate_optional(owner);
  resource_set_triple(0,1,2);
  return 2;
 }
 return 1;
}
asm(".align 2, 0");
