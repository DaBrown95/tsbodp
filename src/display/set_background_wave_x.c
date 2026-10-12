#include "display_motion.h"
void display_set_background_wave_x(unsigned int index, unsigned int phase, short step, short amplitude)
{
    struct BackgroundState *background = &g_background_states[index];
    background->phase_x = phase << 8;
    background->phase_step_x = step;
    background->amplitude_x = amplitude;
}
