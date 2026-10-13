#include "save_transfer.h"

void save_transfer_dma_copy(const void *source, void *destination,
                            unsigned short count)
{
    unsigned short ime = SAVE_TRANSFER_IME;
    SAVE_TRANSFER_IME = 0;
    SAVE_TRANSFER_WAITCNT = (SAVE_TRANSFER_WAITCNT & 0xf8ff)
        | SAVE_TRANSFER_PARAMETERS->wait_control;
    SAVE_TRANSFER_DMA_SOURCE = source;
    SAVE_TRANSFER_DMA_DESTINATION = destination;
    SAVE_TRANSFER_DMA_CONTROL = count | 0x80000000;
    while (SAVE_TRANSFER_DMA_STATUS & 0x8000) {}
    SAVE_TRANSFER_IME = ime;
}
asm(".align 2, 0");
