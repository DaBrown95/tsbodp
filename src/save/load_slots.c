#include "save_stream.h"
#include "heap.h"

void save_stream_load_slots(void)
{
    unsigned int slot;
    for (slot = 0; slot < 4; ++slot) {
        int retry = 0;
        do {
            save_stream_read_slot(slot);
            if ((unsigned char)save_stream_validate_slot(slot)) break;
        } while (retry-- > 0);
        if (g_save_stream_state.valid[slot]) {
            g_save_stream_state.cursor = g_save_stream_state.buffer;
            g_save_stream_state.bit_offset = 0;
            save_stream_load_record(&g_save_stream_state.records[slot]);
        } else {
            heap_clear(&g_save_stream_state.records[slot], 0, 40);
        }
    }
}
asm(".align 2, 0");
