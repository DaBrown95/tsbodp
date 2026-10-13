#include "scene_request_queue.h"
unsigned char scene_request_changed(void)
{
 if(g_scene_request.unknown_00!=g_scene_queued_request.unknown_00)
  return 1;
 else return 0;
}
