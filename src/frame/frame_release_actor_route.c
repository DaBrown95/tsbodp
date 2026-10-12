#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_route.h"
void *scene_fill_bytes(void *,int,unsigned int);
void frame_release_actor_route(unsigned char index)
{
 frame_disable_object_flags(g_frame_actor_routes[index].object,0x1000000);
 frame_enable_object_flags(g_frame_actor_routes[index].object,g_frame_actor_routes[index].flags);
 *g_frame_actor_routes[index].status=0;
 scene_fill_bytes(&g_frame_actor_routes[index],0,sizeof(struct FrameActorRouteJob));
 g_frame_actor_route_count--;
}
asm(".align 2, 0");
