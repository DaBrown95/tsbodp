#include "scene_request_queue.h"
unsigned int scene_queued_request_kind(void){return g_scene_queued_request.unknown_00&~0x80u;}
