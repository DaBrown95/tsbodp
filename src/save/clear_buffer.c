#include "save_stream.h"
#include "heap.h"

void save_stream_clear_buffer(void)
{
    heap_clear(g_save_stream_state.buffer, 0, 2040);
}
asm(".align 2, 0");
