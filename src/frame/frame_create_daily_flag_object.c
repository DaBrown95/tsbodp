#include "frame_daily_flag_creation.h"

struct FrameObject *frame_create_daily_flag_object(unsigned char group, unsigned char slot)
{
    struct FrameDailyFlagSpawnObject *object =
        (struct FrameDailyFlagSpawnObject *)frame_allocate_scene_object();
    struct FrameDailyFlagPayload *payload =
        (struct FrameDailyFlagPayload *)resource_get_object_payload(group, slot);
    unsigned char active;

    object->id = payload->id;
    object->subtype = payload->subtype;
    object->index = payload->index;
    if (frame_test_daily_flag(object->index))
        active = !!frame_test_daily_pending_flag(object->index);
    else {
        if (frame_random_chance(g_frame_daily_flag_chances[object->subtype]) == 1) {
            frame_mark_daily_pending_flag(object->index);
            active = 1;
        } else
            active = 0;
        frame_mark_daily_flag(object->index);
    }
    if (active == 1) {
        frame_set_position((struct FrameObject *)object,
            (unsigned int)(unsigned int)payload->x << 16, (unsigned int)(unsigned int)payload->y << 16);
        object->flags = 0xe0415;
        object->on_step = frame_step_daily_flag_object;
        transition_object_set_state((struct FrameObject *)object, 0);
        object->variant_state = 1;
        object->owner = 0;
        frame_set_animation_record((struct FrameObject *)object,
            &g_frame_daily_flag_animations[object->subtype]);
        frame_acquire_palette_slot((struct FrameObject *)object,
            g_frame_daily_flag_palettes[object->subtype]);
        {
            unsigned char value = object->display_byte;
            value |= 12;
            object->display_byte = value;
        }
        object->on_interact = frame_daily_flag_interact;
    } else {
        frame_remove_object((struct FrameObject *)object);
        object = 0;
    }
    return (struct FrameObject *)object;
}
