#include "display.h"
#include "display_palette_lifecycle.h"

void display_reset_palette_jobs(void)
{
    display_reset_palette_ranges();
    display_reset_palette_blocks();
    g_palette_queue_count = 0;
}
