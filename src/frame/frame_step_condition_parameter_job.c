#include "frame_need_effect_condition_jobs.h"
#include "frame_need_effect_optional_jobs.h"
#include "resource_conditions.h"
#include "frame_actor_social.h"
unsigned int frame_step_condition_parameter_job(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 if (!job->running) {
  switch ((unsigned int)job->timer) {
  case 0:
   ((struct FrameAttachmentJobWork *)owner)->indicator=frame_create_attachment_parameter_indicator(job->actor,0);
   if (((struct FrameActorObject *)owner->object)->direction<=4)
    frame_set_actor_direction(job->actor,2);
   else
    frame_set_actor_direction(job->actor,6);
   frame_request_animation((struct FrameCommandObject *)job->actor,45);
   job->timer=5;
   ((struct FrameAttachmentJobWork *)owner)->sample=audio_play_animation_cue(19);
   break;
  case 5:
   if ((unsigned char)frame_need_effect_consume_optional(owner,job,((struct FrameAttachmentJobWork *)owner)->indicator)==1) {
    job->timer=1;
    resource_set_triple(1,3,2);
   }
   break;
  }
 } else job->timer=1;
 if (job->timer==1) {
  audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  if (((struct FrameAttachmentJobWork *)owner)->indicator) {
   transition_object_set_state(((struct FrameAttachmentJobWork *)owner)->indicator,1);
   ((struct FrameAttachmentJobWork *)owner)->indicator=0;
  }
  return 2;
 }
 return 1;
}
asm(".align 2, 0");
