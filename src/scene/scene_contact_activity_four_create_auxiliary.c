#include "scene_contact_activity_four_objects.h"

struct FrameObject *scene_contact_activity_four_create_auxiliary(void)
{
    struct FrameObject *object = frame_allocate_scene_object();

    object->id = 2;
    {
        struct SceneContactActivityFourEventFlags *view =
            (struct SceneContactActivityFourEventFlags *)object;
        view->contact_mode = 0;
        view->double_size = 0;
        view->layer = 0;
        view->palette = 2;
    }
    object->flags = 1;
    frame_set_position(object, 212 << 16, 30 << 16);
    frame_set_animation_record(object,
        &g_scene_contact_activity_four_auxiliary_animation);
    object->on_step = scene_contact_activity_four_step_auxiliary_object;
    return object;
}

asm(".align 2,0");
