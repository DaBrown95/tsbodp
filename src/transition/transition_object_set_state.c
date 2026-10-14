#include "frame.h"
#include "transition_object.h"

void transition_object_set_state(void *base, unsigned char state)
{
    struct TransitionObject *object = (struct TransitionObject *)base;

    if (object->state != state) {
        object->state = state;
        object->pending |= 1;
    }
}

/* Original zero-filled alignment, separate from the C instruction body. */
asm(".align 2, 0");
