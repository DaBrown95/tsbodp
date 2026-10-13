#include "save_stream.h"

unsigned char save_stream_validate_header(void)
{
    unsigned short *source = g_save_stream_state.header.words;
    unsigned short sum;
    int count;
    int byte;
    save_stream_read_blocks(0, 2, &g_save_stream_state);
    sum = 0;
    count = 8;
    do {
        sum += *source++;
    } while (--count > 0);
    if (sum != 0) return 0;
    for (byte = 0; byte < 8; ++byte)
        if (g_save_stream_state.header.bytes[byte] != g_save_header_template[byte]) return 0;
    return 1;
}
asm(".align 2, 0");
