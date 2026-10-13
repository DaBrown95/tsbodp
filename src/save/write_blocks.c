#include "save_stream.h"

void save_stream_write_blocks(unsigned int block, unsigned int count, const void *buffer)
{
    const unsigned char *source = buffer;
    save_stream_begin_transfer();
    while (count != 0) {
        save_transfer_write_4ccb0(block, source);
        source += 8;
        ++block;
        --count;
    }
    save_stream_end_transfer();
}
asm(".align 2, 0");
