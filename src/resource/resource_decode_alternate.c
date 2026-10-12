#include "resource_decode.h"

unsigned int resource_decode_alternate(const void *source, void *destination) {
    const void *input = source;
    void *output = destination;
    const struct ResourceStream *stream = (const struct ResourceStream *)input;
    register unsigned int metadata asm("r0") = *(const unsigned int *)stream;
    unsigned int codec = ((metadata << 24) >> 28) & ~8;
    unsigned int size = metadata >> 8;

    switch (codec) {
    case 0: {
        const unsigned char *payload = (const unsigned char *)input + 4;
        unsigned int bytes = size;
        resource_bios_swi_0c(payload, output,
                             ((bytes << 9) >> 11));
        break;
    }
    case 1:
        resource_bios_swi_12(input, output);
        break;
    case 2:
        break;
    case 3:
        resource_bios_swi_15(input, output);
        break;
    case 4:
        g_display_tile_decompress(input, output, &size);
        break;
    case 6: {
        const unsigned char *payload = (const unsigned char *)input + 4;
        g_display_background_decompress(payload, output, &size);
        break;
    }
    case 5:
    case 7:
    case 8:
    default:
        break;
    }
    if (stream->codec & 8)
        resource_decode_delta(output, size);
    return stream->size;
}
asm(".align 2, 0");
