#include "display.h"

/* Incoming callers and historical unused formals remain unknown. */
void display_clear_control_flags(unsigned int mask)
{
    g_display_control.flags &= ~mask;
}
