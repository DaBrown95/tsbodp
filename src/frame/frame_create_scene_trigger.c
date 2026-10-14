#include "frame.h"
#include "resource_object_payload.h"
#include "transition_object.h"
#include "frame_scene_trigger.h"
struct FrameObject *frame_create_scene_trigger(unsigned char group,unsigned char entry) {
 unsigned int a=(unsigned char)group,b=(unsigned char)entry;
 struct FrameObject *base=frame_allocate_scene_object();
 const struct SceneTriggerPayload *payload=(const struct SceneTriggerPayload *)resource_get_object_payload(a,b);
 struct SceneTriggerView *object=(struct SceneTriggerView *)base;
 frame_set_position(base,payload->x*65536,payload->y*65536);
 base->id=payload->id;
 base->flags=0x20404;
 transition_object_set_state((struct TransitionObject *)base,0);
 object->selector=payload->selector;
 object->on_contact=frame_scene_trigger_contact;
 object->top=-payload->height;
 object->bottom=payload->height;
 object->left=-payload->width;
 object->right=payload->width;
 object->bound_kind=1;
 object->bound_count=1;
 object->on_step=frame_scene_trigger_noop;
 return base;
}
asm(".align 2,0");
