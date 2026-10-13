#include "scene_request_queue.h"
void scene_run_end_callback(void)
{
 ScenePhaseCallback callback=g_scene_phase_callbacks[g_scene_request.unknown_00].end;
 if(callback) {
  if((g_scene_queued_request.unknown_00&~0x80u)!=2)callback();
 }
}
