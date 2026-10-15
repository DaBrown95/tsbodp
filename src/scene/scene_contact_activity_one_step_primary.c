#include "scene_contact_activity_one.h"
#define STATE ((struct SceneContactActivityOneState*)g_scene_contact_state)
void scene_contact_activity_one_step_primary(struct FrameObject *base) {
 struct FrameActorObject *object=(void*)base;
 switch(object->variant_state) {
 case 0:
  if(!(STATE->flags&2) && (g_input_pressed[0]&1)) {
   frame_set_variant_state((struct FrameObject*)object,1);frame_request_animation((struct FrameCommandObject*)(struct FrameObject*)object,1);
   object->velocity.x=0x48000;object->velocity.y=-0x40000;
   object->acceleration.x=-0x4ccc;object->acceleration.y=0x4ccc;
   ++STATE->attempts;frame_set_animation_frame((struct FrameTickObject*)STATE->secondary,STATE->attempts);
  }break;
 case 1:
  if(frame_object_has_flags((struct FrameObject*)object,0x400000)) {
   frame_set_variant_state((struct FrameObject*)object,3);object->velocity.x=0xccc;object->acceleration.x=0;
   frame_disable_object_flags((struct FrameObject*)object,16);
  }break;
 case 2:
  if(object->position.y>0x4ac0000) {
   frame_set_variant_state((struct FrameObject*)object,5);frame_stop_motion((struct FrameObject*)object);frame_request_animation((struct FrameCommandObject*)(struct FrameObject*)object,8);
   frame_enable_object_flags((struct FrameObject*)object,16);
  } else if(g_input_pressed[0]&64) {
   frame_set_variant_state((struct FrameObject*)object,4);object->acceleration.x=0x3333;
   object->acceleration.y=(int)((unsigned int)object->acceleration.y-0x3333u);
   frame_request_animation((struct FrameCommandObject*)(struct FrameObject*)object,6);frame_enable_object_flags((struct FrameObject*)object,16);
  }break;
 case 3:
  if(object->position.y>0x4500000) {
   frame_set_variant_state((struct FrameObject*)object,2);object->acceleration.y=-0x6666;
   ((struct SceneContactActivityOneObject*)(struct FrameObject*)object)->layer=3;
   scene_contact_activity_one_create_spawn();audio_play_animation_cue(30);
  } else if(g_input_pressed[0]&240) {
   unsigned int animation;
   if(g_input_pressed[0]&16)animation=3;
   else if(g_input_pressed[0]&32)animation=5;
   else if(g_input_pressed[0]&64)animation=4;
   else animation=2;
   frame_set_variant_state((struct FrameObject*)object,11);frame_request_animation((struct FrameCommandObject*)(struct FrameObject*)object,animation);
   object->pending_updates|=4;frame_enable_object_flags((struct FrameObject*)object,16);
  }break;
 case 4:
  if(object->position.y>0x4ac0000 && object->previous_frame<=1) {
   frame_set_variant_state((struct FrameObject*)object,5);frame_stop_motion((struct FrameObject*)object);frame_request_animation((struct FrameCommandObject*)(struct FrameObject*)object,8);
  } else if(frame_object_has_flags((struct FrameObject*)object,0x400000)) {
   frame_set_variant_state((struct FrameObject*)object,6);frame_disable_object_flags((struct FrameObject*)object,16);frame_stop_motion((struct FrameObject*)object);
   ((struct SceneContactActivityOneTimer*)(struct FrameObject*)object)->countdown=30;object->velocity.y=-0x4ccc;scene_contact_activity_one_reward();
  }
  if(object->velocity.y<-32768) {
   object->acceleration.x=0;object->acceleration.y=0;object->velocity.y=-32768;
  }break;
 case 5:
  if(frame_object_has_flags((struct FrameObject*)object,0x400000)) {
   frame_set_variant_state((struct FrameObject*)object,6);frame_disable_object_flags((struct FrameObject*)object,16);
   ((struct SceneContactActivityOneTimer*)(struct FrameObject*)object)->countdown=30;
   if(object->requested_animation==7)object->velocity.y=0x4ccc;
   scene_contact_activity_one_reward();
  }break;
 case 6:
  if(--((struct SceneContactActivityOneTimer*)(struct FrameObject*)object)->countdown==0xffffffffu)STATE->flags|=2;
  break;
 case 11:
  if(object->position.y>0x4500000) {
   frame_set_variant_state((struct FrameObject*)object,5);frame_stop_motion((struct FrameObject*)object);frame_request_animation((struct FrameCommandObject*)(struct FrameObject*)object,7);
   scene_contact_activity_one_create_spawn();audio_play_animation_cue(29);
  }else if(frame_object_has_flags((struct FrameObject*)object,0x400000)) {
   signed char animation;
   frame_set_variant_state((struct FrameObject*)object,3);frame_disable_object_flags((struct FrameObject*)object,16);animation=object->requested_animation;
   if(animation==3)++STATE->counts[1];
   else if(animation==5)++STATE->counts[3];
   else if(animation==4)++STATE->counts[2];
   else ++STATE->counts[0];
  }else if(object->previous_frame==7)((struct SceneContactActivityOneObject*)(struct FrameObject*)object)->layer=3;
  break;
 }
 if(object->velocity.y>0x9cf5c){object->velocity.y=0x9cf5c;object->acceleration.y=0;}
 if((object->pending_updates&22)&&(object->pending_updates&20))
  frame_set_animation_variant((struct FrameObject*)object,object->requested_animation,g_frame_actor_direction_variants_signed[object->direction]);
 object->pending_updates=0;
}
asm(".align 2,0");
