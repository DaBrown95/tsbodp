#include "display_motion.h"
void display_set_background_wave_step(unsigned int index, short x, short y)
{
    struct BackgroundState *background = &g_background_states[index];
    background->phase_step_x = x;
    background->phase_step_y = y;
}
