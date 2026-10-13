#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_choices.h"
unsigned char frame_actor_route_to_target(struct FrameObject *actor,struct FrameObject *target,unsigned char action)
{
 int cell;
 struct FramePoint point;
 unsigned char result=frame_find_target_cell(g_frame_registration,actor,target,&cell,0);
 if(result==1) {
 frame_grid_cell_to_point(g_frame_registration,&cell,&point);
 frame_point_to_fixed(&point,&point);
 frame_begin_actor_route(actor,&point,&((struct FrameActorStateWork *)actor)->movement_status,0,1);
 frame_set_variant_state(actor,3);
 transition_object_set_state(actor,39);
 frame_request_animation((struct FrameCommandObject *)actor,6);
 ((unsigned char*)actor)[0x6a]=action;
 return 1;
 } else return 0;
}
