#include "frame_need_effect_optional_completion.h"
unsigned int frame_step_optional_attachment_kind_12(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 unsigned int result=1;
 if(job->running==1)job->timer=1;
 switch((unsigned int)job->timer) {
 case 0:
  frame_set_actor_direction(job->actor,g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction]);
  frame_request_animation((struct FrameCommandObject *)job->actor,14);
  job->timer=4;
  ((struct FrameAttachmentJobWork *)owner)->sample=audio_play_animation_cue(26);
  break;
 case 4:
  frame_adjust_actor_needs(((struct FrameActorObject *)job->actor)->actor_state,52,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if((unsigned char)frame_need_effect_consume_optional_two(owner)==1)job->timer=1;
  break;
 case 1:
  audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  result=2;
  break;
 }
 return result;
}
