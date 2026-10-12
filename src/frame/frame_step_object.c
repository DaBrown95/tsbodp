#include "frame.h"
void frame_step_object(struct FrameObject *object, FrameU8 update_display)
{
    FrameU32 flags;
    if (object->flags & 2) {
        if (object->flags & 0x10000000)
            frame_unregister_bounds(g_frame_registration, object->registered_bounds, 16);
        frame_remove_object(object);
        return;
    }
    frame_check_visibility(object);
    flags = object->flags;
    if (!(g_frame_flags & 0x4000) && (flags & 0x1008)) {
        if (object->before_step)
            object->before_step(object);
        if (object->on_step && !(object->flags & 0x02000000)) {
            object->on_step(object);
            flags = object->flags;
        }
        if (flags & 0x2000)
            return;
        if (!(flags & 0x02000000)) {
            frame_tick_animation(object);
            if (object->affine_handle)
                frame_update_affine(object);
            frame_integrate_velocity(object);
            frame_update_bounds(object);
            frame_collect_render_order(object);
        }
        if (g_frame_flags & 8) {
            if (update_display != 1)
                return;
            object->position = object->next_position;
            frame_advance_position(object);
        }
    }
    if (update_display == 1 && !(flags & 0x40000000))
        frame_release_display(object);
}
