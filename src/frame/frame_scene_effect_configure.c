#include "frame_scene_player.h"
void frame_scene_effect_configure(struct FrameObject *base,unsigned char animation) {
 struct FrameActorObject *object=(struct FrameActorObject *)base;
 if(animation!=object->requested_animation) {
  object->requested_animation=animation;
  object->pending_updates|=4;
 }
}
