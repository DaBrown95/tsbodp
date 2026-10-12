#include "display.h"
void display_offset_background(unsigned int index)
{
    struct BackgroundState *background = &g_background_states[index];
    if (background->phase_step_x) {
        background->phase_x += background->phase_step_x;
        background->scroll_x += display_scroll_sine(background->phase_x >> 8) * background->amplitude_x;
    }
    if (background->phase_step_y) {
        background->phase_y += background->phase_step_y;
        background->scroll_y += display_scroll_cosine(background->phase_y >> 8) * background->amplitude_y;
    }
}
