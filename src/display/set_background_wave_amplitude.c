#include "display_motion.h"
void display_set_background_wave_amplitude(unsigned int index, short x, short y)
{
    struct BackgroundState *background = &g_background_states[index];
    background->amplitude_x = x;
    background->amplitude_y = y;
}
