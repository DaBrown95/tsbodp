#include "resource_timed_actor.h"

struct FrameObject *resource_create_timed_actor(unsigned char group, unsigned char slot)
{
    struct ResourceTimedActorPayload *payload =
        (struct ResourceTimedActorPayload *)resource_get_object_payload(group, slot);
    struct FrameObject *base = frame_allocate_object(payload->id);
    struct ResourceTimedActor *object = (struct ResourceTimedActor *)base;

    if (object) {
        frame_set_position(base, (unsigned int)payload->x << 16, (unsigned int)payload->y << 16);
        object->kind = payload->kind;
        object->direction = payload->direction;
        frame_set_animation_record(base, g_resource_timed_animations[object->kind].idle +
            g_frame_actor_direction_variants[object->direction]);
        object->variant_state = 7;
        object->state = 0;
        object->on_step = resource_timed_actor_tick;
        object->on_interact = resource_timed_actor_interact;
        object->unknown_ae = 120;
        object->oam.gfx_mode = 0;
        object->oam.double_tile_size = 0;
        object->oam.layer = 1;
        resource_timed_actor_choose_destination(base, frame_random_range(0, 7));
        object->speed = 0x20000;
        switch (object->kind) {
        case 0:
            object->work = g_resource_timed_initial_work;
            object->speed = 0x20000;
            frame_enable_object_flags(base, 0x80000011);
            frame_acquire_palette_slot(base, 6);
            if (!(unsigned char)display_time_in_range(&g_resource_timed_start,
                    &g_resource_timed_end, &g_display_world_clock, 6))
                frame_disable_object_flags(base, 1);
            break;
        case 1:
            frame_enable_object_flags(base, 0x80050651);
            frame_acquire_palette_slot(base, 2);
            object->mode84 = 2;
            transition_object_set_state(base, 9);
            frame_set_variant_state(base, 7);
            object->timer = 90;
            object->timer6c = 60;
            object->timer6e = 90;
            object->timer6a = 50;
            object->timer68 = 90;
            object->on_interact = 0;
            break;
        }
        frame_update_actor_state(base);
    }
    return base;
}
asm(".align 2,0");
