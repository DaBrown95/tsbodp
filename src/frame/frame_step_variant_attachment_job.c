#include "frame_actor_attachment_parameters.h"
unsigned int frame_step_variant_attachment_job(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 int previous=0;
 unsigned int variant=owner->unknown_58[6];
 struct FrameActorNeedState *needs=((struct FrameActorObject *)job->actor)->actor_state;
 unsigned int result=1;
 switch((unsigned int)job->timer) {
 case 0:
  if(owner->kind==47) {
   if(frame_world_in_idle_exclusion_set(g_frame_world_id) || frame_gate_attachment_game_value(owner,job,20)==1)job->timer=6;
   else {
    frame_request_animation((struct FrameCommandObject *)job->actor,5);
    if(!g_frame_interaction_settings.attachment_mode)audio_play_animation_cue(86);
    else audio_play_animation_cue(85);
    job->timer=8;
    break;
   }
  }
  if(frame_attachment_need_is_low(needs,g_frame_attachment_route_variants[variant].timer_need)==1) {
   frame_set_actor_direction(job->actor,4);
   frame_request_animation((struct FrameCommandObject *)job->actor,85);
   if(!g_frame_interaction_settings.attachment_mode)audio_play_animation_cue(137);
   else audio_play_animation_cue(136);
   job->timer=8;
   break;
  }
  if(g_frame_attachment_route_variants[variant].restore_bounds)frame_need_effect_handoff_bounds(job->actor,owner,1);
  if(g_frame_attachment_route_variants[variant].parameter!=7) {
   previous=frame_read_signed_parameter(g_frame_actor_social_probe,g_frame_attachment_route_variants[variant].parameter);
   ((struct FrameAttachmentJobWork *)owner)->indicator=0;
   if(previous!=10) {
    ((struct FrameAttachmentJobWork *)owner)->indicator=frame_create_attachment_parameter_indicator(job->actor,1);
    ((struct FrameActorObject *)job->actor)->direction=frame_direction_to_need_effect_center(job->actor,owner);
   }
  }
  if(g_frame_attachment_route_variants[variant].kind==47 || g_frame_attachment_route_variants[variant].kind==10)
   ((struct FrameActorObject *)job->actor)->direction=g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction];
  else ((struct FrameActorObject *)job->actor)->direction=frame_direction_to_need_effect_center(job->actor,owner);
  job->timer=6;
  frame_request_animation((struct FrameCommandObject *)job->actor,g_frame_attachment_route_variants[variant].animation);
  ((struct FrameActorStateWork *)job->actor)->timer=90;
  frame_commit_need_effect(owner->object,3);
  if(variant==0)owner->object->flags&=~1;
  else if(variant!=3 && g_frame_attachment_route_variants[variant].cue!=255)
   ((struct FrameAttachmentJobWork *)owner)->sample=audio_play_animation_cue(g_frame_attachment_route_variants[variant].cue);
  ((struct FrameAttachmentPhaseClock *)owner->object)->counter=15;
  break;
 case 6:
  if(variant==0 || variant==3) {
   if(((struct FrameAttachmentPhaseClock *)owner->object)->counter++>28) {
    ((struct FrameAttachmentJobWork *)owner)->sample=audio_play_animation_cue(g_frame_attachment_route_variants[variant].cue);
    ((struct FrameAttachmentPhaseClock *)owner->object)->counter=0;
   }
  }
  { unsigned int parameter=g_frame_attachment_route_variants[variant].parameter;
  if(parameter!=7) {
   previous=frame_read_signed_parameter(g_frame_actor_social_probe,parameter);
   if(previous!=10) {
    unsigned char percentage=frame_read_parameter_percentage(g_frame_actor_social_probe,parameter);
    frame_set_attachment_parameter_indicator(((struct FrameAttachmentJobWork *)owner)->indicator,percentage);
    frame_update_attachment_parameter(g_frame_actor_social_probe,parameter,((struct FrameAttachmentJobWork *)owner)->indicator);
   }
  }
  }
  if(g_frame_attachment_route_variants[variant].adjustment_need!=8)
   frame_adjust_actor_needs(needs,g_frame_attachment_route_variants[variant].adjustment_need,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if(g_frame_attachment_route_variants[variant].parameter!=7) {
   if(previous!=10) {
    if(frame_read_signed_parameter(g_frame_actor_social_probe,g_frame_attachment_route_variants[variant].parameter)==previous+1)job->timer=1;
   }else {
    if(--((struct FrameActorStateWork *)job->actor)->timer==-1)job->timer=1;
    frame_adjust_actor_needs(needs,49,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
   }
  }
  if(!(unsigned char)frame_step_attachment_need_timer(job,needs,g_frame_attachment_route_variants[variant].timer_need,&((struct FrameActorStateWork *)job->actor)->timer)) {
   job->timer=1;
   if(g_frame_attachment_route_variants[variant].kind==103) {
    frame_request_animation((struct FrameCommandObject *)job->actor,6);
    frame_begin_actor_route(job->actor,&((struct FrameAttachmentJobWork *)owner)->saved_position,&job->status,5,1);
   }
  }
  if(g_frame_attachment_route_variants[variant].wait_animation)job->timer=9;
  break;
 case 9:
  if(job->actor->flags&0x400000)job->timer=1;
  break;
 case 8:
  if(job->actor->flags&0x400000) {
   job->timer=1;
   frame_request_animation((struct FrameCommandObject *)job->actor,1);
   frame_clear_attachment_need_countdown(needs);
  }
  break;
 case 1:
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  frame_commit_need_effect(owner->object,2);
  if(g_frame_attachment_route_variants[variant].parameter!=7 && ((struct FrameAttachmentJobWork *)owner)->indicator) {
   transition_object_set_state(((struct FrameAttachmentJobWork *)owner)->indicator,1);
   ((struct FrameAttachmentJobWork *)owner)->indicator=0;
  }
  if(g_frame_attachment_route_variants[variant].kind==94)owner->object->flags|=1;
  if(g_frame_attachment_route_variants[variant].restore_bounds)job->actor->before_step=resource_object_before_step;
  if(g_frame_attachment_route_variants[variant].stop_sample)audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
  result=2;
  break;
 }
 return result;
}
