#include "save_stream.h"
#include "heap.h"

void frame_write_save_value(const void *source, int bytes)
{
    if (g_save_stream_state.bit_offset > 0) {
        *g_save_stream_state.cursor &= 255 >> (8 - g_save_stream_state.bit_offset);
        ++g_save_stream_state.cursor;
        g_save_stream_state.bit_offset = 0;
    }
    heap_copy(g_save_stream_state.cursor, source, bytes);
    g_save_stream_state.cursor += bytes;
}
asm(".align 2, 0");
