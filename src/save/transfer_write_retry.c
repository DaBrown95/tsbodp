#include "save_transfer.h"

unsigned short save_transfer_write_retry(unsigned int block_word, const void *source)
{
    const void *input = source;
    unsigned short block = block_word, status;
    unsigned char retries = 0;

    while (retries <= 2) {
        status = save_transfer_write_wait(block, input);
        if (status == 0) {
            status = save_transfer_compare(block, input);
            if (status == 0)
                break;
        }
        ++retries;
    }
    return status;
}
asm(".align 2, 0");
