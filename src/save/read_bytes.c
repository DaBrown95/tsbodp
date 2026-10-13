#include "save_stream.h"
#include "heap.h"

void frame_load_save_value(void *destination, int bytes)
{
    if (g_save_stream_state.bit_offset > 0) {
        ++g_save_stream_state.cursor;
        g_save_stream_state.bit_offset = 0;
    }
    heap_copy(destination, g_save_stream_state.cursor, bytes);
    g_save_stream_state.cursor += bytes;
}
asm(".align 2, 0");
