#include "scene_choice_panel.h"

void scene_choice_panel_original_window_end(unsigned short duration)
{
    struct WindowState *source = &g_window_states[1];
    int left, top, right, bottom, center_x, center_y;
    unsigned int horizontal, vertical;

    right = source->axes[1].current[0].position;
    left = source->axes[0].current[0].position;
    center_x = (right - left) / 2 + left;
    bottom = source->axes[1].current[1].position;
    top = source->axes[0].current[1].position;
    center_y = (bottom - top) / 2 + top;
    {
        union DisplayWindowFixedPoint *position = &source[-1].axes[0].current[0];
        union DisplayWindowFixedPoint *last_position = &source[-1].axes[1].current[0];
        position[0].position = left;
        position[1].position = top;
        last_position[0].position = right;
        last_position[1].position = bottom;
        horizontal = ((unsigned int)position[0].halves.integer << 8) |
                     (unsigned int)(right >> 16);
        vertical = ((unsigned int)position[1].halves.integer << 8) |
                   (unsigned int)(bottom >> 16);
        DISPLAY_REG16(0x04000040) = horizontal;
        DISPLAY_REG16(0x04000044) = vertical;

    }

    {
        struct DisplayWindowAxis *first = &source[-1].axes[0];
        first->target[0] = center_x;
        first->target[1] = center_y;
        first->duration = duration;
        first->flags |= 2;
        {
            struct DisplayWindowAxis *last = &source[-1].axes[1];
            last->target[0] = center_x;
            last->target[1] = center_y;
            last->duration = duration;
            last->flags |= 2;
        }
    }
    display_enable_layers(0x6000);
}
