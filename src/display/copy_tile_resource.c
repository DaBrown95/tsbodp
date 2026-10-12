#include "display.h"
void display_copy_tile_resource(struct DisplayTileResource *resource, unsigned short first)
{
    const struct DisplayTileLayout *layout = (const struct DisplayTileLayout *)resource->layout;
    struct DisplayTileRecord *record;
    unsigned int offset = 0;
    unsigned int i = 0;
    unsigned char *destination;
    unsigned int scratch, record_offset;
    for (; i < *(const unsigned short *)(resource->layout + 6); ++i) {
        record_offset = layout->record_offsets[i];
        record_offset += 12;
        record = (struct DisplayTileRecord *)((unsigned char *)layout + record_offset);
        destination = (unsigned char *)0x06010000 + first * 32 + offset;
        offset += display_bios_div(record->width * record->height, 2);
        if (record->flags & 0x40) {
            register void (**decoder)(const void *, void *, unsigned int *) __asm__("r2") = &g_display_tile_decompress;
            (*decoder)(resource->data + record->data_offset, destination, &scratch);
        }
        else if (record->flags & 0x20)
            display_bios_swi_15(resource->data + record->data_offset, destination);
        else
            display_cpu_copy(resource->data + record->data_offset, destination,
                             ((offset << 9) >> 11) | 0x04000000);
    }
}
