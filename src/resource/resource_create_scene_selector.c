#include "resource_scene_selector.h"

struct FrameObject *resource_create_scene_selector(unsigned char group, unsigned char slot)
{
    struct ResourceSceneSelectorPayload *payload =
        (void *)resource_get_object_payload(group, slot);
    struct ResourceSceneSelector *object;
    unsigned int special = 0;
    if (g_scene_id == 2 && payload->selector == 13 &&
            !(g_save_stream_state.header.words[6] & 2))
        return 0;
    object = (void *)frame_allocate_scene_object();
    frame_set_position((struct FrameObject *)object,
        (unsigned int)payload->x << 16, (unsigned int)payload->y << 16);
    object->id = payload->id;
    object->subtype = payload->subtype;
    object->flags = 0x000a0404;
    transition_object_set_state((struct FrameObject *)object, 0);
    object->selector = payload->selector;
    object->parameter = payload->parameter;
    object->on_interact = resource_scene_selector_interact;
    object->collision_y0 = -payload->half_height;
    object->collision_y1 = payload->half_height;
    object->collision_x0 = -payload->half_width;
    object->collision_x1 = payload->half_width;
    object->collision_kind = 1;
    object->collision_count = 1;
    object->on_step = resource_scene_selector_tick;
    object->variant_state = 1;
    if (object->subtype == 2) {
        frame_set_animation_record((struct FrameObject *)object, &g_resource_selector_animation2);
        object->flags |= 0x40000;
        frame_acquire_palette_slot((struct FrameObject *)object, 4);
        object->oam.layer = 3;
        frame_enable_object_flags((struct FrameObject *)object, 1);
    }
    if (object->subtype == 5) {
        frame_set_animation_record((struct FrameObject *)object, &g_resource_selector_animation5);
        frame_acquire_palette_slot((struct FrameObject *)object, 5);
        object->oam.layer = 2;
        frame_enable_object_flags((struct FrameObject *)object, 0x40001);
    }
    if (object->subtype == 3) {
        frame_set_animation_record((struct FrameObject *)object, &g_resource_selector_animation3);
        frame_acquire_palette_slot((struct FrameObject *)object, 5);
        object->oam.layer = 2;
        frame_enable_object_flags((struct FrameObject *)object, 0x40001);
    }
    if (object->subtype == 4) {
        frame_set_animation_record((struct FrameObject *)object, &g_resource_selector_animation4);
        frame_acquire_palette_slot((struct FrameObject *)object, 5);
        object->oam.layer = 2;
        frame_enable_object_flags((struct FrameObject *)object, 0x40001);
        special = 1;
    }
    {
        struct ResourceSceneSelector *active = (void *)g_frame_primary_list.first;
        unsigned char *first_hour = &object->first_hour;
        unsigned char *second_hour = &object->second_hour;
        while (active) {
            active->scan_flags &= 0xfe;
            active = (void *)active->next;
        }
        if (special)
            object->on_interact = resource_scene_selector_interact_alternate;
        *first_hour = 0;
        *second_hour = 0;
    }
    return (struct FrameObject *)object;
}
asm(".align 2, 0");
