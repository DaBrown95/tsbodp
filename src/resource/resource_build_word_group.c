#include "resource_builders.h"

struct ResourceWordRecord {
    unsigned int words[2];
};

unsigned char *resource_build_word_group(const unsigned char *source,
                                       unsigned char *destination,
                                       unsigned char group)
{
    unsigned int group_offset = group << 1;
    const unsigned short *offsets = (const unsigned short *)(source + 2);
    unsigned int offset = *(const unsigned short *)((const unsigned char *)offsets + group_offset);
    const unsigned char *input = source + offset;
    unsigned char *output = destination;
    unsigned char count = *input, index;

    *(unsigned int *)destination = count;
    for (index = 0; index < count; index++) {
        unsigned int byte_offset = index * sizeof(struct ResourceWordRecord);
        struct ResourceWordRecord *output_record = (struct ResourceWordRecord *)(output + byte_offset + 4);
        const struct ResourceWordRecord *input_record = (const struct ResourceWordRecord *)(input + byte_offset + 4);
        __builtin_memcpy(output_record, input_record, 8);
    }
    offset = count * sizeof(struct ResourceWordRecord);
    destination += 4 + offset;
    return destination;
}
