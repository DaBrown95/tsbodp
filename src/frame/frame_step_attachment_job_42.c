#include "frame_actor_attachment_jobs_42_94.h"
unsigned int frame_step_attachment_job_42(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 struct FrameActorNeedState *needs=((struct FrameActorObject *)job->actor)->actor_state;
 unsigned int result=1;
 if(job->running==1)job->timer=1;
 switch((unsigned int)job->timer) {
 case 0:
  frame_set_actor_direction(job->actor,((struct FrameActorObject *)owner->object)->direction);
  frame_commit_need_effect(owner->object,3);
  frame_request_animation((struct FrameCommandObject *)job->actor,35);
  ((struct FrameAttachmentJobWork *)owner)->sample=audio_play_animation_cue(70);
  job->timer=64;
  ((struct FrameActorStateWork *)job->actor)->timer=150;
  break;
 case 64:
  frame_adjust_actor_needs(needs,16,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if((unsigned char)frame_step_attachment_need_timer(job,needs,6,&((struct FrameActorStateWork *)job->actor)->timer)==0)job->timer=1;
  break;
 case 1:
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  frame_commit_need_effect(owner->object,2);
  audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
  result=2;
  break;
 }
 return result;
}
