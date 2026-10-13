#include "frame_map_scene.h"
#include "display_object_palette.h"

unsigned int frame_find_object_palette_slot(const void *const *resources)
{
    unsigned int result = 255, i, j;

    for (i = 8; i <= 15; i++) {
        if (g_frame_map_palette_state.slots[i].id == 255) {
            if (result == 255)
                result = i;
        } else {
            /* Only the first palette pointer participates in this comparison. */
            for (j = 0; j < 1; j++)
                if (g_frame_map_palette_state.slots[i].sources[j] != resources[j])
                    break;
            if (j == 1) {
                result = i;
                break;
            }
        }
    }
    return result;
}
asm(".align 2, 0");
