#include "display_text_bank.h"

void display_text_select_bank(unsigned int bank)
{
    g_display_text_selected_bank = bank;
    display_text_set_resource(g_display_text_banks[bank]);
    if (g_display_text_selected_bank == 2)
        g_display_text_bank_value = 32;
    else
        g_display_text_bank_value = 44;
}
asm(".align 2, 0");
