#include "save_stream.h"
#include "heap.h"
#include "save_game_serialization.h"
/* The unsigned quotient remains an explicit original provider. */
unsigned int __udivsi3(unsigned int, unsigned int);
void save_stream_build_buffer(void)
{
    unsigned char *buffer;
    unsigned short *checksum;
    unsigned int used, *percentage;
    unsigned int zero;
    {
        struct SaveStreamState *state = &g_save_stream_state;
        unsigned char **cursor;
        unsigned int *bit_offset;
        {
            register unsigned int clear_bytes asm("r2");
            register int clear_value asm("r1");
            heap_clear(state->buffer, (clear_value = 0), (clear_bytes = 2040));
        }
        buffer = state->buffer;
        cursor = &state->cursor;
        *cursor = buffer;
        bit_offset = &state->bit_offset;
        *bit_offset = (zero = 0);
        save_stream_serialize_game_state();
        used = (state->used = *cursor - buffer);
        percentage = &state->percentage;
    }
    {
        unsigned int span;
        *percentage = __udivsi3(used * 100, (span = 2040));
        checksum = (unsigned short *)(buffer + 2038);
        *checksum = zero;
        *checksum = -save_stream_checksum(buffer, span);
    }
}
asm(".align 2,0");
