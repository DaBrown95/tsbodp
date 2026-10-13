#include "save_game_loading.h"

void save_stream_read_world_record(struct SaveStreamWorldRecord *record)
{
    frame_load_save_value(record->bytes, 16);
    save_stream_read_pairs(record->pairs + 0, 1);
    save_stream_read_pairs(record->pairs + 1, 1);
    save_stream_read_nibbles(record->nibbles + 0, 1);
    save_stream_read_nibbles(record->nibbles + 1, 1);
    save_stream_read_nibbles(record->nibbles + 2, 1);
    save_stream_read_nibbles(record->nibbles + 3, 1);
    save_stream_read_nibbles(record->nibbles + 4, 1);
    save_stream_read_nibbles(record->nibbles + 5, 1);
    save_stream_read_six_nibbles((struct SaveStreamSixNibbles *)record->region18);
    save_stream_read_relation_values(&record->region20);
    save_stream_read_six_value_words(record->region88);
    frame_load_actor_needs((struct FrameActorNeedState *)record->regiona0);
}
asm(".align 2, 0");
