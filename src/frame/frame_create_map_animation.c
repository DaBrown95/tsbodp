#include "frame_map_animation.h"

struct FrameObject *frame_create_map_animation(unsigned char group,unsigned char entry) {
 struct FrameMapAnimationPayload *payload=(struct FrameMapAnimationPayload *)resource_get_object_payload(group,entry);
 struct FrameMapAnimationObject *object=(struct FrameMapAnimationObject *)frame_allocate_object(payload->id);
 unsigned char kind;
 frame_set_position((struct FrameObject *)object,payload->x<<16,payload->y<<16);
 object->flags=0x20008;
 object->kind=payload->kind;
 kind=payload->kind;
 object->map=payload->map;
 object->period=payload->period;
 object->timer=payload->period;
 object->one_shot=payload->one_shot;
 object->polarity=payload->polarity;
 if(object->polarity==0)object->enabled=0;else object->enabled=1;
 object->first=payload->first;
 object->width=g_frame_map_animation_definitions[kind].width;
 object->height=g_frame_map_animation_definitions[kind].height;
 object->span=payload->frames*g_frame_map_animation_definitions[kind].step;
 object->step=g_frame_map_animation_definitions[kind].step;
 object->last=object->first+object->span;
 object->reverse=payload->reverse;
 object->sound=payload->sound;
 if(object->reverse==0)object->current=object->last-object->step;
 else object->current=object->first;
 transition_object_set_state((struct TransitionObject *)object,0);
 object->started=0;
 object->on_step=frame_map_animation_tick;
 return (struct FrameObject *)object;
}
asm(".align 2, 0");
