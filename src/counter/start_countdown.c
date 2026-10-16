#include "game_counter.h"
void game_start_countdown_slot(unsigned int index, unsigned int counter)
{
    g_game_counter_slots[index].index = index;
    g_game_counter_slots[index].mode = 1;
    g_game_counter_slots[index].paused = 0;
    g_game_counter_slots[index].counter = counter;
}
