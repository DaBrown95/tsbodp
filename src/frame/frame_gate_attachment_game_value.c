#include "frame_actor_attachment_jobs.h"
unsigned char frame_gate_attachment_game_value(struct FrameNeedEffectState *owner, struct FrameActorAttachmentRecord *job, int amount)
{
 if(job->actor==g_need_effect_player) {
  if(((struct FrameActorValueWorld *)&g_resource_game_state)->value<amount)return 0;
  frame_add_game_value(-amount);
  audio_play_animation_cue(5);
 }
 return 1;
}
asm(".align 2, 0");
