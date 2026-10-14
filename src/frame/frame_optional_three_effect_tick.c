#include "frame_optional_three_effect.h"

void frame_optional_three_effect_tick(struct FrameObject *base) {
 struct FrameOptionalThreeEffectObject *object=(struct FrameOptionalThreeEffectObject *)base;
 unsigned int found=0;
 struct FrameOptionalThreeEffectState *state=object->state;
 if(state->active==1 && --object->timer==-1) {
  struct FrameNeedEffectState *node=(struct FrameNeedEffectState *)g_frame_need_effect_active_list.first;
  while(node) {
   if(node->optional==3) {found=1;break;}
   node=((struct DisplayNeedEffectStateView *)node)->next;
  }
  if(!found) {
   frame_commit_need_effect(state->object,2);
   audio_game_stop_sample(state->sample_handle);
   state->active=0;state->field65=0;
   object->on_step=0;
  } else object->timer=10;
 }
}
asm(".align 2, 0");
