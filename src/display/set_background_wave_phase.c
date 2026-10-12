#include "display_motion.h"
void display_set_background_wave_phase(unsigned int index, unsigned int x, unsigned int y)
{
    struct BackgroundState *background = &g_background_states[index];
    background->phase_x = x << 8;
    background->phase_y = y << 8;
}
