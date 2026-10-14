#include "display_need_effect_update.h"
/* A short serialized-state read; no constrained value survives a call. */
static inline unsigned short game_flag(void)
{
 register unsigned char *state asm("r0")=g_need_effect_game_state;
 return *(unsigned short *)(state+0x744);
}
void frame_update_need_effect(struct FrameObject *base)
{

 struct FrameNeedEffectState *state=((struct FrameNeedEffectObject *)base)->effect_state;
 if(g_need_effect_resources[((struct FrameNeedEffectObject *)base)->kind]) {
  unsigned int palette;
  frame_commit_need_effect(base,((struct FrameNeedEffectObject *)base)->requested_animation);
  if(((struct FrameNeedEffectObject *)base)->subtype==117&&save_world_scene_in_selected_row(g_frame_world_id,1))
   frame_set_animation_frame((struct FrameTickObject *)base,game_flag()!=0);
  palette=g_need_effect_palettes[((struct FrameNeedEffectObject *)base)->kind][state->mode];
  if(palette!=253)frame_acquire_palette_slot(base,palette);
  else switch(((struct FrameNeedEffectObject *)base)->subtype) {
   case 39:frame_set_object_palette(base,&g_need_effect_palette_39);break;
   case 138:frame_set_object_palette(base,&g_need_effect_palette_138);break;
   case 132:frame_set_object_palette(base,&g_need_effect_palette_132);break;
  }
  /* This body writes callback slot +C8, independently of the actor view. */
  if(!*(void **)((unsigned char *)base+0xb0))*(void (**)(struct CollisionObject *,struct CollisionObject *))((unsigned char *)base+0xc8)=0;
  else *(void (**)(struct CollisionObject *,struct CollisionObject *))((unsigned char *)base+0xc8)=frame_need_effect_interact;
 } else {
  *(void (**)(struct CollisionObject *,struct CollisionObject *))((unsigned char *)base+0xc8)=0;
  frame_disable_object_flags(base,17);
 }
 if(((struct FrameNeedEffectObject *)base)->direction>4)((struct FrameNeedEffectObject *)base)->oam.flip_x=1;
 else ((struct FrameNeedEffectObject *)base)->oam.flip_x=0;
}
asm(".align 2, 0");
