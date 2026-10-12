#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_social.h"
#include "frame_actor_distance.h"
unsigned short frame_random_bounded(unsigned short);
void frame_actor_follow_target(struct FrameObject *object,struct FrameObject *target)
{
 unsigned char direction=frame_direction_toward(object,target);
 unsigned char terrain=frame_actor_terrain_step(object,direction);
 unsigned short choice;
 if(direction!=((struct FrameActorObject *)object)->direction)frame_set_actor_direction(object,direction);
 if(terrain<=1||terrain==36)return;
 choice=frame_random_bounded(1);
 direction=g_actor_obstacle_directions[choice+((struct FrameActorObject *)object)->direction*2];
 /* Constrain this argument lifetime for the original call scheduling. */
 {register unsigned char argument asm("r1")=direction;terrain=frame_actor_terrain_step(object,argument);}
 if(terrain>1&&terrain!=36) {
  if(choice==0)choice=1;else choice=0;
  direction=g_actor_obstacle_directions[choice+((struct FrameActorObject *)object)->direction*2];
  choice=direction;
  terrain=frame_actor_terrain_step(object,choice);
  if(terrain>1&&terrain!=36) {
   frame_set_actor_direction(object,choice);
   frame_set_variant_state(object,7);
   ((struct FrameActorFollowWork *)object)->timer=10;
   return;
  }
 }
 /* Constrain this argument lifetime for the original call scheduling. */
 {register unsigned char argument asm("r1")=direction;frame_set_actor_direction(object,argument);}
 frame_set_variant_state(object,13);
 ((struct FrameActorFollowWork *)object)->timer=20;
}
asm(".align 2, 0");
