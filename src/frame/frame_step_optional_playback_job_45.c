#include "frame_optional_playback.h"
unsigned int frame_step_optional_playback_job_45(struct FrameNeedEffectState *owner, struct FrameActorAttachmentRecord *job)
{
 unsigned int result=1;
 if(job->running==1)job->timer=1;
 switch((unsigned int)job->timer){
 case 0:
  frame_set_actor_direction(job->actor,g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction]);
  if((unsigned char)frame_need_effect_try_actor_effect(owner,job->actor)==1){result=2;break;}
  ((struct FrameAttachmentJobWork *)owner)->indicator=frame_create_attachment_parameter_indicator(job->actor,0);
  frame_request_animation((struct FrameCommandObject *)job->actor,46);
  job->timer=5;
  ((struct FrameAttachmentJobWork *)owner)->sample=audio_play_animation_cue(19);
  break;
 case 5:
  if((unsigned char)frame_need_effect_consume_optional(owner,job,((struct FrameAttachmentJobWork *)owner)->indicator)==1){
   job->timer=1;
   resource_set_triple(0,3,2);
  }
  break;
 case 1:
  audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  if(((struct FrameAttachmentJobWork *)owner)->indicator){
   transition_object_set_state(((struct FrameAttachmentJobWork *)owner)->indicator,1);
   ((struct FrameAttachmentJobWork *)owner)->indicator=0;
  }
  result=2;
  break;
 }
 return result;
}
