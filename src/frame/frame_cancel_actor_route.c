#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_route.h"
void frame_cancel_actor_route(struct FrameObject *object) { unsigned char index;for(index=0;index<3;index++) { if(g_frame_actor_routes[index].object==object) frame_release_actor_route(index); } }
asm(".align 2, 0");
