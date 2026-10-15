#include "save_stream.h"

void save_stream_load_record(struct SaveStreamRecord *record)
{
    frame_load_save_value(&g_save_serialized_marker, 1);
    frame_load_save_value(&record->unknown00, 4);
    frame_load_save_value(record->clock_storage.serialized.unknown04, 6);
    frame_load_save_value(&record->signed24, 3);
    if (record->signed24 & 0x800000)
        record->signed24 |= 0xff000000;
    frame_load_save_value(record->unknown10, 16);
    save_stream_read_pairs(&record->pairs[0], 1);
    save_stream_read_pairs(&record->pairs[1], 1);
    save_stream_read_nibbles(&record->nibbles[0], 1);
    save_stream_read_nibbles(&record->nibbles[1], 1);
    save_stream_read_nibbles(&record->nibbles[2], 1);
    save_stream_read_nibbles(&record->nibbles[3], 1);
    save_stream_read_nibbles(&record->nibbles[4], 1);
    save_stream_read_nibbles(&record->nibbles[5], 1);
}
asm(".align 2, 0");
