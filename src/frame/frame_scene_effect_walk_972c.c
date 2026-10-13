#include "frame_scene_effect.h"
void frame_scene_effect_walk_972c(struct FrameObject *base) {
 struct FrameSceneEffectWork *object=(struct FrameSceneEffectWork *)base;
 if(((struct FrameActorSpeedProbe *)object)->blocked!=0)frame_actor_choose_walk_direction((struct FrameObject *)object);
 if(object->velocity.x==0)frame_refresh_velocity((struct FrameObject *)object);
 frame_actor_refresh_terrain(base);
}
