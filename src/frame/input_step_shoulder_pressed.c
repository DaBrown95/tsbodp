#include "input.h"
InputU32 input_step_shoulder_pressed(InputU32 *value, InputU32 minimum, InputU32 maximum, InputU8 wrap, InputU8 player)
{
    if (g_input_pressed[player] & 512) {
        if (*value <= minimum) {
            if (wrap)
                *value = maximum;
        } else {
            (*value)--;
        }
    } else if (g_input_pressed[player] & 256) {
        if (*value >= maximum) {
            if (wrap)
                *value = minimum;
        } else {
            (*value)++;
        }
    }
    return *value;
}

/* Own the zero alignment bytes following this pool-free function. */
asm(".align 2, 0");
