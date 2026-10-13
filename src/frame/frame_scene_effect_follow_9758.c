#include "frame_scene_effect.h"
void frame_scene_effect_follow_9758(struct FrameObject *base) {
 struct FrameSceneEffectWork *object=(struct FrameSceneEffectWork *)base;
 struct FramePoint target=object->owner->position;
 if((view_point_distance(object->position,target)>>16)<=29) {
  frame_stop_motion((struct FrameObject *)object);
  frame_scene_effect_configure((struct FrameObject *)object,1);
  frame_cancel_actor_route((struct FrameObject *)object);
 } else {
  switch(object->route_status) {
  case 0:case 1:
   frame_cancel_actor_route((struct FrameObject *)object);
   frame_begin_actor_route((struct FrameObject *)object,&target,&object->route_status,3,0);
  case 2:
   frame_scene_effect_configure((struct FrameObject *)object,0);
   break;
  case 3:
   frame_cancel_actor_route((struct FrameObject *)object);
   frame_set_variant_state((struct FrameObject *)object,29);
   object->timer=90;
   break;
  }
 }
}
