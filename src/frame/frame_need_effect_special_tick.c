#include "frame_need_effect_special.h"

void frame_need_effect_special_tick(struct FrameObject *base)
{
    struct FrameNeedEffectSpecialWork *effect = (struct FrameNeedEffectSpecialWork *)base;
    struct FrameNeedEffectPlayerSlot *players = (struct FrameNeedEffectPlayerSlot *)&g_input_config;
    struct FrameObject *actor = players[g_input_config.local_player].object;

    if (effect->state == 4) {
        switch (effect->variant_state) {
        case 0: {
            struct FramePoint view_offset;
            transition_object_set_state(actor, 0);
            frame_request_animation((struct FrameCommandObject *)actor, 1);
            frame_commit_need_effect((struct FrameObject *)effect, 1);
            effect->countdown = 30;
            frame_set_variant_state((struct FrameObject *)effect, 2);
            view_offset.x = 40;
            view_offset.y = 80;
            transition_configure_view((struct TransitionViewObject *)(struct FrameObject *)effect, view_offset, 0);
            break;
        }
        case 2:
            if (--effect->countdown == 0xffff) {
                frame_set_actor_direction(actor, 4);
                frame_request_animation((struct FrameCommandObject *)actor, 65);
                frame_set_variant_state((struct FrameObject *)effect, 3);
            }
            break;
        case 3:
            if (frame_object_has_flags(actor, 0x400000)) {
                frame_request_animation((struct FrameCommandObject *)actor, 15);
                frame_set_variant_state((struct FrameObject *)effect, 4);
            }
            break;
        case 4:
            if (frame_object_has_flags(actor, 0x400000)) {
                frame_disable_object_flags(actor, 17);
                frame_commit_need_effect((struct FrameObject *)effect, 2);
                frame_set_variant_state((struct FrameObject *)effect, 5);
            }
            break;
        case 5:
            if (frame_object_has_flags((struct FrameObject *)effect, 0x400000)) {
                struct FrameObject *companion;
                struct FramePoint point;
                frame_enable_object_flags((struct FrameObject *)effect, 8);
                frame_read_attachment((struct FrameObject *)effect, 1, &point);
                point.x = (point.x << 16) + effect->position.x;
                point.y = (point.y << 16) + effect->position.y;
                companion = frame_create_need_effect_companion(point);
                effect->companion = companion;
                effect->velocity.y = -0x80000;
                companion->velocity.y = -0x80000;
                frame_set_variant_state((struct FrameObject *)effect, 7);
            }
            break;
        case 7:
            if (frame_object_has_flags(effect->companion, 0x400000)) {
                frame_set_animation_record(effect->companion,
                                           &g_need_effect_special_animation_second);
                effect->velocity.y = -0x50000;
                effect->companion->velocity.y = -0x50000;
                effect->countdown = 30;
                frame_set_variant_state((struct FrameObject *)effect, 11);
            }
            break;
        case 11:
            if (--effect->countdown == 0xffff) {
                scene_submit_default_request(27);
                g_frame_flags |= 0x800;
            }
            break;
        }
    }
}
