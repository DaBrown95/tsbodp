#include "frame_placement_session.h"
unsigned char frame_placement_begin(void *grid,struct FrameObject *actor,struct FrameObject *effect)
{
 unsigned char width,height,result;
 struct FramePoint actor_position,position,view_size;
 frame_placement_reset_parameter(effect);
 g_frame_placement_session.effect=effect;
 g_frame_placement_session.actor=actor;
 g_frame_placement_session.grid=grid;
 g_frame_placement_session.original_position=effect->position;
 g_frame_placement_session.original_direction=((struct FrameNeedEffectObject *)effect)->direction;
 g_frame_placement_session.preview=frame_placement_create_preview(effect);
 frame_disable_object_flags(g_frame_placement_session.effect,1);
 actor_position.x=((short *)&g_frame_placement_session.actor->position.x)[1];
 actor_position.y=((short *)&g_frame_placement_session.actor->position.y)[1];
 frame_grid_point_to_cell(g_frame_placement_session.grid,&actor_position,&g_frame_placement_session.original_cell);
 if(((struct FramePlacementActor *)g_frame_placement_session.actor)->mode==1) {
  unsigned char facing;
  frame_need_effect_pattern_dimensions(g_need_effect_action_sets[((struct FrameNeedEffectObject *)g_frame_placement_session.preview)->kind],&width,&height);
  facing=g_frame_interaction_directions[((struct FrameNeedEffectObject *)g_frame_placement_session.actor)->direction];
  switch(facing) {
  case 0:
   ((unsigned char *)&g_frame_placement_session.selected)[0]=((unsigned char *)&g_frame_placement_session.original_cell)[0]-(width>>1);
   ((unsigned char *)&g_frame_placement_session.selected)[1]=((unsigned char *)&g_frame_placement_session.original_cell)[1]-height;break;
  case 2:
   ((unsigned char *)&g_frame_placement_session.selected)[0]=((unsigned char *)&g_frame_placement_session.original_cell)[0]+1;
   ((unsigned char *)&g_frame_placement_session.selected)[1]=((unsigned char *)&g_frame_placement_session.original_cell)[1]-(height>>1);break;
  case 4:
   ((unsigned char *)&g_frame_placement_session.selected)[0]=((unsigned char *)&g_frame_placement_session.original_cell)[0]-(width>>1);
   ((unsigned char *)&g_frame_placement_session.selected)[1]=((unsigned char *)&g_frame_placement_session.original_cell)[1]+1;break;
  case 6:
   ((unsigned char *)&g_frame_placement_session.selected)[0]=((unsigned char *)&g_frame_placement_session.original_cell)[0]-width;
   ((unsigned char *)&g_frame_placement_session.selected)[1]=((unsigned char *)&g_frame_placement_session.original_cell)[1]-(height>>1);break;
  }
  if(frame_grid_cell_corner(g_frame_placement_session.grid,(const int *)&g_frame_placement_session.selected,&position)) {
   g_frame_placement_session.preview->position.x=position.x<<16;
   g_frame_placement_session.preview->position.y=position.y<<16;
  }
 } else {
  position.x=((short *)&g_frame_placement_session.preview->position.x)[1];
  position.y=((short *)&g_frame_placement_session.preview->position.y)[1];
  frame_grid_point_to_cell(g_frame_placement_session.grid,&position,&g_frame_placement_session.selected);
 }
 result=frame_placement_validate();
 frame_placement_update_graphic();
 view_size.x=30;view_size.y=30;
 transition_configure_view((struct TransitionViewObject *)g_frame_placement_session.preview,view_size,0);
 return result;
}

asm(".align 2,0");
