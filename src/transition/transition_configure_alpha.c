#include "irq.h"

void transition_configure_alpha(unsigned short first_targets, unsigned short second_targets) {
 REG16(0x04000050) = first_targets | 0x40 | (second_targets << 8);
}
