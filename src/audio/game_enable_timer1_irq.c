#include "audio_game.h"
#include "irq.h"
void audio_game_enable_timer1_irq(void)
{
    REG16(0x04000208) = 0;
    REG16(0x04000200) |= 0x10;
    REG16(0x04000208) = 1;
}
