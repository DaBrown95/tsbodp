#include "display_scene_lifecycle.h"
void display_release_object_list(struct FrameObjectList *list)
{
    struct FrameObject *object = list->first, *next;
    while (object) {
        next = object->next;
        frame_remove_object(object);
        object = next;
    }
    g_frame_release_immediately = 1;
    frame_schedule(&g_frame_primary_list, 1);
}
