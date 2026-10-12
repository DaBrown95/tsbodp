#include "display.h"

void display_commit_windows(void)
{
    unsigned int i;
    struct WindowState *window;
    unsigned int horizontal, vertical;
    if (g_display_commit_context->commit_pending) {
        i = 0;
        for (; i < 2; ++i) {
            window = &g_window_states[i];
            if (window->flags & 1) {
                window->flags &= ~1;
                horizontal = (window->horizontal_start << 8) | window->horizontal_end;
                vertical = (window->vertical_start << 8) | window->vertical_end;
                DISPLAY_REG16(0x04000040 + i * 2) = horizontal;
                DISPLAY_REG16(0x04000044 + i * 2) = vertical;
            }
        }
    }
}
