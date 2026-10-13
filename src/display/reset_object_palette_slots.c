#include "frame_map_scene.h"
#include "display_object_palette.h"

void frame_reset_object_palette_slots(void)
{
    struct FrameMapPaletteState *state = &g_frame_map_palette_state;
    unsigned int i;

    heap_clear(state, 0, 132);
    for (i = 0; i <= 15; i++)
        state->slots[i].id |= 255;
}
