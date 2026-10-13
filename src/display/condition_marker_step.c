#include "display_condition_marker.h"

void condition_marker_step(struct FrameObject *base)
{
    struct ConditionMarkerState *object = (struct ConditionMarkerState *)base;

    switch (object->state) {
    case 0:
        {
            unsigned int matched;
            if (object->completed) {
                if (object->entry == 255)
                    matched = condition_group_complete(object->row, object->column);
                else
                    matched = condition_is_complete(object->row, object->column,
                                                    object->entry);
            } else {
                if (object->entry == 255)
                    matched = condition_group_active(object->row, object->column);
                else
                    matched = condition_is_active(object->row, object->column,
                                                  object->entry);
            }
            if ((unsigned char)matched)
                transition_object_set_state(base, 1);
        }
        break;
    case 1:
        {
            struct ConditionMarkerPayload *payload;
            base->flags |= 2;
            payload = (struct ConditionMarkerPayload *)resource_get_object_payload(
                base->owner_id, base->owner_slot);
            resource_activate_groups(payload->group, payload->slot);
        }
        break;
    }
}

asm(".align 2, 0");
