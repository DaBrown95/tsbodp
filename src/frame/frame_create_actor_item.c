#include "frame_actor_items.h"

#define STATE ((struct FrameActorItemState *)g_scene_contact_state)

void frame_create_actor_item(unsigned int kind, unsigned char *used)
{
    struct FrameObject *object = frame_allocate_scene_object();

    if (kind == 4)
        frame_place_actor_item_in_water(object, used);
    else
        frame_place_actor_item_on_land(object);
    object->id = kind;
    ((struct FrameActorItemDisplay *)object)->contact_mode = 0;
    ((struct FrameActorItemDisplay *)object)->double_size = 0;
    ((struct FrameActorItemDisplay *)object)->layer = 3;
    if (g_frame_flags & 16)
        frame_enable_object_flags(object, 5);
    else {
        frame_enable_object_flags(object, 8);
        object->on_step = frame_step_actor_item_visibility;
    }
    frame_acquire_palette_slot(object, g_actor_24420_palette_by_id[kind]);
    object->sharing_flags |= 2;
    switch (kind) {
    case 2:
        object->shared_group = 4;
        frame_set_animation_record(object, &g_frame_actor_item_resource2);
        STATE->created_count++;
        ((struct FrameActor24420CollisionView *)object)->collision = frame_actor_item_contact_collect;
        break;
    case 3:
        object->shared_group = 5;
        frame_set_animation_record(object, &g_frame_actor_item_resource3);
        ((struct FrameActor24420CollisionView *)object)->collision = frame_actor_contact_24a08;
        break;
    case 4:
        object->shared_group = 6;
        frame_set_animation_record(object, &g_frame_actor_item_resource4);
        ((struct FrameActor24420CollisionView *)object)->collision = frame_actor_item_contact_penalty;
        break;
    }
    object->before_step = resource_object_before_step;
}
asm(".align 2,0");
