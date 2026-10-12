#include "irq.h"

void restore_irq_table_entry(unsigned int index) {
 g_irq_table[index] = g_irq_defaults[index];
}
