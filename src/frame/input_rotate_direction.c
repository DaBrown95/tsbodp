#include "input.h"
InputU8 input_rotate_direction(InputU8 player, InputU8 direction)
{
    int next = direction;
    if (g_input_current[player] & 0x20) {
        next--;
        if (next < 0)
            next = 15;
    } else if (g_input_current[player] & 0x10) {
        next++;
        if (next > 15)
            next = 0;
    } else {
        next = 16;
    }
    return next;
}
