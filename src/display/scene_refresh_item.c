#include "display_scene_lifecycle.h"
void display_scene_refresh_item(struct FrameObject *object)
{
    frame_set_animation_record(object, &g_frame_scene_resources[object->unknown_0a]);
}
