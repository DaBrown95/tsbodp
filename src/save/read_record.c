#include "save_stream.h"
#include "heap.h"

void save_stream_read_record(unsigned int slot)
{
    if (g_save_stream_state.valid[slot]) {
        g_save_stream_state.cursor = g_save_stream_state.buffer;
        g_save_stream_state.bit_offset = 0;
        save_stream_load_record(&g_save_stream_state.records[slot]);
    } else {
        heap_clear(&g_save_stream_state.records[slot], 0, 40);
    }
}
asm(".align 2, 0");
