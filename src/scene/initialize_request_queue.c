#include "scene_request_queue.h"
void scene_initialize_request_queue(void)
{
 g_scene_request.unknown_00=0;
 g_scene_queued_request=g_scene_request;
 g_scene_previous_request=g_scene_request;
 scene_stage_08026908();
 if(g_save_stream_state.header.bytes[11]==0)scene_submit_default_request(12);
 else scene_submit_default_request(3);
}
