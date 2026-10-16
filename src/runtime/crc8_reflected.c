#include "checksum.h"

unsigned char crc8_reflected(const unsigned char *data, unsigned int length)
{
    unsigned int checksum = 0;
    for (; length--; data++) {
        unsigned int byte = *data;
        unsigned int bit;
        for (bit = 0; bit < 8; bit++) {
            unsigned int mix = (checksum ^ byte) & 1;
            byte >>= 1;
            checksum >>= 1;
            if (mix)
                checksum ^= 0x8c;
        }
    }
    return checksum;
}
