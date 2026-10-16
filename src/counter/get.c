#include "game_counter.h"
unsigned int game_get_counter_slot(unsigned int index)
{
    return g_game_counter_slots[index].counter;
}
