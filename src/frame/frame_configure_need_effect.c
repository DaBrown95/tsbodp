#include "frame_need_effect_placement.h"

unsigned char frame_configure_need_effect(struct FrameObject *base, int direction, int x, int y)
{
 struct FrameNeedEffectObject *object=(struct FrameNeedEffectObject *)base;
 struct FramePoint requested={(short)x,(short)y},position;
 struct FrameActorPackedCell cell;
 unsigned char result;
 object->direction=direction;
 if(!frame_grid_project_effect_point(g_frame_registration,&requested,object->direction,&position)) {
  position.x=(short)x;
  position.y=(short)y;
 }
 frame_set_position((struct FrameObject *)object,position.x<<16,position.y<<16);
 if(frame_need_effect_action_available(object->effect_state,2)) {
  struct FrameNeedEffectState *neighbor;
  frame_grid_point_to_cell(g_frame_registration,&position,&cell);
  neighbor=frame_need_effect_find_neighbor(&cell,3);
  if(neighbor)frame_need_effect_handoff_bounds((struct FrameObject *)object,neighbor,1);
 }
 frame_enable_object_flags((struct FrameObject *)object,1);
 result=frame_need_effect_register_3b12c(g_frame_registration,(struct FrameObject *)object,1);
 frame_update_need_effect((struct FrameObject *)object);
 if(object->direction>4)object->oam.flip_x=1;
 else object->oam.flip_x=0;
 return result;
}
asm(".align 2,0");
