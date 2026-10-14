#include "display.h"
#include "display_palette_lifecycle.h"

void display_remove_palette_block(unsigned int index)
{
    display_reset_palette_block(&g_palette_block_jobs[index]);
}
