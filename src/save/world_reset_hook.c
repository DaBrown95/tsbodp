#include "save_world_defaults.h"

void save_world_original_reset_hook(void)
{
}

/* The next independent entry starts at the following word boundary. */
asm(".align 2, 0");
