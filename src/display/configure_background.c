#include "display.h"
void display_configure_background(unsigned int index, unsigned int control)
{
    struct BackgroundState *background = &g_background_states[index];
    void *map;
    background->registers.control_word = control;
    map = (void *)(0x06000000 + (((control << 19) >> 27) << 11));
    background->tilemap_destination = map;
    background->tilemap_buffer = map;
    background->character_destination = (void *)(0x06000000 + (((control << 28) >> 30) << 14));
    background->flags |= 0x20;
}
