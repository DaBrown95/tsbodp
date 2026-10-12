#include "input.h"
void input_clear(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        g_input_current[i] = 0;
        g_input_previous[i] = 0;
        g_input_pressed[i] = 0;
        g_input_released[i] = 0;
        g_input_local_current[i] = 0;
        g_input_local_previous[i] = 0;
        g_input_local_pressed[i] = 0;
        g_input_local_released[i] = 0;
    }
}
