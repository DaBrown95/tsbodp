#include "save_transfer.h"

unsigned short save_transfer_write_core(unsigned int block_word,
                                       const void *source,
                                       unsigned int wait_word)
{
    unsigned short serial[82];
    volatile unsigned short completed, previous, current;
    volatile unsigned int elapsed;
    unsigned char i, j;
    unsigned short *cursor;
    const unsigned short *input = source;
    unsigned short block = block_word;
    unsigned char wait = wait_word;
    unsigned short status;

    if (block >= SAVE_TRANSFER_PARAMETERS->blocks)
        return 0x80ff;
    {
        unsigned int offset = SAVE_TRANSFER_PARAMETERS->address_bits * 2;
        unsigned short *base = serial;
        cursor = (unsigned short *)(offset + (unsigned int)base) + 66;
    }
    *cursor-- = 0;
    i = 0;
    do {
        unsigned short value = *input++;
        j = 0;
        do {
            *cursor-- = value;
            value >>= 1;
        } while (++j <= 15);
    } while (++i <= 3);
    i = 0;
    while (i < SAVE_TRANSFER_PARAMETERS->address_bits) {
        *cursor-- = block;
        block >>= 1;
        ++i;
    }
    *cursor-- = 0;
    *cursor = 1;
    save_transfer_dma_copy(serial, (void *)0x0d000000,
                           SAVE_TRANSFER_PARAMETERS->address_bits + 67);

    status = 0;
    completed = 0;
    previous = *(volatile unsigned short *)0x04000006;
    elapsed = 0;
    for (;;) {
        if (completed == 0 && (*(volatile unsigned short *)0x0d000000 & 1)) {
            ++completed;
            if (wait == 0)
                break;
        }
        current = *(volatile unsigned short *)0x04000006;
        if (current != previous) {
            if (current > previous) {
                volatile unsigned int *total = &elapsed;
                unsigned int difference;
                difference = current - previous;
                *total = difference + *total;
            } else {
                volatile unsigned int *total = &elapsed;
                unsigned int difference;
                difference = current + 228;
                difference -= previous;
                *total = difference + *total;
            }
            if (elapsed > 136) {
                if (completed == 0 && !(*(volatile unsigned short *)0x0d000000 & 1))
                    status = 0xc001;
                break;
            }
            previous = current;
        }
    }
    return status;
}
asm(".align 2, 0");
