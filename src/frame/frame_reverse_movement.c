#include "frame_movement.h"

/* Original incoming calls and historical interface remain unestablished. */
void frame_reverse_movement(struct FrameObject *object)
{
    ((struct FrameMovementDirection *)object)->direction =
        g_frame_movement_reverse_directions[
            ((struct FrameMovementDirection *)object)->direction];
    ((struct FrameMovementPending *)object)->pending |= 16;
    object->velocity.x = 0u - (unsigned int)object->velocity.x;
    object->velocity.y = 0u - (unsigned int)object->velocity.y;
    object->next_position.word.x = object->position.x;
    object->next_position.word.y = object->position.y;
}
