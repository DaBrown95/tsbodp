#include "frame_actor_items.h"

void frame_step_actor_item_visibility(struct FrameObject *object)
{
    if ((unsigned char)frame_check_visibility(object) == 0) {
        frame_enable_object_flags(object, 5);
        frame_disable_object_flags(object, 8);
        object->on_step = 0;
    }
    ((struct FrameActorObject *)object)->pending_updates = 0;
}
asm(".align 2,0");
