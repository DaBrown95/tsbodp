#include "scene_contact_activity_zero.h"
#include "display_collision.h"
#define STATE ((struct FrameActorItemState *)g_scene_contact_state)

void scene_contact_activity_zero_initialize(void)
{
    unsigned char used[43];
    int count;
    struct FrameObject *object;

    display_show_background(3, g_activity_zero_background_control);
    display_fill_background(3, 0);
    display_load_background(3, &g_activity_zero_background, 43, 1, 0, 0);
    frame_define_palette_slot(g_actor_24420_palette_by_id[0], g_activity_zero_palettes);
    frame_define_palette_slot(g_actor_24420_palette_by_id[2], g_activity_zero_palettes + 2);
    frame_define_palette_slot(g_actor_24420_palette_by_id[3], g_activity_zero_palettes + 3);
    frame_define_palette_slot(g_actor_24420_palette_by_id[4], g_activity_zero_palettes + 4);
    frame_define_palette_slot(15, g_activity_zero_palette15);
    frame_define_palette_slot(14, g_activity_zero_palette14);
    frame_initialize_transient_definition(0, 1, &g_activity_zero_transient1);
    frame_initialize_transient_definition(0, 0, &g_activity_zero_transient0);
    STATE->flags |= 32;
    {
        struct FrameObject *primary = frame_create_actor_24420(g_activity_zero_start, 14);
        struct FrameScenePlayerSlot *slots = g_frame_scene_player_slots;
        STATE->primary = primary;
        slots[0].object = primary;
    }
    heap_clear(used, 0, 43);
    display_time_copy(&g_display_countdown, &g_frame_actor_item_options[STATE->option].clock);
    for (count = g_frame_actor_item_options[STATE->option].count2; count > 0; --count)
        frame_create_actor_item(2, used);
    for (count = g_frame_actor_item_options[STATE->option].count3; count > 0; --count)
        frame_create_actor_item(3, used);
    for (count = g_frame_actor_item_options[STATE->option].count4; count > 0; --count)
        frame_create_actor_item(4, used);
    for (count = g_frame_actor_item_options[STATE->option].count_other; count > 0; --count) {
        object = frame_create_option_object(1, 4, 8, 0, 0);
        frame_place_actor_item_on_land(object);
        frame_disable_object_flags(object, 0x10050040);
        frame_enable_object_flags(object, 8);
        ((struct CollisionObject *)object)->on_collision[1] = 0;
        ((struct CollisionObject *)object)->on_collision[0] = frame_actor_item_contact_relation;
        ((struct FrameOptionObject *)object)->speed = 0x30000;
        ((struct FrameOptionObject *)object)->time1 = 80;
        ((struct FrameOptionObject *)object)->time0 = 120;
    }
}
asm(".align 2,0");
