#include "frame_actor_attachment_jobs.h"
unsigned int frame_step_attachment_job_73(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 struct FrameActorNeedState *needs=((struct FrameActorObject *)job->actor)->actor_state;
 switch((unsigned int)job->timer) {
 case 0:
  ((struct FrameActorObject *)job->actor)->direction=frame_direction_to_need_effect_center(job->actor,owner);
  if(frame_gate_attachment_game_value(owner,job,5)==1) {
   frame_request_animation((struct FrameCommandObject *)job->actor,58);
   frame_commit_need_effect(owner->object,1);
   job->timer=61;
   audio_play_animation_cue(54);
  }else {
   frame_request_animation((struct FrameCommandObject *)job->actor,5);
   job->timer=9;
  }
  break;
 case 61:
  if(job->actor->flags&0x400000) {
   frame_adjust_actor_needs(needs,51,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
   frame_commit_need_effect(owner->object,3);
   frame_request_animation((struct FrameCommandObject *)job->actor,1);
   ((struct FrameActorStateWork *)job->actor)->timer=60;
   job->timer=89;
  }
  break;
 case 89:
  if((unsigned char)frame_step_attachment_need_timer(job,needs,2,&((struct FrameActorStateWork *)job->actor)->timer)) {
   if(--((struct FrameActorStateWork *)job->actor)->timer==-1) {
    unsigned int random=frame_random_range(0,100),i;
    for(i=0;i<=4;i++)if(random<g_frame_attachment_chances[i].chance)break;
    if(i<=4) {
     frame_gate_attachment_game_value(owner,job,-g_frame_attachment_chances[i].parameter);
     audio_play_animation_cue(55);
     frame_request_animation((struct FrameCommandObject *)job->actor,67);
     job->timer=9;
    }else job->timer=1;
   }
  }else job->timer=1;
  break;
 case 9:
  frame_adjust_actor_needs(needs,51,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if(job->actor->flags&0x400000) {
   job->timer=1;
   frame_request_animation((struct FrameCommandObject *)job->actor,1);
  }
  break;
 case 1:
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  frame_commit_need_effect(owner->object,2);
  return 2;
 }
 return 1;
}
asm(".align 2, 0");
