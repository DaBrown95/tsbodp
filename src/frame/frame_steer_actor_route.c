#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "view_math.h"
#include "frame_actor_route.h"
unsigned char frame_steer_actor_route(struct FrameActorRouteJob *job)
{
 struct FramePoint destination=job->destination;
 struct FramePoint position=job->object->position;
 unsigned char direction=frame_direction_to_destination(position,destination,((struct FrameActorObject *)job->object)->speed);
 unsigned char contact=((struct FrameActorContactWork *)job->object)->contact!=0;
 unsigned char result;
 if(direction==8) {
  unsigned int style=job->style;
  if(style==1) {job->mode=style;result=2;}
  else result=1;
 } else if(contact==1) {
  job->mode=g_frame_actor_route_modes[job->mode].next;
  result=2;
 } else {
  result=2;
  if(((struct FrameActorObject *)job->object)->direction!=direction)
   frame_set_actor_direction(job->object,direction);
  frame_make_velocity(&job->object->velocity,job->object->flags,direction,((struct FrameActorObject *)job->object)->speed);
  job->delta=position;
 }
 return result;
}
asm(".align 2, 0");
