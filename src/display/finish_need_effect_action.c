#include "display_need_effect_update.h"
static inline struct ConditionActorEntries *current_entry_list(void)
{
 register unsigned char *state asm("r0")=g_need_effect_game_state;
 return *(struct ConditionActorEntries **)(state+0xf0);
}
void frame_need_effect_finish_action(struct FrameObject *base)
{
 struct FrameNeedEffectObject *object=(struct FrameNeedEffectObject *)base;
 switch(object->unknown_4e[0]) {
 case 0:
  if((unsigned char)actor_entry_has_space(current_entry_list())) {
   transition_object_set_state(((struct DisplayNeedEffectActorView *)object)->actor,0);
   frame_request_animation((struct FrameCommandObject *)((struct DisplayNeedEffectActorView *)object)->actor,32);
   frame_set_variant_state(base,14);
   audio_play_animation_cue(8);
   ((struct DisplayNeedEffectActorView *)object)->timer=8;
  } else {
   transition_object_set_state(((struct DisplayNeedEffectActorView *)object)->actor,16);
   frame_set_variant_state(((struct DisplayNeedEffectActorView *)object)->actor,2);
   frame_reset_need_effect(base);
   g_need_effect_saved_objects[g_need_effect_save_state[49]].flags|=0x200000;
  }
  break;
 case 14:
  if(--((struct DisplayNeedEffectActorView *)object)->timer==-1) {
   frame_set_variant_state(base,15);
   frame_need_effect_restore_audio(base);
   if((unsigned char)actor_entry_add(current_entry_list(),object->kind,object->effect_state->optional,object->effect_state->parameter>>8)==1)
    frame_disable_object_flags(base,1);
   else frame_reset_need_effect(base);
  }
  break;
 case 15:
  if(((struct DisplayNeedEffectActorView *)object)->actor->flags&0x400000) {
   transition_object_set_state(base,1);
   frame_enable_object_flags(base,2);
   transition_object_set_state(((struct DisplayNeedEffectActorView *)object)->actor,16);
   frame_set_variant_state(((struct DisplayNeedEffectActorView *)object)->actor,2);
   frame_request_animation((struct FrameCommandObject *)((struct DisplayNeedEffectActorView *)object)->actor,1);
  }
  break;
 }
}
asm(".align 2, 0");
