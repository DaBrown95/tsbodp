#include "frame_map_animation.h"

struct FrameObject *frame_create_map_animation_simple(unsigned char group,unsigned char entry) {
 struct FrameMapAnimationSimplePayload *payload=(struct FrameMapAnimationSimplePayload *)resource_get_object_payload(group,entry);
 struct FrameMapAnimationObject *object=(struct FrameMapAnimationObject *)frame_allocate_scene_object();
 if(object) {
 frame_set_position((struct FrameObject *)object,payload->x<<16,payload->y<<16);
 object->id=payload->id;
 object->flags=0x20008;
 object->map=payload->map;
 object->first=payload->first;
 object->current=payload->first;
 object->width=payload->width;
 object->height=payload->height;
 object->span=payload->width*payload->height;
 object->span=object->span*payload->frames;
 object->last=object->first+object->span;
 object->timer=payload->period;
 object->period=payload->period;
 object->one_shot=payload->one_shot;
 object->reverse=payload->repeat;
 object->on_step=frame_map_animation_simple_tick;
 transition_object_set_state((struct TransitionObject *)object,0);
 }
 return (struct FrameObject *)object;
}
asm(".align 2, 0");
