#include "frame_daily_flags.h"

void frame_step_daily_flag_object(struct FrameObject *base)
{
    struct FrameDailyFlagObject *object = (struct FrameDailyFlagObject *)base;
    switch (object->state) {
    case 0:
        break;
    case 1:
        frame_run_actor_state((struct FrameObject *)object);
        break;
    case 18:
        switch (object->variant_state) {
        case 0:
            frame_stop_motion(object->owner);
            transition_object_set_state(object->owner, 0);
            {
                unsigned char direction = frame_direction_toward(
                    object->owner, (struct FrameObject *)object);
                frame_set_actor_direction(object->owner, direction);
            }
            frame_request_animation((struct FrameCommandObject *)object->owner, 32);
            frame_set_variant_state((struct FrameObject *)object, 14);
            object->timer = 8;
            break;
        case 14:
            if (--object->timer != -1)
                break;
            actor_entry_adjust_counter(g_scene_entry_data, object->subtype, 1);
            frame_disable_object_flags((struct FrameObject *)object, 1);
            audio_play_animation_cue(48);
            frame_set_variant_state((struct FrameObject *)object, 15);
            break;
        case 15:
            if (object->owner->flags & 0x400000) {
                unsigned int index = object->index;
                unsigned int *flags;
                if (index <= 31) {
                    register unsigned int base asm("r2") =
                        (unsigned int)&g_display_daily_world;
                    flags = (unsigned int *)(base + 0x71c);
                } else {
                    {
                        register unsigned int base asm("r2") =
                            (unsigned int)&g_display_daily_world;
                        flags = (unsigned int *)(base + 0x720);
                    }
                    index -= 32;
                }
                *flags &= ~(1u << index);
                transition_object_set_state((struct FrameObject *)object, 1);
                frame_enable_object_flags((struct FrameObject *)object, 2);
                transition_object_set_state(object->owner, 16);
                frame_request_animation((struct FrameCommandObject *)object->owner, 1);
            }
            break;
        }
        break;
    }
}
asm(".align 2, 0");
