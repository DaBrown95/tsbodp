#include "input.h"
InputU32 input_step_local_horizontal_pressed(InputU32 *value, InputU32 minimum, InputU32 maximum, InputU8 wrap, InputU8 player)
{
    if (g_input_local_pressed[player] & 32) {
        if (*value <= minimum) {
            if (wrap)
                *value = maximum;
        } else {
            (*value)--;
        }
    } else if (g_input_local_pressed[player] & 16) {
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
