#include "save_transfer.h"

unsigned short save_transfer_write_nowait(unsigned int block_word, const void *source)
{
    unsigned short block = block_word;
    if (SAVE_TRANSFER_PARAMETERS->byte_size == 512)
        return 0x8080;
    return save_transfer_write_core(block, source, 0);
}
asm(".align 2,0");
