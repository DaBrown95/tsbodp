#include "game_counter.h"
void game_pause_counter_slot(unsigned int index)
{
    g_game_counter_slots[index].paused = 1;
}
