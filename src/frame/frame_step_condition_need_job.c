#include "frame_need_effect_condition_jobs.h"
#include "frame_need_effect_optional_jobs.h"
#include "resource_conditions.h"
#include "frame_actor_social.h"
unsigned int frame_step_condition_need_job(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 struct FrameActorNeedState *needs=((struct FrameActorObject *)job->actor)->actor_state;
 unsigned int result=1;
 if (job->running==1) job->timer=1;
 switch ((unsigned int)job->timer) {
 case 0:
  frame_set_actor_direction(job->actor,7);
  frame_request_animation((struct FrameCommandObject *)job->actor,8);
  job->timer=3;
  ((struct FrameActorObject *)job->actor)->need_timer=90;
  break;
 case 3:
  frame_adjust_attachment_need(needs,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if (!(unsigned char)frame_step_attachment_need_timer(job,needs,7,&((struct FrameActorStateWork *)job->actor)->timer)) {
   job->timer=1;
   frame_request_animation((struct FrameCommandObject *)job->actor,1);
   if (!g_frame_interaction_settings.attachment_mode) audio_play_animation_cue(133);
   else audio_play_animation_cue(132);
  }
  break;
 case 1:
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  result=2;
  break;
 }
 return result;
}
asm(".align 2, 0");
