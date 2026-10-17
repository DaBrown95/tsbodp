#include "scene_startup.h"
#include "scene_request_queue.h"

void resource_select_scene_nine(void)
{
    g_resource_selected = 1;
    resource_submit_scene(1, 0, 9);
    g_scene_mode_bytes[0] = 4;
}
