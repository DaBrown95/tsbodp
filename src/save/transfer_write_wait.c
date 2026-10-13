#include "save_transfer.h"

unsigned short save_transfer_write_wait(unsigned short block, const void *source)
{
    return save_transfer_write_core(block, source, 1);
}
asm(".align 2, 0");
