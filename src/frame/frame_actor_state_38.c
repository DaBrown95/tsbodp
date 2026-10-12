#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "frame_actor_scene.h"
void frame_actor_state_38(void)
{
 if(g_resource_scene_arg==2 && g_actor_scene_request_active) {
  g_scene_mode_bytes[0]=0;
  ((struct FrameActorSceneState*)&g_resource_game_state)->timer=360;
  resource_submit_scene(1,0,37);
 } else {
  if(!((struct FrameActorSceneState*)&g_resource_game_state)->variant)
   g_actor_scene_result_id.id=304;
  else g_actor_scene_result_id.id=305;
  g_actor_scene_request.object=frame_create_scene_object(193,244,15,0);
  g_actor_scene_request_active=1;
  frame_activate_actor_scene_request();
 }
}
