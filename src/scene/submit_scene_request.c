#include "scene_request_queue.h"
void resource_submit_scene(unsigned int kind,unsigned int mode,unsigned int argument)
{
 g_scene_queued_request.unknown_00=kind|0x80;
 g_scene_queued_request.mode=mode;
 g_scene_queued_request.scene=argument;
 g_scene_queued_request.parameter=0;
 g_scene_queued_request.unknown_10=0;
 g_scene_queued_request.unknown_14=0;
}
