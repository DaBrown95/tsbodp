#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_route.h"
#include "frame_actor_grid.h"
unsigned char frame_find_actor_route(struct FrameActorRouteJob *job)
{
 struct FramePoint start,destination;
 struct FrameActorPackedCell start_cell,destination_cell;
 unsigned char finished,result;
 frame_disable_object_flags(job->object,0x10000);
 start.x=((short*)&job->object->position)[1];
 start.y=((short*)&job->object->position)[3];
 destination.x=((short*)&job->destination)[1];
 destination.y=((short*)&job->destination)[3];
 frame_grid_point_to_cell(g_frame_registration,&start,&start_cell);
 frame_grid_point_to_cell(g_frame_registration,&destination,&destination_cell);
 finished=0;result=2;
 if(start_cell.index!=destination_cell.index) {
  unsigned char search=(unsigned char)frame_grid_search(g_frame_registration,&start_cell,&destination_cell,job->limit,1);
  unsigned int status=frame_grid_search_status();
  if(search==1 || (status==2 && job->use_destination==1)) {
   if(status==2) job->unknown_117=1;
   frame_copy_grid_path(job->path,30);
   job->mode=6;
   job->path_index=0;
  } else if(search==2) finished=1;
  else {
   unsigned int next=g_frame_actor_route_modes[job->mode].next;
   if(next!=7) {job->mode=next;result=2;}
   else result=3;
  }
 } else finished=1;
 if(finished==1) {
  if(job->style==1) {job->mode=2;result=2;}
  else result=1;
 }
 return result;
}
asm(".align 2, 0");
