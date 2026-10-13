#include "scene_request_queue.h"
void scene_run_step_callback(void)
{
 ScenePhaseCallback callback=g_scene_phase_callbacks[g_scene_request.unknown_00].step;
 if(callback)callback();
}
