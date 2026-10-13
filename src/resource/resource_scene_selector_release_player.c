#include "resource_scene_selector.h"
void resource_scene_selector_release_player(struct FrameObject *object)
{
    frame_disable_object_flags(object, 1);
}
