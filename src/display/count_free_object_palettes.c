#include "frame_map_scene.h"
#include "display_object_palette.h"

unsigned char frame_count_free_object_palettes(void)
{
    unsigned char count = 0;
    unsigned int i;

    for (i = 8; i <= 15; i++)
        if (g_frame_map_palette_state.slots[i].id == 255)
            count++;
    return count;
}
asm(".align 2, 0");
