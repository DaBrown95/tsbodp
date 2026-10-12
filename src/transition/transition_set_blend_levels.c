#include "irq.h"

void transition_set_blend_levels(unsigned char a, unsigned char b, unsigned char brightness) {
 REG16(0x04000052) = (b << 8) | a;
 REG16(0x04000054) = brightness;
}
