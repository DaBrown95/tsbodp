#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "view_math.h"
#include "audio_game.h"
struct FrameActorProximityWork {
 unsigned char unknown_00[0x14]; int speed; struct FramePoint position;
 unsigned char unknown_20[0x2e]; unsigned char variant_state;
 unsigned char unknown_4f[0xf]; unsigned short timer;
 unsigned char unknown_60[4]; int saved_speed;
 unsigned short leave_range, enter_range, turn_delay, wait_delay;
};
void frame_actor_state_44(struct FrameObject *base)
{
 struct FrameActorProximityWork *object=(struct FrameActorProximityWork*)base;
 struct FrameObject *actor=g_frame_actor_need_input.views[g_frame_actor_need_input.local_player].actor;
 if((unsigned char)(object->variant_state-4)>1) {
  /* Constrain this temporary result to preserve the original allocation. */
  register unsigned int distance asm("r1")=view_point_distance(object->position,actor->position)>>16;
  if(distance<object->enter_range) {
   frame_set_variant_state((struct FrameObject*)object,4);
   object->saved_speed=object->speed;
   object->speed=object->saved_speed*2;
   audio_play_animation_cue(179);
   frame_set_actor_direction((struct FrameObject*)object,frame_random_bounded(7));
   object->timer=frame_random_range(10,object->turn_delay);
  }
 }
 switch(object->variant_state) {
 case 3:
  if(--object->timer==65535) {
   frame_set_variant_state((struct FrameObject*)object,7);
   object->timer=frame_random_range(15,object->wait_delay);
  }
  break;
 case 7:
  if(--object->timer==65535) {
   frame_set_variant_state((struct FrameObject*)object,3);
   frame_set_actor_direction((struct FrameObject*)object,frame_random_bounded(7));
   object->timer=frame_random_range(10,object->turn_delay);
  }
  break;
 case 4: {
  /* Constrain this temporary result to preserve the original allocation. */
  register unsigned int distance asm("r1")=view_point_distance(object->position,actor->position)>>16;
  if(distance>object->leave_range) {
   frame_set_variant_state((struct FrameObject*)object,7);
   object->timer=frame_random_range(15,object->wait_delay);
   object->speed=object->saved_speed;
  } else if(--object->timer==65535) {
   frame_set_actor_direction((struct FrameObject*)object,frame_direction_toward((struct FrameObject*)object,actor));
   object->timer=frame_random_range(10,object->turn_delay);
  }
  break;
 }
 case 5:break;
 }
}
