#include "display.h"

/* The possible interior entry at E1EE has a separate, unresolved contract. */
unsigned int display_read_control_flags(unsigned int mask)
{
    return g_display_control.flags & mask;
}

asm(".align 2, 0");
