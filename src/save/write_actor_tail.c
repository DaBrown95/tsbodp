#include "save_game_serialization.h"

void save_stream_write_actor_tail(const void *source)
{
    frame_write_save_value(source, 28);
}
