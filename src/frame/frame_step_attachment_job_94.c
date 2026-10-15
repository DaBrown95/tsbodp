#include "frame_actor_attachment_jobs_42_94.h"
unsigned int frame_step_attachment_job_94(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 struct FrameActorNeedState *needs=((struct FrameActorObject *)job->actor)->actor_state;
 unsigned int result=1;
 int previous;
 if(job->running==1)job->timer=1;
 switch((unsigned int)job->timer) {
 case 0:
  previous=frame_read_signed_parameter(g_frame_actor_social_probe,2);
  ((struct FrameAttachmentJobWork *)owner)->indicator=0;
  if(previous!=10) {
   ((struct FrameAttachmentJobWork *)owner)->indicator=frame_create_attachment_parameter_indicator(job->actor,1);
   ((struct FrameActorObject *)job->actor)->direction=frame_direction_to_need_effect_center(job->actor,owner);
  }
  frame_set_actor_direction(job->actor,((struct FrameActorObject *)owner->object)->direction);
  frame_commit_need_effect(owner->object,3);
  frame_request_animation((struct FrameCommandObject *)job->actor,35);
  audio_game_stop_sequence();
  audio_select_sequence(g_attachment_job_94_sequence_rows[frame_read_signed_parameter(g_frame_actor_social_probe,2)][0]);
  job->timer=64;
  ((struct FrameActorStateWork *)job->actor)->timer=150;
  break;
 case 64:
  previous=frame_read_signed_parameter(g_frame_actor_social_probe,2);
  if(previous==10)frame_adjust_actor_needs(needs,16,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  else frame_adjust_actor_needs(needs,35,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if(previous!=10) {
   unsigned char percentage=frame_read_parameter_percentage(g_frame_actor_social_probe,2);
   frame_set_attachment_parameter_indicator(((struct FrameAttachmentJobWork *)owner)->indicator,percentage);
   frame_update_attachment_parameter(g_frame_actor_social_probe,2,((struct FrameAttachmentJobWork *)owner)->indicator);
   if(frame_read_signed_parameter(g_frame_actor_social_probe,2)==previous+1)job->timer=1;
  } else if(--((struct FrameActorStateWork *)job->actor)->timer==-1)job->timer=1;
  if((unsigned char)frame_step_attachment_need_timer(job,needs,6,&((struct FrameActorStateWork *)job->actor)->timer)==0)job->timer=1;
  break;
 case 1:
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  frame_commit_need_effect(owner->object,2);
  if(((struct FrameAttachmentJobWork *)owner)->indicator) {
   transition_object_set_state(((struct FrameAttachmentJobWork *)owner)->indicator,1);
   ((struct FrameAttachmentJobWork *)owner)->indicator=0;
  }
  audio_game_stop_sequence();
  audio_select_sequence(scene_audio_for_period(g_scene_context.period));
  result=2;
  break;
 }
 return result;
}
