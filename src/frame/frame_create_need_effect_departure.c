#include "frame_need_effect_departure.h"

struct FrameObject *frame_create_need_effect_departure(void)
{
    struct FrameNeedEffectDepartureObject *object =
        (struct FrameNeedEffectDepartureObject *)frame_allocate_object(0);
    frame_set_position((struct FrameObject *)object, 0x4c0000, 0x780000);
    object->flags = 0x19;
    object->oam.gfx_mode = 0;
    object->oam.double_tile_size = 0;
    object->oam.layer = 1;
    object->oam.palette = 0;
    object->on_step = frame_need_effect_departure_tick;
    object->state = 0;
    object->countdown = 12;
    object->velocity.y = -0x40000;
    frame_set_animation_record((struct FrameObject *)object,
                               &g_need_effect_departure_animation_first);
    object->before_step = resource_object_before_step;
    g_need_effect_departure_cue = audio_play_animation_cue(69);
    return (struct FrameObject *)object;
}
