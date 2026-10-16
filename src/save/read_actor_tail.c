#include "save_game_serialization.h"

void save_stream_read_actor_tail(void *destination)
{
    frame_load_save_value(destination, 28);
}
