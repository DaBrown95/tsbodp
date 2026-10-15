#include "frame_shared_optional_jobs.h"
unsigned int frame_shared_optional_timed_step(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 struct FrameActorNeedState *needs=((struct FrameActorObject *)job->actor)->actor_state;
 unsigned int result=1;
 if (job->running==1) job->timer=9;
 switch ((unsigned int)job->timer) {
 case 0:
  frame_need_effect_try_optional(owner);
  frame_set_actor_direction(job->actor,g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction]);
  frame_request_animation((struct FrameCommandObject *)job->actor,63);
  job->timer=6;
  audio_play_animation_cue(165);
  break;
 case 6:
  ((struct FrameAttachmentJobWork *)owner)->sample=audio_play_animation_cue(162);
  ((struct FrameActorStateWork *)job->actor)->timer=90;
  job->timer=53;
  break;
 case 53:
  frame_adjust_actor_needs(needs,32,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if ((((struct FrameActorStateWork *)job->actor)->timer=(int)((unsigned int)((struct FrameActorStateWork *)job->actor)->timer-1u))==-1) job->timer=9;
  break;
 case 9:
  {
   struct FramePoint point;
   frame_attachment_position(owner->object,1,&point);
   frame_request_animation((struct FrameCommandObject *)job->actor,6);
   frame_begin_actor_route(job->actor,&point,&job->status,4,1);
   job->timer=1;
  }
  break;
 case 1:
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  result=2;
  break;
 }
 if (result==2) audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
 return result;
}
