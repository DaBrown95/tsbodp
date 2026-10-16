#include "game_counter.h"
unsigned char game_step_counter_slot(unsigned int index)
{
    unsigned int complete;
    switch (g_game_counter_slots[index].mode) {
    case 0:
        complete = 1;
        break;
    case 1:
        if (!g_game_counter_slots[index].counter) {
            complete = 1;
        } else if (g_game_counter_slots[index].paused) {
            complete = 0;
        } else {
            g_game_counter_slots[index].counter--;
            complete = g_game_counter_slots[index].counter == 0;
        }
        break;
    case 2:
        if (!g_game_counter_slots[index].paused) {
            g_game_counter_slots[index].counter++;
        }
        complete = 0;
        break;
    default:
        complete = 0;
        break;
    }
    return complete;
}
asm(".align 2, 0");
