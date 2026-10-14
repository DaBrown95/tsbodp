#include "scene_contact_activity_two.h"
void scene_contact_activity_two_step_completed_event(struct FrameObject *object)
{
    if (object->flags & 0x400000) {
        object->flags |= 3;
        scene_contact_activity_two_reset_controls();
        scene_contact_activity_two_draw_row(frame_random_range(0, 6));
    }
}
asm(".align 2, 0");
