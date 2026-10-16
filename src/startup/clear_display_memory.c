#include "startup_memory.h"

void startup_clear_display_memory(void)
{
    startup_clear_vram();
    startup_clear_oam();
    startup_clear_palette_memory();
}
asm(".align 2, 0");
