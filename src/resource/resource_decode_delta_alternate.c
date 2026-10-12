#include "resource_decode.h"

void resource_decode_delta_alternate(void *destination, unsigned int bytes) {
    unsigned int index = 1;
    bytes >>= 1;
    if (index < bytes) {
        unsigned short *cursor = destination;
        do {
            unsigned int next = cursor[1];
            cursor[1] = cursor[0] + next;
            cursor++;
            index++;
        } while (index < bytes);
    }
}
asm(".align 2, 0");
