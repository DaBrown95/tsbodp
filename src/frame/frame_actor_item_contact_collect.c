#include "frame_actor_items.h"

#define STATE ((struct FrameActorItemState *)g_scene_contact_state)

void frame_actor_item_contact_collect(struct CollisionObject *first,
                                     struct CollisionObject *second)
{
    struct FrameObject *object = (struct FrameObject *)first;
    struct FrameObject *other = (struct FrameObject *)second;

    if (other->id == 0) {
        frame_disable_object_flags(object, 5);
        frame_enable_object_flags(object, 2);
        if (STATE->created_count < 100)
            frame_create_actor_item(2, 0);
        STATE->collected_count++;
        scene_contact_add_activity_score(g_frame_actor_item_options[STATE->option].reward);
        if (STATE->collected_count == 100) {
            STATE->flags |= 1;
            scene_contact_add_activity_score(g_display_countdown.minute *
                g_frame_actor_item_options[STATE->option].reward);
        }
        audio_play_animation_cue(182);
        frame_emit_actor_item_contact(other, 1);
    }
}
asm(".align 2,0");
