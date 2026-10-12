#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_route.h"
void frame_route_enable_destination(struct FrameObject *object) { unsigned char index;for(index=0;index<3;index++) { if(g_frame_actor_routes[index].object==object) {g_frame_actor_routes[index].use_destination=1;break;} } }
asm(".align 2, 0");
