#include "display_motion.h"
void display_set_background_wave(unsigned int index, const struct DisplayBackgroundWave *wave)
{
    struct BackgroundState *background = &g_background_states[index];
    *(struct DisplayBackgroundWave *)&background->phase_x = *wave;
    background->flags |= 0x40;
}
