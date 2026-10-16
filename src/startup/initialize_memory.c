#include "startup_memory.h"

void startup_initialize_memory(void)
{
    startup_clear_unused_ram();
    startup_clear_display_memory();
}
asm(".align 2, 0");
