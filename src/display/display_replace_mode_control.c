#include "display.h"

/* Incoming calls have not yet been established. */
void display_replace_mode_control(unsigned short value)
{
    g_display_control.control =
        (g_display_control.control & 0xFFF8u) | value;
    g_display_control.flags |= 2;
}
