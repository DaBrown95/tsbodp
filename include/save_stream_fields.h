#ifndef SAVE_STREAM_FIELDS_H
#define SAVE_STREAM_FIELDS_H
#include "save_stream.h"

struct SaveStreamPrefixedHalfword {
    unsigned short unknown00, value;
};
struct SaveStreamPrefixedByte {
    unsigned char unknown00[3], value;
};
/* Overlapping, partial RAM views; they do not establish separate allocations. */
struct SaveStreamWorldFields {
    unsigned char unknown00[0x424];
    struct SaveStreamPrefixedHalfword first, second;
    unsigned char byte42c, nibble42d, bit42e;
};
struct SaveStreamAuxiliaryFields {
    struct SaveStreamPrefixedHalfword first, second;
    struct SaveStreamPrefixedByte tail;
    unsigned char third, second_byte, first_byte;
};
extern struct SaveStreamWorldFields g_save_world_fields;
extern struct SaveStreamAuxiliaryFields g_save_auxiliary_fields;
void save_stream_write_world_fields(void);
void save_stream_write_auxiliary_fields(void);

static inline unsigned short
save_stream_prefixed_halfword(const struct SaveStreamPrefixedHalfword *prefix)
{
    return prefix->value;
}
static inline unsigned char
save_stream_prefixed_byte(const struct SaveStreamPrefixedByte *prefix)
{
    return prefix->value;
}
#endif
