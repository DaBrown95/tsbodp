#include "display.h"
#include "heap.h"

/* Incoming callers and any additional unused formals remain unknown. */
void display_release_background_buffer_unrooted_e254(unsigned int index)
{
    struct BackgroundState *background = &g_background_states[index];

    background->flags &= ~0x30u;
    if (background->tilemap_source) {
        heap_free(background->tilemap_source);
        background->tilemap_source = 0;
    }
}

asm(".align 2, 0");
