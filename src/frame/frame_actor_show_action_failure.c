#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_choices.h"
void frame_actor_show_action_failure(struct FrameObject *object)
{
 switch(((struct FrameActorObject *)object)->subtype) {
 case 0:
  g_actor_scene_result_id.id=502;
  g_actor_scene_request.object=frame_create_scene_object(193,263,15,0);
  break;
 case 2:
  g_actor_scene_result_id.id=503;
  g_actor_scene_request.object=frame_create_scene_object(193,264,15,0);
  break;
 case 3:
  g_actor_scene_result_id.id=501;
  g_actor_scene_request.object=frame_create_scene_object(193,265,15,0);
  break;
 case 4:g_actor_scene_result_id.id=501;break;
 default:g_actor_scene_result_id.id=500;break;
 }
 frame_activate_actor_scene_request();
}
