#include "frame_placement_session.h"
unsigned char frame_placement_move(unsigned int direction)
{
 struct { unsigned int x:8,y:8,unknown:16; } cell;
 struct FramePoint point;
 int dx;
 unsigned char dy;
 struct FramePlacementSession *session;
 unsigned int axis=g_frame_interaction_directions[direction];
 session=&g_frame_placement_session;
 cell.x=((unsigned char *)&session->selected)[0]+g_frame_placement_steps[axis][0];
 cell.y=((unsigned char *)&session->selected)[1]+g_frame_placement_steps[axis][1];
 dx=(unsigned char)(((unsigned char *)&session->original_cell)[0]-cell.x);
 dy=(signed char)(((unsigned char *)&session->original_cell)[1]-cell.y);
 dx=(signed char)dx;
 if(dx<0)dx=-dx;
 if(dx<=20) {
  int abs_y=(signed char)dy;
  if(abs_y<0)abs_y=-abs_y;
  if(abs_y<=20 && frame_grid_cell_corner(session->grid,(const int *)&cell,&point)==1) {
   if(frame_grid_project_effect_point(session->grid,&point,((struct FrameNeedEffectObject *)session->preview)->direction,&point)) {
    session->preview->position.x=point.x<<16;
    session->preview->position.y=point.y<<16;
    session->selected=*(struct FrameActorPackedCell *)&cell;
    frame_set_actor_direction(session->actor,frame_direction_toward(session->actor,session->preview));
   }
  }
 }
 return frame_placement_validate();
}

asm(".align 2,0");
