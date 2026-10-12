#include "irq.h"
#include "transition_alpha.h"

void transition_set_alpha(unsigned short a, unsigned short b) {
 g_transition_alpha_a.value = a << 8;
 g_transition_alpha_b.value = b << 8;
 REG16(0x04000052) = a | (b << 8);
}
