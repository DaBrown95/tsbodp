#include "save_stream.h"

unsigned short save_stream_checksum(const void *buffer, unsigned int bytes)
{
    const unsigned short *source = buffer;
    unsigned short sum = 0;
    bytes >>= 1;
    while ((int)bytes > 0) {
        sum += *source++;
        --bytes;
    }
    return sum;
}
asm(".align 2, 0");
