#include "display_condition_marker.h"

struct FrameObject *condition_marker_create(unsigned char group, unsigned char slot)
{
    struct ConditionMarkerPayload *payload =
        (struct ConditionMarkerPayload *)resource_get_object_payload(group, slot);
    struct FrameObject *base = frame_allocate_object(payload->id);
    struct ConditionMarkerState *object = (struct ConditionMarkerState *)base;

    if (base) {
        frame_set_position(base, (unsigned int)payload->x << 16,
                           (unsigned int)payload->y << 16);
        object->variant = 7;
        object->state = 0;
        base->on_step = condition_marker_step;
        object->row = payload->row;
        object->column = payload->column;
        object->entry = payload->entry;
        object->completed = payload->completed;
        frame_enable_object_flags(base, 8);
    }
    return base;
}

asm(".align 2, 0");
