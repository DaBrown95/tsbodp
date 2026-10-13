#include "save_stream.h"
#include "heap.h"

void save_stream_initialize_header(void)
{
    unsigned short *source = (unsigned short *)&g_save_stream_state;
    unsigned short sum;
    int count;
    heap_copy(&g_save_stream_state, g_save_header_template, 16);
    sum = 0;
    count = 8;
    do {
        sum += *source++;
    } while (--count > 0);
    g_save_stream_state.header_checksum = -sum;
    save_stream_write_blocks(0, 2, &g_save_stream_state);
}
asm(".align 2, 0");
