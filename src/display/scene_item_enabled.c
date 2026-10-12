#include "display_scene_redraw.h"
unsigned char display_scene_item_enabled(const unsigned int *mask, unsigned int index)
{
    unsigned char result = 0;
    if (index <= 148) {
        const unsigned int *word = &mask[index >> 5];
        unsigned int shift = index & 31;
        unsigned int bit = 1;
        bit <<= shift;
        result = (*word & bit) != 0;
    }
    return result;
}
