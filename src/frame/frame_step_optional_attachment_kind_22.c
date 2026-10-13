#include "frame_need_effect_optional_completion.h"
unsigned int frame_step_optional_attachment_kind_22(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 unsigned int result=1;
 if(job->running==1)job->timer=1;
 switch((unsigned int)job->timer) {
 case 0:
  frame_set_actor_direction(job->actor,g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction]);
  frame_request_animation((struct FrameCommandObject *)job->actor,24);
  job->timer=11;
  ((struct FrameAttachmentJobWork *)owner)->sample=audio_play_animation_cue(33);
  break;
 case 11:
  if((unsigned char)frame_need_effect_consume_optional_three(owner)==1)job->timer=1;
  break;
 case 1:
  audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  result=2;
  break;
 }
 return result;
}
asm(".align 2, 0");
