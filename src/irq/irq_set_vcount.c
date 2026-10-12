#include "irq.h"

void irq_set_vcount(unsigned int line) {
 REG16(0x04000200) |= 4;
 REG16(0x04000004) |= 0x20 | (line << 8);
}
