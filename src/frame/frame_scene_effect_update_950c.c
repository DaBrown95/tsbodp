#include "frame_scene_effect.h"
void frame_scene_effect_update_950c(struct FrameObject *base) {
 struct FrameActorObject *object=(struct FrameActorObject *)base;
 if(object->pending_updates&2) {
  switch(object->variant_state) {
  case 7:case 24:case 26:case 27:case 29:
   frame_stop_motion((struct FrameObject *)object);
   frame_scene_effect_configure((struct FrameObject *)object,1);
   break;
  case 30:
   frame_stop_motion((struct FrameObject *)object);
   frame_scene_effect_configure((struct FrameObject *)object,1);
   if((unsigned char)(object->actor_id-2)<=1)audio_play_animation_cue(160);
   else if((unsigned char)object->actor_id<=1)audio_play_animation_cue(157);
   break;
  case 52:
   frame_stop_motion((struct FrameObject *)object);
   frame_scene_effect_configure((struct FrameObject *)object,4);
   audio_play_animation_cue(35);
   break;
  case 25:{
   unsigned char chance=frame_random_chance(10);
   unsigned char *kind=&object->actor_id;
   if(chance==1) {
    if((unsigned char)(*kind-2)<=1)audio_play_animation_cue(159);
    else if((unsigned char)*kind<=1)audio_play_animation_cue(156);
   }
   frame_scene_effect_configure((struct FrameObject *)object,0);
   object->speed=g_frame_scene_effect_speeds[*kind];
   break;
  }
  case 28:
   frame_scene_effect_configure((struct FrameObject *)object,0);
   object->speed=g_frame_scene_effect_speeds[object->actor_id];
   break;
  case 31:
   frame_scene_effect_configure((struct FrameObject *)object,3);
   frame_stop_motion((struct FrameObject *)object);
   if((unsigned char)(object->actor_id-2)<=1)audio_play_animation_cue(160);
   else if((unsigned char)object->actor_id<=1)audio_play_animation_cue(156);
   break;
  default:
   frame_stop_motion((struct FrameObject *)object);
   frame_scene_effect_configure((struct FrameObject *)object,1);
   break;
  }
  object->pending_updates&=~2;
 }
}
