#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_route.h"
void frame_update_actor_routes(void)
{
 unsigned char index;
 if(g_frame_actor_route_count) {
  for(index=0;index<3;index++) {
   if(g_frame_actor_routes[index].object) {
    struct FrameActorRouteJob *job=&g_frame_actor_routes[index];
    unsigned int status;
    if(job->object->flags&2) frame_release_actor_route(index);
    status=*job->status;
    if(status<=1) goto finished;
    if(status>3) goto invalid;
    {
     if(g_frame_actor_route_modes[job->mode].step) {
      unsigned char result=g_frame_actor_route_modes[job->mode].step(job);
      if(result==1 && job->unknown_117==1) *job->status=3;
      else *job->status=result;
     } else *job->status=3;
    }
    goto next;
finished:
    frame_release_actor_route(index);
    goto next;
invalid:
    frame_release_actor_route(index);
next:;
   }
  }
 }
}
asm(".align 2, 0");
