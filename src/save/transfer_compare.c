#include "save_transfer.h"

unsigned short save_transfer_compare(unsigned int block_word, const void *source)
{
    unsigned short data[4], *cursor;
    const unsigned short *input = source;
    unsigned short block = block_word;
    unsigned short status = 0;
    unsigned char i;

    if (block >= SAVE_TRANSFER_PARAMETERS->blocks)
        return 0x80ff;
    save_transfer_read_4c9bc(block, data);
    cursor = data;
    i = 0;
    while (i <= 3) {
        if (*input++ != *cursor++) {
            status = 0x8000;
            break;
        }
        ++i;
    }
    return status;
}
asm(".align 2, 0");
