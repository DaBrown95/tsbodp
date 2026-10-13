#include "display_need_effect_update.h"
void frame_need_effect_choose_action(struct FrameObject *base)
{
 struct FrameNeedEffectObject *object=(struct FrameNeedEffectObject *)base;
 struct FrameObject *actor=((struct DisplayNeedEffectActorView *)object)->actor;
 struct FrameNeedEffectState *state=object->effect_state;
 unsigned char canceled=0;
 int index=g_need_effect_choice_state.index;
 if(index!=-1) {
  unsigned char *choices=object->effect_choices;
  unsigned char *choice=choices+index;
  if(*choice==40) {
   frame_stop_motion(actor);
   transition_object_set_state(base,18);
   frame_set_variant_state(base,0);
  } else if(*choice==34) {
   frame_stop_motion(actor);
   transition_object_set_state(actor,22);
   frame_set_variant_state(actor,0);
   ((struct DisplayNeedEffectActorView *)actor)->owner=(struct FrameNeedEffectState *)base;
   *((unsigned char *)actor+0x68)=0;
   frame_reset_need_effect(base);
   frame_need_effect_restore_audio(base);
  } else {
   if((unsigned char)((struct DisplayNeedEffectActionState *)state)->begin(state,actor,*choice)==1)
    frame_attach_actor(((struct DisplayNeedEffectActorView *)object)->actor,(struct FrameObject *)state);
   else canceled=1;
   frame_reset_need_effect(base);
  }
 } else {
  canceled=1;
  frame_reset_need_effect(base);
 }
 if(canceled==1) {
  transition_object_set_state(actor,16);
  frame_set_variant_state(actor,2);
 }
}
asm(".align 2, 0");
