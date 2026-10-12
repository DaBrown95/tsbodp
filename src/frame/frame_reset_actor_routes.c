#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_route.h"
void *scene_fill_bytes(void *,int,unsigned int);
void frame_reset_actor_routes(void) {g_frame_actor_route_count=0;scene_fill_bytes(g_frame_actor_routes,0,3*sizeof(struct FrameActorRouteJob));}
