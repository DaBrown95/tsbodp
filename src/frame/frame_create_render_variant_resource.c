#include "frame_render_variant_resource.h"
#include "frame_indicator.h"
#include "frame_actor_state.h"
#include "scene_retention.h"
#include "resource_object_payload.h"

struct FrameObject *frame_create_render_variant_resource(unsigned char group,
        unsigned char entry)
{
    struct FrameRenderVariantPayload *payload =
        (struct FrameRenderVariantPayload *)resource_get_object_payload(group, entry);
    struct FrameObject *object = frame_allocate_object(payload->selector_word);

    if (object) {
        struct FrameRenderVariantFlags *flags = (struct FrameRenderVariantFlags *)object;
        frame_set_position(object, payload->x * 65536, payload->y * 65536);
        object->unknown_0a = payload->subtype;
        flags->contact_mode = 0;
        flags->double_size = 0;
        flags->layer = 1;

        switch (object->unknown_0a) {
        case 0:
            frame_enable_object_flags(object, 0x40001);
            frame_acquire_palette_slot(object, 2);
            break;
        case 1:
            frame_enable_object_flags(object, 0x40011);
            frame_set_object_palette(object, g_frame_render_variant_palette);
            break;
        }

        frame_set_animation_record(object,
            g_frame_render_variant_animations[object->unknown_0a]);
        frame_update_actor_state(object);
    }
    return object;
}
