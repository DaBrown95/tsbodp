#include "display.h"
void display_transfer_palette(const void *input_, unsigned int first_,
    unsigned int count_, struct PaletteBufferPair *pair_)
{
    const void *input = input_;
    unsigned int first = first_;
    unsigned int count = count_;
    struct PaletteBufferPair *pair = pair_;
    unsigned char *destination;
    const void *source;
    count *= 2;
    first *= 2;
    destination = (unsigned char *)pair->staging + first;
    display_copy_bytes(destination, input, count);
    source = destination;
    destination = (unsigned char *)pair->destination + first;
    DISPLAY_DMA3->source = (unsigned int)source;
    DISPLAY_DMA3->destination = (unsigned int)destination;
    count >>= 1;
    DISPLAY_DMA3->control = count | 0x80000000;
    DISPLAY_DMA3->control;
}
