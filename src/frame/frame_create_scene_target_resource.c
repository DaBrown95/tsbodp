#include "frame_scene_marker_resources.h"
#include "frame_scene_player.h"
#include "frame_actor_state.h"
#include "resource_object_payload.h"
struct FrameObject *frame_create_scene_target_resource(unsigned char group,unsigned char entry) {
 struct FrameObject *object=frame_allocate_scene_object();
 struct FrameSceneTargetPayload *payload=(struct FrameSceneTargetPayload *)resource_get_object_payload(group,entry);
 frame_set_position(object,payload->x*65536,payload->y*65536);
 object->id=payload->selector_word;
 object->unknown_0a=0;
 object->flags=0x22000;
 transition_object_set_state(object,0);
 frame_set_variant_state(object,1);
 object->on_step=frame_scene_target_resource_step;
 return object;
}
