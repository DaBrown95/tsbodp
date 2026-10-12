#include "display_scene_lifecycle.h"
void display_release_tile_bytes_immediately(FrameU16 first, FrameU32 bytes, FrameU8 small_tiles)
{
    FrameU16 count;
    if (small_tiles)
        count = bytes >> 5;
    else
        count = bytes >> 6;
    display_release_tiles_immediately(first, count);
}
/* Zero-filled alignment after the pool-free Thumb function. */
__asm__(".align 2, 0");
