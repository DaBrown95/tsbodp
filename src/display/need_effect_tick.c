#include "display_need_effect_update.h"
void frame_need_effect_tick(struct FrameObject *base)
{

 switch(((struct FrameNeedEffectObject *)base)->state) {
 case 0:case 2:case 4:case 5:case 6:case 7:case 8:case 9:case 10:case 11:case 12:case 13:case 14:case 16:case 17:break;
 case 1:frame_enable_object_flags(base,2);break;
 case 3:transition_object_set_state(base,0);break;
 case 15:
  switch(((struct FrameNeedEffectObject *)base)->unknown_4e[0]) {
  case 0:frame_set_variant_state(base,55);break;
  case 55:frame_need_effect_choose_action(base);break;
  }
  break;
 case 18:frame_need_effect_finish_action(base);break;
 }
 if(((struct FrameNeedEffectObject *)base)->direction>4)((struct FrameNeedEffectObject *)base)->oam.flip_x=1;
 else ((struct FrameNeedEffectObject *)base)->oam.flip_x=0;
 if(((struct FrameNeedEffectObject *)base)->mode==1)frame_step_need_effect_attachments(((struct FrameNeedEffectObject *)base)->effect_state);
}
asm(".align 2, 0");
