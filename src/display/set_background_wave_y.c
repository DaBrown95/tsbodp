#include "display_motion.h"
void display_set_background_wave_y(unsigned int index, unsigned int phase, short step, short amplitude)
{
    struct BackgroundState *background = &g_background_states[index];
    background->phase_y = phase << 8;
    background->phase_step_y = step;
    background->amplitude_y = amplitude;
}
