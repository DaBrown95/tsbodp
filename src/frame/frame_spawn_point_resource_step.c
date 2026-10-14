#include "frame_scene_marker_resources.h"
#include "frame_scene_player.h"
#include "frame_actor_state.h"
void frame_spawn_point_resource_step(struct FrameObject *object) {
 switch(((struct FrameActorObject *)object)->state) {
 case 0: break;
 case 1: frame_run_actor_state(object);break;
 }
}
