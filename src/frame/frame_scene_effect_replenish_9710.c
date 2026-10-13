#include "frame_scene_effect.h"
void frame_scene_effect_replenish_9710(struct FrameObject *base) {
 struct FrameSceneEffectWork *object=(struct FrameSceneEffectWork *)base;
 object->value+=0x14000000;
 if(object->value>0x64000000)object->value=0x64000000;
}
