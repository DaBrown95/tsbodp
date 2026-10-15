#include "frame_need_effect_secondary_header_jobs.h"
unsigned int frame_step_secondary_header_attachment_job_50(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 struct FrameActorNeedState *needs=((struct FrameActorObject *)job->actor)->actor_state;
 unsigned int result=1;
 switch((unsigned int)job->timer){
 case 0:
  owner->parameter=2560;
  owner->optional=2;
  ((struct FrameActorObject *)job->actor)->direction=g_secondary_header_attachment_directions_two[((struct FrameActorObject *)owner->object)->direction];
  if(((unsigned char *)&job->unknown14)[0]==0)
   frame_attachment_position(owner->object,1,&((struct FrameActorObject *)job->actor)->position);
  else frame_attachment_position(owner->object,4,&((struct FrameActorObject *)job->actor)->position);
  job->timer=34;
  frame_request_animation((struct FrameCommandObject *)job->actor,12);
  frame_need_effect_handoff_bounds(job->actor,owner,1);
  break;
 case 34:
  if(job->actor->flags&0x400000){
   frame_commit_need_effect(owner->object,2);
   audio_play_animation_cue(66);
   frame_clear_animation_pending(job->actor);
   ((struct FrameAttachmentJobWork *)owner)->sample=audio_play_animation_cue(142);
   job->timer=35;
   ((struct FrameActorStateWork *)job->actor)->timer=120;
  }
  break;
 case 35:
  {
   register struct FrameObject *header_actor asm("r0");
   struct FrameObject *actor;
   unsigned int identity,key;
   unsigned int special;
   unsigned char finished;
   frame_adjust_actor_needs(needs,26,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
   if(job->actor==g_need_effect_player)frame_set_actor_need_step_mode(1);
   header_actor=job->actor;
   identity=((struct FrameSecondaryHeaderActorWord *)header_actor)->header.word;
   key=0x001e0007;
   special=0;
   actor=header_actor;
   if(identity==key)special=1;
   if(special==1){
    unsigned char delta=(unsigned char)(((struct FrameActorClockState *)&g_resource_game_state)->clock-5);
    finished=0;
    if(delta<=16)goto check_completion;
    break;
   }else{
    if((unsigned char)(((struct FrameActorClockState *)&g_resource_game_state)->clock-5)<=17||job->running==1)
     finished=(unsigned char)frame_step_attachment_need_timer(job,needs,2,&((struct FrameActorStateWork *)actor)->timer);
    else break;
   }
  check_completion:
   if(!finished){
    if(((unsigned char *)&job->unknown14)[0]==0)
     frame_attachment_position(owner->object,1,&((struct FrameActorObject *)job->actor)->position);
    else frame_attachment_position(owner->object,4,&((struct FrameActorObject *)job->actor)->position);
    audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
    job->timer=36;
    frame_request_animation((struct FrameCommandObject *)job->actor,11);
   }
  }
  break;
 case 36:
  if(job->actor->flags&0x400000){
   if(((unsigned char *)&job->unknown14)[0]==0)
    frame_attachment_position(owner->object,0,&((struct FrameActorObject *)job->actor)->position);
   else frame_attachment_position(owner->object,3,&((struct FrameActorObject *)job->actor)->position);
   frame_request_animation((struct FrameCommandObject *)job->actor,1);
   job->timer=1;
  }
  break;
 case 1:
  resource_set_triple(0,1,1);
  ((struct FrameActorObject *)job->actor)->before_step=resource_object_before_step;
  if(frame_need_effect_attachment_count(owner)==1)((struct FrameSecondaryHeaderOwnerWork *)owner)->active=0;
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  result=2;
  break;
 }
 return result;
}
