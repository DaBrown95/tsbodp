#include "frame_scene_marker_resources.h"
#include "frame_scene_player.h"
#include "frame_actor_state.h"
#include "resource_object_payload.h"
void frame_scene_target_resource_step(struct FrameObject *object) {
 switch(((struct FrameActorObject *)object)->state) {
 case 0: break;
 case 1: frame_run_actor_state(object);break;
 }
}
