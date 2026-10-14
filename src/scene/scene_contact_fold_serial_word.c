#include "scene_contact_serial_words.h"

unsigned int scene_contact_fold_serial_word(unsigned short input)
{
    unsigned int current = input;
    unsigned int value = 0;
    register unsigned int remaining asm("r3") = 2;
    do {
        unsigned int mask = 0x80;
        unsigned int next = current >> 8;
        --remaining;
        do {
            value <<= 1;
            if (current & mask) {
                if (value & 0x100)
                    value ^= 0xCC;
                else
                    ++value;
            } else if (value & 0x100) {
                value ^= 0xCD;
            }
            mask >>= 1;
        } while (mask);
        current = next;
    } while (remaining);
    do {
        value <<= 1;
        if (value & 0x100)
            value ^= 0xCD;
        ++remaining;
    } while (remaining <= 7);
    return (unsigned char)value;
}
asm(".align 2, 0");
