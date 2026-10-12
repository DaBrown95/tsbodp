#include "irq.h"

void irq_disable_vcount(void) {
 REG16(0x04000200) &= 0xFFFB;
 REG16(0x04000004) &= 0xFFDF;
}
