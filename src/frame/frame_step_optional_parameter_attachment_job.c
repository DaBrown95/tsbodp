#include "frame_need_effect_optional_completion.h"
unsigned int frame_step_optional_parameter_attachment_job(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 struct FrameActorNeedState *needs=((struct FrameActorObject *)job->actor)->actor_state;
 unsigned int result=1;
 if(job->running==1)job->timer=1;
 switch((unsigned int)job->timer) {
 case 0:
  if(frame_attachment_need_is_low(needs,8)==1) {
   frame_set_actor_direction(job->actor,4);
   frame_request_animation((struct FrameCommandObject *)job->actor,85);
   if(!g_frame_interaction_settings.attachment_mode)audio_play_animation_cue(137);
   else audio_play_animation_cue(136);
   job->timer=8;
   break;
  }
  ((struct FrameAttachmentJobWork *)owner)->indicator=frame_create_attachment_parameter_indicator(job->actor,1);
  frame_set_actor_direction(job->actor,g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction]);
  frame_request_animation((struct FrameCommandObject *)job->actor,45);
  job->timer=52;
  ((struct FrameAttachmentJobWork *)owner)->sample=audio_play_animation_cue(19);
  break;
 case 52:
  frame_adjust_actor_needs(needs,18,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if((unsigned char)frame_need_effect_step_parameter(owner,g_frame_actor_social_probe,1,((struct FrameAttachmentJobWork *)owner)->indicator)==1)job->timer=1;
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
  if(((struct FrameAttachmentJobWork *)owner)->indicator) {
   transition_object_set_state(((struct FrameAttachmentJobWork *)owner)->indicator,1);
   ((struct FrameAttachmentJobWork *)owner)->indicator=0;
  }
  result=2;
  break;
 }
 return result;
}
