#include "display.h"
extern void display_load_palette(const void *, unsigned int, unsigned int);
unsigned int display_load_resource_palette(const struct BackgroundResource *resource,
                                          unsigned short extra_bank)
{
    const unsigned char *source = (const unsigned char *)resource + 2;
    unsigned int bytes;
    if (resource->flags & 1) {
        bytes = 0x200;
        display_load_palette(source, 0, 0x100);
    } else if (resource->flags & 2) {
        bytes = 0x20;
        display_load_palette(source, ((resource->palette_bank >> 4) + extra_bank) << 4, 0x10);
    } else {
        bytes = 0;
    }
    return bytes;
}
