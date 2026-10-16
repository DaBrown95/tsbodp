#include "frame_actor_24420.h"

void frame_actor_contact_24a08(struct CollisionObject *first,
                              struct CollisionObject *second)
{
    struct FrameObject *object = (struct FrameObject *)first;
    struct FrameObject *other = (struct FrameObject *)second;
    if (other->id == 0) {
        frame_disable_object_flags(object, 5);
        frame_enable_object_flags(object, 2);
        frame_set_variant_state(other, 8);
        audio_play_animation_cue(181);
    }
}
asm(".align 2,0");
