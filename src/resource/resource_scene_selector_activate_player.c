#include "resource_scene_selector.h"
void resource_scene_selector_activate_player(struct FrameObject *base, int x, int y, unsigned short layer)
{
    struct ResourceSceneSelector *object = (void *)base;
    frame_set_position((struct FrameObject *)object, (unsigned int)x << 16, (unsigned int)y << 16);
    frame_enable_object_flags((struct FrameObject *)object, 1);
    object->oam.layer = layer;
}
asm(".align 2, 0");
