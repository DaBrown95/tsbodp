#include "frame_placement_session.h"
void frame_placement_update_graphic(void)
{
 unsigned char width,height;
 unsigned int kind=((struct FrameNeedEffectObject *)g_frame_placement_session.preview)->kind;
 struct FrameSpriteResource *resource;
 frame_need_effect_pattern_dimensions(g_need_effect_action_sets[kind],&width,&height);
 resource=g_frame_placement_resources[width+height*5];
 if((unsigned int)g_frame_placement_resources+kind*20!=0) {
  unsigned char direction=((struct FrameNeedEffectObject *)g_frame_placement_session.preview)->direction;
  if(direction==1 || direction==7)resource=(struct FrameSpriteResource *)((unsigned char *)resource+16);
  else if(direction==3 || direction==5)resource=(struct FrameSpriteResource *)((unsigned char *)resource+48);
  else goto done;
  frame_set_animation_program(g_frame_placement_session.preview,resource,g_frame_placement_commands,0);
 }
 if(((struct FrameNeedEffectObject *)g_frame_placement_session.preview)->direction>4)((struct FrameNeedEffectObject *)g_frame_placement_session.preview)->oam.flip_x=1;
 else ((struct FrameNeedEffectObject *)g_frame_placement_session.preview)->oam.flip_x=0;
 done:;
}
asm(".align 2,0");
