#include "display_actor_interaction.h"

unsigned char frame_actor_need_average(struct FrameActorNeedState *needs)
{
    unsigned int sum = 0;
    unsigned char i;
    for (i = 0; i < 8; i++) {
        unsigned int address = (unsigned int)needs + i * 4;
        signed char value = *(signed char *)(address + 3);
        sum += value;
    }
    return sum / 8;
}
