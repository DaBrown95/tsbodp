#include "frame.h"

/* Build the next frame's object work and delayed VBlank display queue. */
int frame_schedule(struct FrameObjectList *list, FrameU8 update_display)
{
    struct FrameObject *object, *next;
    FrameU32 i, layer;
    void (*dispatch_primary)(void *, void *) = (void (*)(void *, void *))0x03002a20;
    void (*dispatch_sort)(void) = (void (*)(void))0x03002900;
    int changed = 0;
    g_frame_count = 0;
    g_frame_queue.count = 0;
    g_frame_dispatch_arg = 0;
    layer = 0;
    if ((g_frame_flags & 0x10008) == 8) {
        for (object = list->first; object; object = next) {
            next = object->next;
            frame_step_object(object, update_display);
        }
    } else {
        for (object = list->last; object; object = next) {
            next = object->previous;
            frame_step_object(object, update_display);
        }
        if (!(g_frame_flags & 0x4000) && g_frame_dispatch_arg
                && list == &g_frame_primary_list)
            dispatch_primary(
                g_frame_dispatch_arg, g_frame_dispatch_scratch);
        for (object = list->first; object; object = object->next) {
            if (object->animation_source)
                frame_prepare_animation(object);
            object->position = object->next_position;
            frame_advance_position(object);
        }
    }
    for (object = list->first; object; object = next) {
        next = object->next;
        if ((object->flags & 0x1003) == 0x1001)
            frame_finalize_object(object);
    }
    if (update_display == 1 && g_frame_count > 1)
        dispatch_sort();
    frame_collect_objects();
    for (i = 0; i < g_frame_count; i++) {
        object = g_frame_objects[i];
        if (!(object->flags & 0x100))
            frame_apply_update(object, update_display);
        if (update_display == 1) {
            FrameU8 result = frame_render_object(object);
            if (object->display_layer != layer)
                for (; layer < object->display_layer; layer++)
                    frame_finish_layer(layer);
            if (object->sharing_flags & 0x10) {
                object->render_special = 1;
                frame_render_object(object);
                object->render_special = 0;
            }
            if (result) {
                changed = 1;
                if (result == 2)
                    g_frame_queue.objects[g_frame_queue.count++] = object;
            }
        }
    }
    if (g_frame_queue.deferred_refresh)
        for (i = 0; i < g_frame_count; i++) {
            object = g_frame_objects[i];
            if ((object->flags & 0x04000000) && update_display == 1) {
                object->sharing_flags |= 0x80;
                frame_render_object(object);
                object->sharing_flags &= 0x7f;
            }
        }
    if (update_display == 1) {
        for (; layer < 4; layer++)
            frame_finish_layer(layer);
        if (update_display == 1)
            frame_finish_display();
    }
    return changed;
}
