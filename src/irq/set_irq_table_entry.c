/* Index bounds and valid handler values are the caller's responsibility. */
extern unsigned int g_irq_table[];

void set_irq_table_entry(unsigned int index, unsigned int handler)
{
    g_irq_table[index] = handler;
}
