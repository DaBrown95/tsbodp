#include "frame.h"

/* Installed by irq_init as the VBlank callback. */
void frame_update(void)
{
    int i;
    if (g_irq_context->transfer_ready == 1) {
        for (i = 0; i < g_frame_queue.count; i++) {
            struct FrameObject *object = g_frame_queue.objects[i];
            if (object->flags & 2)
                frame_release_display(object);
            else if (object->flags & 0x80) {
                object->flags &= ~0x80;
                object->display_tile = object->display_index;
            }
        }
        g_frame_queue.count = 0;
        frame_flush_display();
    }
}
