#include "save_game_serialization.h"

void save_stream_write_world_record(struct SaveStreamWorldRecord *record)
{
    frame_write_save_value(record->bytes, 16);
    save_stream_write_pairs(record->pairs + 0, 1);
    save_stream_write_pairs(record->pairs + 1, 1);
    save_stream_write_nibbles(record->nibbles + 0, 1);
    save_stream_write_nibbles(record->nibbles + 1, 1);
    save_stream_write_nibbles(record->nibbles + 2, 1);
    save_stream_write_nibbles(record->nibbles + 3, 1);
    save_stream_write_nibbles(record->nibbles + 4, 1);
    save_stream_write_nibbles(record->nibbles + 5, 1);
    save_stream_write_six_nibbles((struct SaveStreamSixNibbles *)record->region18);
    save_subrecord_35f2c(record->region20);
    save_subrecord_3d198(record->region88);
    frame_save_actor_needs((struct FrameActorNeedState *)record->regiona0);
}
asm(".align 2, 0");
