#include "frame_trigger_objects.h"

struct FrameObject *frame_create_actor_trigger(unsigned char group, unsigned char entry)
{
 struct FrameTriggerPayload *payload=(struct FrameTriggerPayload *)resource_get_object_payload(group,entry);
 struct FrameTriggerObject *object=(struct FrameTriggerObject *)frame_allocate_scene_object();
 frame_set_position((struct FrameObject *)object,payload->x<<16,payload->y<<16);
 object->id=payload->id;
 object->flags=12;
 object->kind=payload->kind;
 object->duration=payload->duration*30;
 transition_object_set_state((struct TransitionObject *)object,0);
 object->on_interact=frame_actor_trigger_interact;
 object->left=-payload->width;
 object->top=-payload->height;
 object->right=payload->width;
 object->bottom=payload->height;
 object->bound_kind=1;
 object->bound_count=1;
 object->on_step=frame_actor_trigger_step;
 return (struct FrameObject *)object;
}
asm(".align 2, 0");
