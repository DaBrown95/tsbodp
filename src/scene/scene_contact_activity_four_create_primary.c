#include "scene_contact_activity_four_objects.h"

struct FrameObject *scene_contact_activity_four_create_primary(void)
{
    struct FrameObject *object = frame_allocate_scene_object();

    object->id = 0;
    {
        struct SceneContactActivityFourEventFlags *view =
            (struct SceneContactActivityFourEventFlags *)object;
        view->contact_mode = 0;
        view->double_size = 0;
        view->layer = 2;
        view->palette = 0;
    }
    object->flags = 1;
    frame_set_position(object, 88 << 16, 152 << 16);
    frame_set_animation_record(object,
        &g_scene_contact_activity_four_primary_animation);
    object->on_step = scene_contact_original_step_four_primary;
    return object;
}

asm(".align 2,0");
