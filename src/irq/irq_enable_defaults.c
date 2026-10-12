#include "irq.h"

void irq_enable_defaults(void) {
 REG16(0x04000208) = 1;
 REG16(0x04000200) = 0x11;
 REG16(0x04000004) = 8;
}
