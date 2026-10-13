#include "frame_grid_selection.h"
unsigned char frame_need_effect_cycle_mode(struct FrameObject *base)
{
 struct FrameNeedEffectObject *object=(struct FrameNeedEffectObject *)base;
 unsigned char result=0;
 if(object->subtype!=82) {
  struct DisplayNeedEffectStateView *state=(struct DisplayNeedEffectStateView *)object->effect_state;
  unsigned char current=state->mode;
  unsigned char next=current+1;
  if(next>5)next=0;
  if(next!=current) {
   state->mode=next;
   frame_acquire_palette_slot(base,g_need_effect_palettes[((struct FrameActorObject *)base)->actor_id][next]);
   result=1;
  }
 }
 return result;
}
asm(".align 2,0");
