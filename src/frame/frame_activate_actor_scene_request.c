#include "frame.h"
#include "frame_actor_scene.h"
void frame_activate_actor_scene_request(void)
{
 g_actor_scene_request.active=1;
 if(g_actor_scene_request.object)
  g_actor_scene_request.object->flags=(g_actor_scene_request.object->flags|0x200000)&~1;
 display_scene_stage_08027dc0(2);
}
