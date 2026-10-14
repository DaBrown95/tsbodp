#include "save_stream.h"

unsigned int save_stream_commit_header(void)
{
    union {
        unsigned int words[4];
        unsigned char bytes[16];
    } previous;
    unsigned int remaining;
    unsigned int result;

    save_stream_read_blocks(0, 2, previous.bytes);
    g_save_stream_state.header.words[7] = 0;
    g_save_stream_state.header.words[7] =
        -save_stream_checksum(g_save_stream_state.header.bytes, 16);

    for (remaining = 4; remaining != 0; remaining--)
        if (g_save_stream_state.header.dwords[0] != previous.words[0])
            break;

    if (remaining)
        result = 0;
    else {
        save_stream_write_blocks(0, 2, g_save_stream_state.header.bytes);
        result = 1;
    }
    return result;
}

asm(".align 2,0");
