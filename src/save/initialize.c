#include "save_stream.h"
#include "heap.h"

void save_stream_initialize(void)
{
    g_save_stream_state.buffer = heap_allocate_zeroed(2040);
    if (!save_stream_validate_header()) {
        unsigned int slot, block;
        struct SaveStreamState *state;
        save_stream_initialize_header();
        save_stream_clear_buffer();
        slot = 0;
        state = &g_save_stream_state;
        block = 2;
        do {
            save_stream_write_blocks(block, 5, state->buffer);
            block += 255;
            ++slot;
        } while (slot < 4);
    }
    display_text_select_bank(g_save_stream_state.header.bytes[10]);
    save_stream_load_slots();
}
asm(".align 2, 0");
