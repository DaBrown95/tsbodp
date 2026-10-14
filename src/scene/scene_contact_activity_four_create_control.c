#include "scene_contact_activity_four_objects.h"

struct FrameObject *scene_contact_activity_four_create_control(void)
{
    struct FrameObject *object = frame_allocate_scene_object();

    object->id = 1;
    {
        struct SceneContactActivityFourEventFlags *view =
            (struct SceneContactActivityFourEventFlags *)object;
        view->contact_mode = 0;
        view->double_size = 0;
        view->layer = 2;
        view->palette = 1;
    }
    object->flags = 0x100001;
    frame_set_position(object, 88 << 16, 140 << 16);
    frame_set_animation_record(object,
        &g_scene_contact_activity_four_control_animation);
    object->on_step = scene_contact_activity_four_step_control_object;
    ((struct SceneContactCursor *)object)->state = 1;
    return object;
}

asm(".align 2,0");
