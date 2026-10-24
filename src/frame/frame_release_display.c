#include "frame.h"

/* Defer tile allocation release until the VBlank queue is processed. */
void frame_release_display(struct FrameObject *object)
{
    int i;
    if (object->flags & 0x100)
        return;
    if ((object->sharing_flags & 3) != 0) {
        int slot;
        int group;
        if (object->display_index == 0xffff)
            return;
        group = object->shared_group;
        if (object->sharing_flags & 1)
            slot = 0;
        else
            slot = object->display_payload.shared.shared_slot;
        if (--g_frame_shared_display[group].counts[slot] == 0) {
            g_frame_shared_display[group].indices[slot] = 0xffff;
            frame_free_display_range(object->display_index,
                object->display_bytes, object->double_tile_size);
        }
        object->display_index = 0xffff;
        object->display_bytes = 0;
    } else {
        if (object->display_index != 0xffff) {
            frame_free_display_range(object->display_index,
                object->display_bytes, object->double_tile_size);
            object->display_index |= 0xffff;
            object->display_bytes = 0;
        }
        if (object->sharing_flags & 0x40) {
            for (i = 0; i < 4; i++) {
                struct FrameDisplayPart *part = &object->parts[i];
                if (part->index != 0xffff) {
                    frame_free_display_range(part->index, part->bytes,
                        object->double_tile_size);
                    part->index |= 0xffff;
                    part->bytes = 0;
                }
            }
        }
    }
}
