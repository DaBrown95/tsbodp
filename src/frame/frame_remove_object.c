#include "frame.h"
void frame_remove_object(struct FrameObject *object)
{
    if (object->id != 0xffff) {
        if (object->on_remove)
            object->on_remove(object);
        frame_release_object_palette(object);
        if ((int)object->flags < 0)
            resource_set_object(0, object->owner_id, object->owner_slot);
        object->id |= 0xffff;
        if (object->display_mode == 1 || object->display_mode == 3)
            frame_destroy_affine(object);
        if (g_frame_release_immediately == 1)
            frame_release_display(object);
        if (g_frame_primary_list.last == object)
            g_frame_primary_list.last = object->previous;
        frame_recycle_object(&g_frame_queue.free_list, &g_frame_primary_list, object);
    }
}
