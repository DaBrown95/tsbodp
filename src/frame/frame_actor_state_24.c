#include "frame_actor_runtime.h"
#include "frame_actor_state.h"

void frame_actor_state_24(struct FrameObject *object)
{
 void *target;
 unsigned int action;
 unsigned char used;
 switch (((struct FrameActorObject *)object)->variant_state) {
 case 2:
  frame_actor_choose_walk_direction(object);
  frame_set_variant_state(object, 25);
  frame_request_animation((struct FrameCommandObject *)object, 6);
  ((struct FrameActorStateWork *)object)->timer=90;
  break;
 case 11:
  if (--((struct FrameActorStateWork *)object)->timer == -1) {
   frame_actor_choose_walk_direction(object);
   frame_set_variant_state(object, 25);
   frame_request_animation((struct FrameCommandObject *)object, 6);
   ((struct FrameActorStateWork *)object)->timer=90;
  break;
  }
  break;
 case 25:
  if (--((struct FrameActorStateWork *)object)->timer == -1 || ((struct FrameActorContactWork *)object)->contact) {
   frame_set_variant_state(object, 7);
   frame_set_actor_direction(object, g_actor_wander_directions[frame_random_range(1,7)]);
   ((struct FrameActorStateWork *)object)->timer = 300;
  } else {
   frame_actor_refresh_terrain(object);
  }
  break;
 case 7:
  if (--((struct FrameActorStateWork *)object)->timer == -1) {
   if (frame_find_need_target(object, &target, &action) == 1)
    used=frame_actor_use_target(target,object,(unsigned char)action);
   else
    used=0;
   if (!used) {
    frame_actor_choose_walk_direction(object);
    frame_request_animation((struct FrameCommandObject *)object, 6);
    frame_set_variant_state(object, 25);
    ((struct FrameActorStateWork *)object)->timer=90;
   }
  }
  break;
 }
}
asm(".align 2, 0");
