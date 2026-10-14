#include "scene_contact_activity_four_event.h"

struct FrameObject *scene_contact_activity_four_create_event(void)
{
    struct FrameObject *object = frame_allocate_scene_object();
    int selected;

    object->id = 4;
    selected = frame_random_range(1, 100);
    if (selected <
        g_scene_contact_activity_four_rows[g_scene_contact_state->option].chance)
        object->unknown_0a = 0;
    else
        object->unknown_0a = frame_random_range(1,
            g_scene_contact_activity_four_rows[g_scene_contact_state->option].count);
    switch (object->unknown_0a) {
    case 0:
        object->unknown_4c[0] = frame_random_range(0, 1);
        break;
    case 1:
    case 2:
        object->unknown_4c[0] = frame_random_range(2, 3);
        break;
    case 3:
    case 4:
        object->unknown_4c[0] = frame_random_range(4, 5);
        break;
    case 5:
    case 6:
        object->unknown_4c[0] = frame_random_range(6, 7);
        break;
    }
    {
        struct SceneContactActivityFourEventFlags *view =
            (struct SceneContactActivityFourEventFlags *)object;

        view->contact_mode = 0;
        view->double_size = 0;
        view->layer = 2;
        view->palette = 15 - object->unknown_0a;
    }
    object->flags = 17;
    frame_set_position(object,
        (int)((unsigned int)g_scene_contact_activity_four_event_positions[
            object->unknown_4c[0]].x << 16),
        (int)((unsigned int)g_scene_contact_activity_four_event_positions[
            object->unknown_4c[0]].y << 16));
    ((struct SceneContactActivityFourEventObject *)object)->speed =
        g_scene_contact_activity_four_event_positions[object->unknown_4c[0]].speed;
    if (object->unknown_4c[0] & 1)
        object->unknown_12[0] = 2;
    else
        object->unknown_12[0] = 6;
    object->velocity.x = frame_fixed_multiply(
        g_frame_velocity_default[object->unknown_12[0] * 2],
        ((struct SceneContactActivityFourEventObject *)object)->speed);
    object->velocity.y = frame_fixed_multiply(
        (g_frame_velocity_default + 1)[object->unknown_12[0] * 2],
        ((struct SceneContactActivityFourEventObject *)object)->speed);
    frame_set_animation_record(object,
        (struct FrameVariantResource *)&g_scene_contact_activity_four_items[
            object->unknown_0a]);
    object->on_step = scene_contact_activity_four_step_event;
    return object;
}

asm(".align 2,0");
