#include "frame_speed_exit_resource.h"
#include "frame.h"
#include "frame_actor_scene.h"
#include "frame_actor_speed_control.h"
#include "resource_object_payload.h"
struct FrameObject *frame_create_speed_exit_resource(unsigned char group,unsigned char entry) {
 struct FrameActorSpeedGame *world=(struct FrameActorSpeedGame *)&g_resource_game_state;
 if(world->world==50 && world->exit_flag!=1) {
  const struct FrameSpeedExitResourcePayload *payload=(const struct FrameSpeedExitResourcePayload *)resource_get_object_payload(group,entry);
  return frame_create_speed_exit_actor(payload->direction,payload->x*65536,payload->y*65536);
 }
 return 0;
}
