#include "display_pending_block.h"

void display_pending_noop(unsigned int *value, unsigned int *delta)
{
}

/* The following independent entry begins on a zero-filled word boundary. */
asm(".align 2, 0");
