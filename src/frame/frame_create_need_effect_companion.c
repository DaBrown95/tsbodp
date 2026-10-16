#include "frame_need_effect_special.h"

struct FrameObject *frame_create_need_effect_companion(struct FramePoint point)
{
    struct FrameActorObject *object = (struct FrameActorObject *)frame_allocate_object(24);
    frame_set_position((struct FrameObject *)object, point.x, point.y);
    object->flags = 0x19;
    object->oam.gfx_mode = 0;
    object->oam.double_tile_size = 0;
    object->oam.layer = 2;
    frame_acquire_palette_slot((struct FrameObject *)object, 7);
    frame_set_animation_record((struct FrameObject *)object,
                               &g_need_effect_special_animation_first);
    return (struct FrameObject *)object;
}
