#include "scene_contact_activity_four.h"

struct FrameObject *scene_contact_activity_four_create_item(
    struct FramePoint position, unsigned int selected, unsigned int slot)
{
    struct FrameObject *object = frame_allocate_scene_object();
    unsigned int quadrant, direction;

    object->id = 3;
    object->unknown_12[0] = slot;
    object->unknown_0a = selected;
    {
        struct SceneContactActivityFourObjectFlags *view =
            (struct SceneContactActivityFourObjectFlags *)object;

        view->contact_mode = 0;
        view->double_size = 0;
        view->layer = 1;
        view->palette = 3;
    }
    object->flags = 1;
    frame_set_position(object, (int)((unsigned int)position.x << 16),
        (int)((unsigned int)position.y << 16));
    quadrant = slot & 3;
    if (quadrant == 0 || quadrant == 3)
        frame_set_animation_record(object,
            &g_scene_contact_activity_four_animation_a);
    else
        frame_set_animation_record(object,
            &g_scene_contact_activity_four_animation_b);
    frame_set_animation_frame((struct FrameTickObject *)object,
        ((unsigned char *)object)[10]);
    direction = slot >> 1;
    if (slot > 3)
        ((struct SceneContactActivityFourObjectFlags *)object)->flag4 = -1;
    else
        ((struct SceneContactActivityFourObjectFlags *)object)->flag4 = 0;
    {
        unsigned int range = 3;

        range &= direction;
        range -= 1;
        if (range <= 1)
            ((struct SceneContactActivityFourObjectFlags *)object)->flag5 = 1;
        else
            ((struct SceneContactActivityFourObjectFlags *)object)->flag5 = 0;
    }
    return object;
}

asm(".align 2,0");
