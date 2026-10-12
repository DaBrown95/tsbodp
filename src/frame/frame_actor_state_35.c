#include "frame_actor_runtime.h"
#include "frame_actor_state.h"

void frame_actor_state_35(struct FrameObject *object)
{
 void *target, *need_target;
 unsigned int action;
 unsigned char used, need_used;
 switch (((struct FrameActorObject *)object)->variant_state) {
 case 2:
  frame_request_animation((struct FrameCommandObject *)object, 1);
  frame_set_variant_state(object, 7);
  ((struct FrameActorStateWork *)object)->timer=frame_random_range(150,300);
  break;
 case 7:
  if (--((struct FrameActorStateWork *)object)->timer == -1) {
   used=0;
   if ((object->flags & 0x800000) && frame_begin_actor_route(object,&object->destination,&((struct FrameActorStateWork *)object)->movement_status,0,0)==1) {
    frame_route_enable_destination(object);
    frame_route_set_limit(object,200);
    frame_request_animation((struct FrameCommandObject *)object,6);
    frame_set_variant_state(object,45);
    break;
   }
   if (g_frame_world_id==28 && ((struct FrameActorObject *)object)->subtype==30 && (unsigned char)(((struct FrameActorClockState *)&g_resource_game_state)->clock-5)>16 && frame_find_action_target(object,50,&target)==1)
    used=frame_actor_use_target(target,object,50);
   if ((g_frame_world_id==41 || g_frame_world_id==26 || g_frame_world_id==37) && frame_random_chance(60) &&
       (((struct FrameActorObject *)object)->subtype==22 || ((struct FrameActorObject *)object)->subtype==26 || ((struct FrameActorObject *)object)->subtype==28 || ((struct FrameActorObject *)object)->subtype>31)) {
    if (frame_find_action_target(object,18,&target)==1)
     used=frame_actor_use_target(target,object,18);
    goto actions_done;
   }
   if (((struct FrameActorObject *)object)->subtype==21) {
    if (frame_random_chance(10)==1 && frame_find_action_target(object,46,&target)==1)
     used=frame_actor_use_target(target,object,46);
   } else if (((struct FrameActorObject *)object)->subtype==24) {
    if (frame_random_chance(10)==1) {
     if (frame_find_action_target(object,14,&target)==1)
      used=frame_actor_use_target(target,object,14);
    } else if ((g_frame_world_id==2 && object->position.x<=0x1e9ffff && object->position.y>0x33e0000) ||
               (g_frame_world_id==7 && object->position.x<=0x23effff && object->position.y>0x2d50000)) {
     used=1;
     frame_stop_motion(object);
     frame_request_animation((struct FrameCommandObject *)object,92);
     frame_set_variant_state(object,41);
     ((struct FrameActorStateWork *)object)->timer=300;
     frame_set_actor_direction(object,4);
    }
   } else if (((struct FrameActorObject *)object)->subtype==20) {
    if (g_frame_world_id==0 && frame_random_chance(10)==1) {
     used=1;
     frame_stop_motion(object);
     frame_request_animation((struct FrameCommandObject *)object,91);
     frame_set_variant_state(object,41);
     ((struct FrameActorStateWork *)object)->timer=450;
    }
   } else if (((struct FrameActorObject *)object)->subtype==28) {
    if (frame_random_chance(5)==1 && frame_find_action_target(object,49,&target)==1)
     used=frame_actor_use_target(target,object,49);
   } else if (((struct FrameActorObject *)object)->subtype==18) {
    if (frame_random_chance(5)==1 && frame_find_action_target(object,7,&target)==1)
     used=frame_actor_use_target(target,object,7);
   }
actions_done:
   if (used)
    break;
   if (((struct FrameActorObject *)object)->subtype>31 && frame_random_chance(30)==1) {
    used=1;
    frame_set_variant_state(object,61);
   }
   if (used)
    break;
   goto wander;
  } else {
   frame_actor_state_46(object);
  }
  break;
 case 62:
  if ((object->flags & 0x400000) || --((struct FrameActorStateWork *)object)->timer==-1)
   frame_set_variant_state(object,2);
  break;
 case 63:
  if (object->flags & 0x400000)
   frame_set_variant_state(object,2);
  break;
 case 41:
  if (--((struct FrameActorStateWork *)object)->timer==-1)
   frame_set_variant_state(object,2);
  break;
 case 25:
  if (--((struct FrameActorStateWork *)object)->timer==-1) {
   frame_set_variant_state(object,2);
  } else {
   if (((struct FrameActorContactWork *)object)->contact) {
    frame_request_animation((struct FrameCommandObject *)object,1);
    frame_set_actor_direction(object,g_actor_reverse_directions[((struct FrameActorObject *)object)->direction]);
    frame_set_variant_state(object,7);
    ((struct FrameActorStateWork *)object)->timer=30;
   }
   frame_actor_refresh_terrain(object);
  }
  break;
 case 61:
  if (frame_find_need_target(object,&need_target,&action)==1)
   need_used=frame_actor_use_target(need_target,object,(unsigned char)action);
  else
   need_used=0;
  if (need_used)
   break;
  goto wander;
 case 45:
  if (((struct FrameActorStateWork *)object)->movement_status!=2) {
   if (((struct FrameActorStateWork *)object)->movement_status==3 || ((struct FrameActorStateWork *)object)->movement_status==0) {
    frame_cancel_actor_route(object);
wander:
    frame_request_animation((struct FrameCommandObject *)object,6);
    frame_set_variant_state(object,25);
    ((struct FrameActorStateWork *)object)->timer=frame_random_range(30,90);
    frame_actor_choose_walk_direction(object);
   } else if (((struct FrameActorStateWork *)object)->movement_status==1) {
    frame_cancel_actor_route(object);
    transition_object_set_state(object,1);
   }
  }
  break;
 }
}
asm(".align 2, 0");
