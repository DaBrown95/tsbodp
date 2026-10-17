#include "frame.h"
void frame_integrate_velocity(struct FrameObject *object)
{
    object->velocity.x += object->acceleration.x;
    object->velocity.y += object->acceleration.y;
    object->next_position.word.x = object->position.x + object->velocity.x;
    object->next_position.word.y = object->position.y + object->velocity.y;
}
/* Own the zero alignment bytes following this pool-free function. */
asm(".align 2, 0");
