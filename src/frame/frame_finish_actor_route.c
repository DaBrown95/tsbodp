#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_route.h"
unsigned char frame_finish_actor_route(struct FrameActorRouteJob *job) {frame_set_position(job->object,job->destination.x,job->destination.y);frame_stop_motion(job->object);return 1;}
