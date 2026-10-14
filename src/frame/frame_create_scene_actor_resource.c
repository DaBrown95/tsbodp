#include "frame_serialized_actor.h"
#include "frame_scene_player.h"
#include "resource_object_payload.h"

struct FrameObject *frame_create_scene_actor_resource(unsigned char group,unsigned char entry)
{
 struct FrameSerializedActorPayload *payload=(struct FrameSerializedActorPayload *)resource_get_object_payload(group,entry);
 struct FrameObject *object;
 if(frame_scene_actor_allowed(payload->actor,g_frame_world_id,(const struct DisplayTimeRecord *)g_scene_world_state)==1) {
  object=frame_create_actor(payload->actor,payload->direction,payload->x*65536,payload->y*65536);
  ((struct FrameActorObject *)object)->indicator=0;
 } else object=0;
 return object;
}
asm(".align 2, 0");
