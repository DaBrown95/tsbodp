#include "display.h"
#include "display_palette_lifecycle.h"

void display_step_palette_jobs(void)
{
    display_step_palette_ranges();
    display_step_palette_blocks();
}
__asm__(".align 2, 0");
