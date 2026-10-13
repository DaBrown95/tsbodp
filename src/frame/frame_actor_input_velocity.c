#include "frame_actor_needs.h"
#include "input.h"
#include "view_math.h"
void frame_actor_input_velocity(struct FrameObject *object,struct FramePoint *velocity)
{
 if(g_input_current[g_frame_actor_need_input.local_player]&2) {
  frame_make_velocity(velocity,object->flags,((struct FrameActorObject *)object)->direction,(int)(unsigned int)(((struct FrameActorObject *)object)->speed*1.8));
  frame_request_animation((struct FrameCommandObject *)object,4);
 } else {
  frame_make_velocity(velocity,object->flags,((struct FrameActorObject *)object)->direction,((struct FrameActorObject *)object)->speed);
  frame_request_animation((struct FrameCommandObject *)object,6);
 }
}
asm(".align 2, 0");
