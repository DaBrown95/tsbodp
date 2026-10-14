#include "display.h"
#include "display_palette_lifecycle.h"

void display_reset_palette_range(struct PaletteRangeJob *job)
{
    display_set_bytes(job, 0, 8);
}
__asm__(".align 2, 0");
