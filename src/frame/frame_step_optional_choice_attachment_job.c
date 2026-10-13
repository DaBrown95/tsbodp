#include "frame_need_effect_optional_choice.h"
static inline void end_choice(struct FrameActorAttachmentRecord *job)
{
 job->timer=18;
 frame_request_animation((struct FrameCommandObject *)job->actor,30);
}
static inline void cancel_choice(struct FrameActorAttachmentRecord *job)
{
 if(!frame_world_in_idle_exclusion_set(g_frame_world_id) && g_frame_world_id!=28)frame_add_game_value(1);
 end_choice(job);
}
unsigned int frame_step_optional_choice_attachment_job(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 switch((unsigned int)job->timer) {
 case 0:
  frame_set_actor_direction(job->actor,g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction]);
  frame_need_effect_try_optional(owner);
  job->timer=6;
  if(!frame_world_in_idle_exclusion_set(g_frame_world_id) && g_frame_world_id!=28 && !frame_gate_attachment_game_value(owner,job,1)) {
   frame_request_animation((struct FrameCommandObject *)job->actor,5);
   if(!g_frame_interaction_settings.attachment_mode)audio_play_animation_cue(86);
   else audio_play_animation_cue(85);
   job->timer=8;
  }
  break;
 case 8:
  if(job->actor->flags&0x400000)job->timer=1;
  break;
 case 6:
  g_optional_choice_selection=4;
  frame_request_animation((struct FrameCommandObject *)job->actor,30);
  job->timer=14;
  break;
 case 14:
  if(job->actor->flags&0x400000) {
   job->timer=15;
   frame_request_animation((struct FrameCommandObject *)job->actor,31);
   ((struct FrameAttachmentPhaseClock *)job->actor)->counter=30;
   frame_optional_choice_begin();
  }
  break;
 case 15:
  if(!frame_world_in_idle_exclusion_set(g_frame_world_id) && !g_need_effect_choice_state.index)g_need_effect_choice_state.index=1;
  switch((unsigned int)g_need_effect_choice_state.index) {
  case 0:
   job->timer=16;
   frame_optional_choice_open_secondary();
   break;
  case 1:
   job->timer=17;
   g_optional_choice_page=0;
   frame_optional_choice_refresh();
   break;
  case (unsigned int)-1:cancel_choice(job);break;
  }
  break;
 case 16:
  {
  g_optional_choice_selection=g_need_effect_choice_state.index;
  switch((unsigned int)g_need_effect_choice_state.index) {
  case 0:frame_optional_choice_apply(0,job);break;
  case 1:frame_optional_choice_apply(2,job);break;
  case 2:frame_optional_choice_apply(3,job);break;
  case 3:frame_optional_choice_apply_special();break;
  case (unsigned int)-1:cancel_choice(job);break;
  }}
  break;
 case 17:
  {unsigned int choice=g_need_effect_choice_state.index;
  switch(choice) {
  default:frame_optional_choice_apply_page((unsigned char)(g_optional_choice_page+choice-1),job);break;
  case 0: {
   unsigned int page=g_optional_choice_page+4;
   g_optional_choice_page=page;
   if((unsigned char)page>=g_optional_choice_count)g_optional_choice_page=0;
   frame_optional_choice_refresh();
  }break;
  case (unsigned int)-1:cancel_choice(job);break;
  }
  }
  break;
 case 19:
  if(--((struct FrameAttachmentPhaseClock *)job->actor)->counter==65535)end_choice(job);
  break;
 case 18:
  if(job->actor->flags&0x400000) {
   frame_request_animation((struct FrameCommandObject *)job->actor,1);
   job->timer=1;
   audio_play_animation_cue(176);
   switch((int)g_optional_choice_selection) {
   case 0:frame_optional_choice_complete(0);break;
   case 1:frame_optional_choice_complete(2);break;
   case 2:frame_optional_choice_complete(3);break;
   }
  }
  break;
 }
 if(job->timer==1)return 2;
 return 1;
}
asm(".align 2, 0");
