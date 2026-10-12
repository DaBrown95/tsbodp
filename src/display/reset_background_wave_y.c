#include "display_motion.h"
void display_reset_background_wave_y(unsigned int index)
{
    struct BackgroundState *background = &g_background_states[index];
    background->phase_y = 0;
    background->phase_step_y = 0;
    background->amplitude_y = 0;
}
