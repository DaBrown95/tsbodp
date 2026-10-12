#include "transition_object.h"

void transition_object_set_state(struct TransitionObject *object, unsigned char state) {
 if (object->state != state) {
  object->state = state;
  object->pending |= 1;
 }
}

/* Original zero-filled alignment, separate from the C instruction body. */
asm(".align 2, 0");
