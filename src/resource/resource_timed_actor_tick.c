#include "resource_timed_actor.h"

void resource_timed_actor_tick(struct FrameObject *base)
{
    struct ResourceTimedActor *object = (struct ResourceTimedActor *)base;
    unsigned int direction;
    unsigned char *pending;
    unsigned int initial_pending;

    if (object->kind) {
        frame_run_actor_state((struct FrameObject *)object);
    } else {
        switch (object->state) {
        case 0:
            if ((unsigned char)display_time_in_range(&g_resource_timed_start,
                &g_resource_timed_end, &g_display_world_clock, 6))
                resource_timed_actor_patrol((struct FrameObject *)object);
            else
                frame_disable_object_flags((struct FrameObject *)object, 1);
            break;
        case 1: {
            struct ResourceTimedActorPayload *payload;
            object->flags |= 2;
            payload = (struct ResourceTimedActorPayload *)resource_get_object_payload(
                object->owner_group, object->owner_slot);
            resource_activate_groups(payload->group, payload->slot);
            return;
        }
        }
    }
    direction = object->direction;
    initial_pending = object->pending_updates & 8;
    pending = &object->pending_updates;
    if (initial_pending)
        frame_make_velocity(&object->velocity, object->flags, direction, object->speed);
    if (*pending & 4)
        frame_set_animation_record((struct FrameObject *)object, g_resource_timed_animations[object->kind].idle +
            g_frame_actor_direction_variants[direction]);
    if (*pending & 0x12) {
        if (object->variant_state == 9 || object->variant_state == 3) {
            frame_set_animation_record((struct FrameObject *)object, g_resource_timed_animations[object->kind].moving +
                g_frame_actor_direction_variants[direction]);
            frame_refresh_velocity((struct FrameObject *)object);
        } else {
            frame_set_animation_record((struct FrameObject *)object, g_resource_timed_animations[object->kind].idle +
                g_frame_actor_direction_variants[direction]);
            frame_stop_motion((struct FrameObject *)object);
        }
        if (direction > 4)
            object->oam.flip_x = 1;
        else
            object->oam.flip_x = 0;
    }
    *pending = 0;
}
asm(".align 2,0");
