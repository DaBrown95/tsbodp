#include "save_stream.h"

void save_stream_read_blocks(unsigned int block, unsigned int count, void *buffer)
{
    unsigned char *destination = buffer;
    save_stream_begin_transfer();
    while (count != 0) {
        save_transfer_read_4c9bc(block, destination);
        destination += 8;
        ++block;
        --count;
    }
    save_stream_end_transfer();
}
asm(".align 2, 0");
