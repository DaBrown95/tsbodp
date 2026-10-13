#include "frame_scene_effect.h"
void frame_scene_effect_state_8e14(struct FrameObject *base) {
 struct FrameSceneEffectWork *object=(struct FrameSceneEffectWork *)base;
 int cancel,clear_partner;
 if(object->value>0x3d709)object->value+=-0x3d70a;
 cancel=(g_input_pressed[g_input_config.local_player]>>1)&1;
 clear_partner=0;
 switch(object->variant_state) {
 case 0:
  frame_set_variant_state((struct FrameObject *)object,25);
  object->timer=90;
  object->partner=0;
  break;
 case 7:
  if(object->velocity.x || object->velocity.y)frame_stop_motion((struct FrameObject *)object);
  if(--object->timer==-1) {
   if(object->value<=0x4ffffff) {
    struct FrameObject *effect=frame_spawn_need_effect(135,0,0,0,1);
    struct FramePoint point;
    struct FrameActorPackedCell cell;
    unsigned char valid;
    ((struct FrameSceneNeedFields *)effect)->linked=0;
    effect->position.x=object->position.x;
    effect->position.y=object->position.y;
    point.x=((short*)&object->position.x)[1];
    point.y=((short*)&object->position.y)[1];
    valid=frame_grid_point_to_cell(g_frame_registration,&point,&cell);
    if(valid==1) {
     if(!(frame_grid_terrain(g_frame_registration,(int*)&cell)&3))valid=0;
     if(valid==1)valid=frame_configure_need_effect(effect,3,((short*)&object->position.x)[1],((short*)&object->position.y)[1]);
    }
    if(valid!=1) {
     frame_remove_object(effect);
     frame_set_variant_state((struct FrameObject *)object,25);
     object->timer=90;
     object->value=0x14000000;
     audio_play_animation_cue(35);
    } else {
     effect->flags|=0x80000;
     ((struct FrameSceneNeedRender *)effect)->attribute1_high|=12;
     frame_commit_need_effect(effect,1);
     audio_play_animation_cue(35);
     frame_set_variant_state((struct FrameObject *)object,52);
     object->value=0x64000000;
    }
   } else {
    frame_set_variant_state((struct FrameObject *)object,25);
    object->timer=90;
   }
  }
  break;
 case 52:
  if(object->flags&0x400000) {
   frame_set_variant_state((struct FrameObject *)object,7);
   object->timer=frame_random_range(90,300);
  }
  break;
 case 24:
  if(object->flags&0x400000) {
   frame_set_variant_state((struct FrameObject *)object,7);
   object->timer=frame_random_range(90,300);
  }
  break;
 case 25:
  if(--object->timer==-1) {
   frame_set_variant_state((struct FrameObject *)object,7);
   object->timer=frame_random_range(90,300);
  } else frame_scene_effect_walk_972c((struct FrameObject *)object);
  break;
 case 26:
  if(--object->timer==-1) {
   frame_scene_effect_configure((struct FrameObject *)object,0);
   frame_set_variant_state((struct FrameObject *)object,25);
   object->timer=90;
   frame_scene_effect_replenish_9710((struct FrameObject *)object);
   clear_partner=1;
  }
  break;
 case 27:
  if(--object->timer==-1) {
   frame_set_variant_state((struct FrameObject *)object,7);
   object->timer=frame_random_range(90,300);
   frame_scene_effect_replenish_9710((struct FrameObject *)object);
   clear_partner=1;
  }
  break;
 case 28:
  if(--object->timer==-1) {
   frame_set_variant_state((struct FrameObject *)object,7);
   object->timer=frame_random_range(90,300);
   frame_scene_effect_replenish_9710((struct FrameObject *)object);
   clear_partner=1;
  } else frame_scene_effect_follow_9758((struct FrameObject *)object);
  break;
 case 29:
  if(--object->timer==-1) {
   frame_set_variant_state((struct FrameObject *)object,28);
   object->timer=1800;
  }
  break;
 case 30:
  if(--object->timer==-1 || cancel) {
   transition_object_set_state(object->partner,((struct FrameActorObject *)object->partner)->default_state);
   frame_set_variant_state(object->partner,2);
   frame_set_variant_state((struct FrameObject *)object,7);
   object->timer=frame_random_range(90,300);
   frame_scene_effect_replenish_9710((struct FrameObject *)object);
   clear_partner=1;
  } else frame_adjust_actor_needs(((struct FrameActorObject *)object->partner)->actor_state,13,1);
  break;
 case 31:
  if(--object->timer==-1 || cancel) {
   transition_object_set_state(object->partner,((struct FrameActorObject *)object->partner)->default_state);
   frame_set_variant_state(object->partner,2);
   frame_set_variant_state((struct FrameObject *)object,7);
   object->timer=frame_random_range(90,300);
   frame_scene_effect_replenish_9710((struct FrameObject *)object);
   clear_partner=1;
  } else frame_adjust_actor_needs(((struct FrameActorObject *)object->partner)->actor_state,14,1);
  break;
 }
 if(clear_partner==1)object->partner=0;
}
