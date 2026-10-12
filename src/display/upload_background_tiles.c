#include "display.h"
void display_upload_background_tiles(unsigned int index, unsigned short first,
    unsigned short count, const void *source)
{
    struct BackgroundState *background = &g_background_states[index];
    if (*(unsigned char *)background & 0x80) {
        first <<= 1;
        count <<= 1;
    }
    display_cpu_copy(source, (unsigned char *)background->character_destination + first * 32, count << 4);
}
