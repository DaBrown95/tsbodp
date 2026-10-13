#include "save_transfer.h"

unsigned short save_transfer_read_4c9bc(unsigned int block_word, void *destination)
{
    unsigned short serial[68];
    unsigned char i, j;
    unsigned short *cursor, *output = destination;
    unsigned short block;
    block = block_word;
    if (block >= SAVE_TRANSFER_PARAMETERS->blocks)
        return 0x80ff;
    {
        unsigned int offset = SAVE_TRANSFER_PARAMETERS->address_bits * 2;
        unsigned short *base = serial;
        cursor = (unsigned short *)(offset + (unsigned int)base);
        ++cursor;
    }
    i = 0;
    while (i < SAVE_TRANSFER_PARAMETERS->address_bits) {
        *cursor-- = block;
        block >>= 1;
        ++i;
    }
    *cursor-- = 1;
    *cursor = 1;
    save_transfer_dma_copy(serial, (void *)0x0d000000,
                           SAVE_TRANSFER_PARAMETERS->address_bits + 3);
    save_transfer_dma_copy((const void *)0x0d000000, serial, 68);
    cursor = serial + 4;
    output += 3;
    i = 0;
    do {
        unsigned short value = 0;
        j = 0;
        do {
            value <<= 1;
            value |= *cursor++ & 1;
        } while (++j <= 15);
        *output-- = value;
    } while (++i <= 3);
    return 0;
}
asm(".align 2, 0");
