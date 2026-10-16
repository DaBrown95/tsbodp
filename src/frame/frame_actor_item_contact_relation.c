#include "frame_actor_items.h"

void frame_actor_item_contact_relation(struct CollisionObject *first,
                                      struct CollisionObject *second)
{
    struct FrameObject *object = (struct FrameObject *)first;
    struct FrameObject *other = (struct FrameObject *)second;

    if (other->id == 0) {
        frame_disable_object_flags(object, 5);
        frame_enable_object_flags(object, 2);
        display_menu_adjust_relation(&g_display_menu_relation_state, 12, -4);
        audio_play_animation_cue(184);
        frame_emit_actor_item_contact(other, 0);
    }
}
asm(".align 2,0");
