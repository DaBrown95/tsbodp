#include "display.h"

/* Incoming callers and any unused historical formals remain unknown. */
void display_clear_control_bit0(void)
{
    g_display_control.flags &= ~1u;
}
