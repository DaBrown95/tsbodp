#include "display_text_slots.h"
void display_clear_text_slots(void)
{
    unsigned char i;
    for (i = 0; i <= 5; i++)
        g_display_text_slots[i] = 0;
}
asm(".align 2,0");
