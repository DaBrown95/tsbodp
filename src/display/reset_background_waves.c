#include "display_motion.h"
void display_reset_background_waves(unsigned int index)
{
    struct BackgroundState *background = &g_background_states[index];
    display_reset_background_wave_x(index);
    display_reset_background_wave_y(index);
    background->flags &= ~0x40;
}
