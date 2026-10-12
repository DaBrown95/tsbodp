#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "view_math.h"
#include "frame_actor_route.h"
unsigned char frame_follow_actor_route(struct FrameActorRouteJob *job)
{
 struct FramePoint position=job->object->position;
 unsigned char index=job->path_index;
 struct FramePoint destination;
 unsigned char direction;
 destination.x=job->path[index].x<<16;
 destination.y=job->path[index].y<<16;
 direction=frame_direction_to_destination(position,destination,((struct FrameActorObject*)job->object)->speed);
 if(direction==8) {
  int next=index+1;
  job->path_index=next;
  if(!job->path[next].x && !job->path[next].y) {
   frame_stop_motion(job->object);
   if(job->style==1) job->mode=4;
   else return 1;
  }
 } else {
  if(((struct FrameActorContactWork*)job->object)->contact) return 3;
  if(((struct FrameActorObject*)job->object)->direction!=direction)
   frame_set_actor_direction(job->object,direction);
  frame_make_velocity(&job->object->velocity,job->object->flags,direction,((struct FrameActorObject*)job->object)->speed);
  job->delta=position;
 }
 return 2;
}
asm(".align 2, 0");
