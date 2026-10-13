#ifndef SAVE_STREAM_FIELDS_H
#define SAVE_STREAM_FIELDS_H
#include "save_stream.h"

struct SaveStreamPrefixedHalfword {
    unsigned short unknown00, value;
};
struct SaveStreamPrefixedByte {
    unsigned char unknown00[3], value;
};
/* Readers replace the complete word; writers consume its high field. */
union SaveStreamHalfwordField {
    unsigned int word;
    struct SaveStreamPrefixedHalfword prefix;
};
union SaveStreamByteField {
    unsigned int word;
    struct SaveStreamPrefixedByte prefix;
};
/* Overlapping, partial RAM views; they do not establish separate allocations. */
struct SaveStreamWorldFields {
    unsigned char unknown00[0x424];
    union SaveStreamHalfwordField first, second;
    unsigned char byte42c, nibble42d, bit42e;
};
struct SaveStreamAuxiliaryFields {
    union SaveStreamHalfwordField first, second;
    union SaveStreamByteField tail;
    unsigned char third, second_byte, first_byte;
};
extern struct SaveStreamWorldFields g_save_world_fields;
extern struct SaveStreamAuxiliaryFields g_save_auxiliary_fields;
void save_stream_write_world_fields(void);
void save_stream_write_auxiliary_fields(void);
void save_stream_read_world_fields(void);
void save_stream_read_auxiliary_fields(void);

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
