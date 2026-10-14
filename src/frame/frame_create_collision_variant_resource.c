#include "frame_collision_variant_resource.h"
#include "display_need_effect_update.h"
#include "resource_object_payload.h"

struct FrameObject *frame_create_collision_variant_resource(unsigned char group,
        unsigned char entry)
{
    struct FrameCollisionVariantPayload *payload =
        (void *)resource_get_object_payload(group, entry);
    struct FrameCollisionVariantView *object =
        (void *)frame_allocate_object(payload->selector_word);

    frame_set_position((struct FrameObject *)object,
        payload->x * 65536, payload->y * 65536);
    object->flags = 0x60015;
    object->subtype = payload->kind;
    object->kind = payload->kind;
    object->contact_mode = 0;
    object->double_size = 0;
    frame_update_actor_state((struct FrameObject *)object);
    object->on_step = frame_collision_variant_resource_step;
    object->on_contact = frame_need_effect_interact;
    object->mode_ae = 24;
    transition_object_set_state(object, 0);
    frame_set_subtype_object_palette((struct FrameObject *)object,
        g_frame_collision_variant_palettes);
    object->sharing_flags |= 2;

    switch (object->kind) {
    case 0: object->sharing_flags &= 0xfd; break;
    case 1: object->shared_group = 0; break;
    case 2: object->shared_group = 1; break;
    case 3: object->shared_group = 2; break;
    case 4: object->shared_group = 3; break;
    }
    frame_set_animation_record((struct FrameObject *)object,
        &g_frame_collision_variant_animations[object->kind]);
    return (struct FrameObject *)object;
}

/* Original zero-filled alignment, separate from the C instruction body. */
asm(".align 2, 0");
