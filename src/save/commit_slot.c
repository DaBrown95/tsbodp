#include "save_stream.h"
#include "heap.h"

void save_stream_commit_slot(unsigned int slot)
{
    save_stream_build_buffer();
    save_stream_suspend_audio();
    save_stream_write_slot(slot);
    save_stream_read_slot(slot);
    save_stream_resume_audio();
    save_stream_validate_slot(slot);
    if (g_save_stream_state.valid[slot]) {
        g_save_stream_state.cursor = g_save_stream_state.buffer;
        g_save_stream_state.bit_offset = 0;
        save_stream_load_record(&g_save_stream_state.records[slot]);
    } else {
        heap_clear(&g_save_stream_state.records[slot], 0, 40);
    }
    g_save_stream_state.selected = slot;
}
asm(".align 2, 0");
