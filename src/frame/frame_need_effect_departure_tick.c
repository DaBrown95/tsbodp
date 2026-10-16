#include "frame_need_effect_departure.h"

void frame_need_effect_departure_tick(struct FrameObject *base)
{
    struct FrameNeedEffectDepartureObject *object =
        (struct FrameNeedEffectDepartureObject *)base;
    switch (object->state) {
    case 0:
        if (--object->countdown == -1) {
            object->acceleration.y = 0x4000;
            object->state = 1;
            audio_game_stop_sample(g_need_effect_departure_cue);
        }
        break;
    case 1:
        if (object->velocity.y >= 0) {
            frame_stop_motion((struct FrameObject *)object);
            frame_set_animation_record((struct FrameObject *)object,
                                       &g_need_effect_departure_animation_second);
            object->state = 2;
            if (((struct FrameNeedEffectDepartureGame *)&g_resource_game_state)->appearance == 1)
                audio_play_animation_cue(130);
            else
                audio_play_animation_cue(131);
        }
        break;
    case 2:
        if (frame_object_has_flags((struct FrameObject *)object, 0x400000)) {
            object->acceleration.y = 0x4000;
            frame_set_animation_record((struct FrameObject *)object,
                                       &g_need_effect_departure_animation_third);
            object->state = 3;
        }
        break;
    case 3:
        if (object->velocity.y > 0x3ffff) {
            object->acceleration.y = 0;
            object->state = 4;
            if (((struct FrameNeedEffectDepartureGame *)&g_resource_game_state)->appearance == 1)
                audio_play_animation_cue(140);
            else
                audio_play_animation_cue(141);
        }
        break;
    case 4:
        if (object->position.y > 0x7fffff)
            g_scene_request.scene = 1;
        break;
    }
}
