#include "scene_contact_activity_three.h"

#define LINE (&g_scene_contact_activity_three_slots)

unsigned int scene_contact_activity_three_raster_line_slot(unsigned int index)
{
    struct FrameObject *object = LINE->objects[index];
    unsigned short *buffer;
    int x, y, remainder, i;
    unsigned int display_index = object->display_index;

    if (display_index != 65535) {
        buffer = (unsigned short *)(0x06010000u + (display_index << 5));
        {
            unsigned int fill = 0;
            display_cpu_copy(&fill, buffer, 0x05000020);
        }
        if (LINE->horizontal) {
            int distance = LINE->endpoint.x - (LINE->origin.x >> 16);
            int magnitude = distance, delta, start_y, end, step_x;

            if (magnitude < 0)
                magnitude = -magnitude;
            LINE->count = (magnitude >> 4) + 1;
            remainder = (distance + 1) & 15;
            delta = (unsigned int)LINE->step.y << 4;
            start_y = 8 * 65536 - (delta >> 1);
            if (start_y < 0)
                start_y = 0;
            end = (unsigned int)start_y + (unsigned int)delta;
            step_x = LINE->step.x;
            x = 15 * 65536;
            if (step_x > 0)
                x = 0;
            y = start_y;
            LINE->delta.y = (unsigned int)y - (unsigned int)end;
        } else {
            int distance = LINE->endpoint.y - (LINE->origin.y >> 16);
            int magnitude = distance, delta;

            if (magnitude < 0)
                magnitude = -magnitude;
            LINE->count = (magnitude >> 4) + 1;
            remainder = distance & 15;
            delta = (unsigned int)LINE->step.x << 4;
            x = 8 * 65536 - (delta >> 1);
            y = 0;
            LINE->delta.x = 0u - (unsigned int)delta;
        }
        for (i = 0; i < 16; ++i) {
            scene_contact_activity_three_plot_line_pixel(buffer, x >> 16, y >> 16);
            x = (unsigned int)x + (unsigned int)LINE->step.x;
            y = (unsigned int)y + (unsigned int)LINE->step.y;
        }
        if (LINE->origin.y == 0) {
            unsigned int shifted_position_x = (unsigned int)object->position.x + 4 * 65536u;
            object->position.x = shifted_position_x +
                (unsigned int)(remainder - 6) * (unsigned int)LINE->step.x;
            object->position.y = (unsigned int)object->position.y +
                (unsigned int)(remainder - 6) * (unsigned int)LINE->step.y;
        }
        ++LINE->count;
        object->next_position.word.x = object->position.x;
        object->next_position.word.y = object->position.y;
    }
    return 0;
}

__asm__(".align 2,0");
