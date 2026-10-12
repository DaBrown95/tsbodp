#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_route.h"
unsigned char frame_begin_actor_route(struct FrameObject *object, struct FramePoint *destination, unsigned int *status, unsigned int mode, unsigned char style)
{
 unsigned char result=0,index;
 for(index=0;index<3;index++) {
  if(!g_frame_actor_routes[index].object) {
   g_frame_actor_routes[index].object=object;
   g_frame_actor_routes[index].destination.x=destination->x;
   g_frame_actor_routes[index].destination.y=destination->y;
   g_frame_actor_routes[index].delta.x=0;
   g_frame_actor_routes[index].delta.y=0;
   g_frame_actor_routes[index].status=status;
   g_frame_actor_routes[index].mode=mode;
   g_frame_actor_routes[index].flags=object->flags&0x10240;
   g_frame_actor_routes[index].style=style;
   g_frame_actor_routes[index].use_destination=0;
   g_frame_actor_routes[index].unknown_117=0;
   g_frame_actor_routes[index].limit=200;
   frame_enable_object_flags(object,0x1000000);
   *g_frame_actor_routes[index].status=2;
   g_frame_actor_route_count++;
   result=1;
   break;
  }
 }
 return result;
}
asm(".align 2, 0");
