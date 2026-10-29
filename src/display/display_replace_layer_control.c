#include "display.h"

/* Incoming calls have not yet been established. */
void display_replace_layer_control(unsigned short value)
{
    g_display_control.control =
        (g_display_control.control & 0xE0FFu) | value;
    g_display_control.flags |= 2;
}
