#include "game_counter.h"
void game_start_incrementing_slot(unsigned int index)
{
    g_game_counter_slots[index].index = index;
    g_game_counter_slots[index].mode = 2;
    g_game_counter_slots[index].paused = 0;
    g_game_counter_slots[index].counter = 0;
}
