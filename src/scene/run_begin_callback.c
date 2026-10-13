#include "scene_request_queue.h"
void scene_run_begin_callback(void)
{
 const struct ScenePhaseCallbacks *table=g_scene_phase_callbacks;
 unsigned int kind=g_scene_request.unknown_00;
 ScenePhaseCallback callback=table[kind].begin;
 if(callback) {
  if(g_scene_previous_request.unknown_00==2 && kind==1)return;
  callback();
 }
}
