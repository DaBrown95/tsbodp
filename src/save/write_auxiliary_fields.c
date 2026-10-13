#include "save_stream_fields.h"

void save_stream_write_auxiliary_fields(void)
{
    unsigned char *last = (unsigned char *)&g_save_auxiliary_fields + 14;
    unsigned short first, second;
    unsigned char tail;

    frame_write_save_value(last, 1);
    frame_write_save_value(last - 1, 1);
    frame_write_save_value(last - 2, 1);
    first = save_stream_prefixed_halfword(
        &((union SaveStreamHalfwordField *)(last - 14))->prefix);
    second = save_stream_prefixed_halfword(
        &((union SaveStreamHalfwordField *)(last - 10))->prefix);
    frame_write_save_value(&first, 2);
    frame_write_save_value(&second, 2);
    tail = save_stream_prefixed_byte(
        &((union SaveStreamByteField *)(last - 6))->prefix);
    frame_write_save_value(&tail, 1);
}
asm(".align 2, 0");
