#include "frame_actor_attachment_job_71.h"
unsigned int frame_step_attachment_job_71(struct FrameNeedEffectState *owner, struct FrameActorAttachmentRecord *job)
{
 unsigned int result=1;
 struct FrameActorNeedState *needs=((struct FrameActorObject *)job->actor)->actor_state;
 int previous;
 if(job->running==1)job->timer=1;
 switch((unsigned int)job->timer) {
 case 0:
  if(frame_attachment_need_is_low(needs,8)==1) {
   frame_set_actor_direction(job->actor,4);
   frame_request_animation((struct FrameCommandObject *)job->actor,85);
   if(g_frame_interaction_settings.attachment_mode==0)audio_play_animation_cue(137);
   else audio_play_animation_cue(136);
   job->timer=8;
   break;
  }
  ((struct FrameAttachmentJobWork *)owner)->indicator=0;
  previous=frame_read_signed_parameter(g_frame_actor_social_probe,3);
  if(previous!=10) {
   ((struct FrameAttachmentJobWork *)owner)->indicator=frame_create_attachment_parameter_indicator(job->actor,1);
   ((struct FrameActorObject *)job->actor)->direction=frame_direction_to_need_effect_center(job->actor,owner);
  }
  ((struct FrameActorObject *)job->actor)->direction=frame_direction_to_need_effect_center(job->actor,owner);
  job->timer=80;
  frame_request_animation((struct FrameCommandObject *)job->actor,40);
  ((struct FrameActorStateWork *)job->actor)->timer=90;
  frame_commit_need_effect(owner->object,3);
  ((struct FrameAttachmentJobWork *)owner)->sample=audio_play_animation_cue(34);
  break;
 case 80:
  frame_adjust_actor_needs(needs,12,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  previous=frame_read_signed_parameter(g_frame_actor_social_probe,3);
  if(previous!=10) {
   unsigned char percentage=frame_read_parameter_percentage(g_frame_actor_social_probe,3);
   frame_set_attachment_parameter_indicator(((struct FrameAttachmentJobWork *)owner)->indicator,percentage);
   frame_update_attachment_parameter(g_frame_actor_social_probe,3,((struct FrameAttachmentJobWork *)owner)->indicator);
   if(frame_read_signed_parameter(g_frame_actor_social_probe,3)==previous+1)job->timer=1;
   if(frame_actor_need_fixed_word(needs,2)<=0x13ffffff)job->timer=1;
  } else if(--((struct FrameActorStateWork *)job->actor)->timer==-1)job->timer=1;
  break;
 case 8:
  if(job->actor->flags&0x400000) {
   job->timer=1;
   frame_request_animation((struct FrameCommandObject *)job->actor,1);
   frame_clear_attachment_need_countdown(needs);
  }
  break;
 case 1:
  audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  frame_commit_need_effect(owner->object,2);
  if(((struct FrameAttachmentJobWork *)owner)->indicator) {
   transition_object_set_state(((struct FrameAttachmentJobWork *)owner)->indicator,1);
   ((struct FrameAttachmentJobWork *)owner)->indicator=0;
  }
  result=2;
  break;
 }
 return result;
}
