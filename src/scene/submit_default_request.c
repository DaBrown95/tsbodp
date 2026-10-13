#include "scene_request_queue.h"
void scene_submit_default_request(unsigned int kind)
{
 resource_submit_scene(kind,0,0);
}
