#include "resource_groups.h"
#include "transition_object.h"
#include "resource_transition.h"

void resource_transition_delay_tick(struct FrameObject *base)
{
    struct TransitionObject *object = (struct TransitionObject *)base;
    switch (object->state) {
    case 0:
        if (--object->countdown == -1)
            transition_object_set_state(object, 1);
        break;
    case 1:
        resource_activate_groups(object->layer_a, object->layer_b);
        object->flags |= 2;
        break;
    }
    object->pending = 0;
}

asm(".align 2, 0");
