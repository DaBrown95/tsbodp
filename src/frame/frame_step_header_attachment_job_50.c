#include "frame_need_effect_header_jobs.h"
#include "frame_need_effect_optional_jobs.h"
#include "frame_actor_social.h"
void frame_stop_motion(struct FrameObject *);
#include "frame_actor_idle.h"
unsigned int frame_step_header_attachment_job_50(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 struct FrameActorNeedState *needs=((struct FrameActorObject *)job->actor)->actor_state;
 switch((unsigned int)job->timer){
 case 0:
  frame_stop_motion(job->actor);
  ((struct FrameActorObject *)job->actor)->direction=g_header_attachment_reverse_directions[((struct FrameActorObject *)owner->object)->direction];
  ((struct FrameActorStateWork *)job->actor)->timer=90;
  job->timer=37;
  frame_request_animation((struct FrameCommandObject *)job->actor,16);
  if(((struct FrameActorObject *)owner->object)->direction==3||((struct FrameActorObject *)owner->object)->direction==5)
   frame_need_effect_handoff_bounds(job->actor,owner,1);
  break;
 case 37:
  if(job->actor->flags&0x400000){
   audio_play_animation_cue(66);
   frame_clear_animation_pending(job->actor);
   ((struct FrameAttachmentJobWork *)owner)->sample=audio_play_animation_cue(142);
   job->timer=38;
  }
  break;
 case 38:
  frame_adjust_actor_needs(needs,27,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if(job->actor==g_need_effect_player)frame_set_actor_need_step_mode(1);
  if(!(unsigned char)frame_step_attachment_need_timer(job,needs,2,&((struct FrameActorStateWork *)job->actor)->timer)){
   audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
   job->timer=1;
   frame_request_animation((struct FrameCommandObject *)job->actor,1);
  }
  break;
 }
 if(job->timer==1){
  resource_set_triple(0,1,1);
  ((struct FrameActorObject *)job->actor)->before_step=resource_object_before_step;
  return 2;
 }
 return 1;
}
