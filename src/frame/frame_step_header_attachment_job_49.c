#include "frame_need_effect_header_jobs.h"
#include "frame_need_effect_optional_jobs.h"
#include "frame_actor_social.h"
void frame_stop_motion(struct FrameObject *);
#include "frame_actor_idle.h"
unsigned int frame_step_header_attachment_job_49(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 struct FrameActorNeedState *needs=((struct FrameActorObject *)job->actor)->actor_state;
 switch((unsigned int)job->timer){
 case 1:return 2;
 case 0:
  ((struct FrameActorObject *)job->actor)->direction=((struct FrameActorObject *)owner->object)->direction;
  frame_stop_motion(job->actor);
  job->timer=41;
  frame_request_animation((struct FrameCommandObject *)job->actor,50);
  ((struct FrameActorStateWork *)job->actor)->timer=90;
  break;
 case 41:
  if(job->actor->flags&0x400000){audio_play_animation_cue(65);job->timer=43;}
  break;
 case 43:
  frame_adjust_actor_needs(needs,22,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if(!(unsigned char)frame_step_attachment_need_timer(job,needs,4,&((struct FrameActorStateWork *)job->actor)->timer)){
   job->timer=1;frame_request_animation((struct FrameCommandObject *)job->actor,1);
  }
  break;
 case 39:
  frame_adjust_actor_needs(needs,1,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if(!(unsigned char)frame_step_attachment_need_timer(job,needs,4,&((struct FrameActorStateWork *)job->actor)->timer))job->timer=40;
  break;
 }
 if(job->timer==1)return 2;
 return 1;
}
