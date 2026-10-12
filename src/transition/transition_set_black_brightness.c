#include "irq.h"

void transition_set_black_brightness(unsigned short targets, unsigned short level) {
 REG16(0x04000050) = targets | 0xC0;
 if (level > 16) level = 16;
 REG16(0x04000054) = level;
}
