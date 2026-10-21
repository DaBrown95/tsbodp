#include "display.h"
#include "heap.h"

/* Incoming callers and any additional unused formals remain unknown. */
void display_enable_background_buffer_unrooted_e21c(unsigned int index)
{
    struct BackgroundState *background = &g_background_states[index];

    if (!background->tilemap_source) {
        background->tilemap_source = heap_allocate_zeroed(2048);
        background->flags &= ~0x20u;
    }
    background->flags |= 0x10u;
}

asm(".align 2, 0");
