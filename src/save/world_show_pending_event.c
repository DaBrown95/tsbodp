#include "save_world_pending_notices.h"
#include "save_world_initialization.h"
#include "frame_actor_scene.h"

void save_world_show_pending_event(void)
{
    if (g_save_world_init_state.prefix.unknown748 == 4)
        g_actor_scene_result_id.id = 307;
    else
        g_actor_scene_result_id.id = 306;
    g_actor_scene_request.object = frame_create_scene_object(193, 266, 15, 0);
    frame_activate_actor_scene_request();
}
