#include "display.h"
void display_set_background_scroll_target(unsigned int index, int x, int y,
    unsigned int duration)
{
    struct BackgroundState *background = &g_background_states[index];
    background->target_x = x;
    background->target_y = y;
    background->scroll_duration = duration;
    background->flags |= 1;
}
