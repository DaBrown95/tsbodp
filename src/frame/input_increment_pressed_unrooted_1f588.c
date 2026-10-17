#include "input.h"

/* Provisional unrooted interface; the observed player byte needs valid backing. */
InputU32 input_increment_pressed_unrooted_1f588(InputU32 *value,
                                             InputU32 minimum,
                                             InputU32 maximum,
                                             InputU8 wrap, InputU8 player)
{
    if (g_input_pressed[player] & 512) {
        if (*value >= maximum) {
            if (wrap)
                *value = minimum;
        } else {
            (*value)++;
        }
    }
    return *value;
}
