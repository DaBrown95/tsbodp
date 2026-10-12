#include "display_motion.h"
void display_reset_background_wave_x(unsigned int index)
{
    struct BackgroundState *background = &g_background_states[index];
    background->phase_x = 0;
    background->phase_step_x = 0;
    background->amplitude_x = 0;
}
