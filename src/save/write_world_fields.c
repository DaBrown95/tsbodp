#include "save_stream_fields.h"

void save_stream_write_world_fields(void)
{
    struct SaveStreamWorldFields *world = &g_save_world_fields;
    unsigned short first = save_stream_prefixed_halfword(&world->first);
    unsigned short second = save_stream_prefixed_halfword(&world->second);

    save_stream_write_bits(&world->bit42e, 1);
    save_stream_write_nibbles(&world->nibble42d, 1);
    frame_write_save_value(&world->byte42c, 1);
    frame_write_save_value(&first, 2);
    frame_write_save_value(&second, 2);
}
asm(".align 2, 0");
