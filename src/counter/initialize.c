#include "game_counter.h"
void game_initialize_counter_slots(void)
{
    unsigned int index;
    for (index = 0; index < 4; index++) {
        game_reset_counter_slot(index);
    }
}
asm(".align 2, 0");
