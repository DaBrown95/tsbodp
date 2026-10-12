#include "display_text_raster.h"
#include "heap.h"

void display_text_initialize(void)
{
    unsigned int group;
    for (group = 0; group < 4; ++group) display_text_load_font(group, 0);
    heap_clear(&g_display_text_state, 0, 60);
    g_display_text_state.work = heap_allocate(2048);
}
