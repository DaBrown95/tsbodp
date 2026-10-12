#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_route.h"
void frame_route_set_limit(struct FrameObject *object, unsigned char limit) { unsigned char index;for(index=0;index<3;index++) { if(g_frame_actor_routes[index].object==object) {g_frame_actor_routes[index].limit=limit;break;} } }
asm(".align 2, 0");
