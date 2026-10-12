#include "display_text_fields.h"

void display_text_number_field(int value, unsigned int slot)
{
    display_text_format_number(value, (void *)g_display_text_fields[slot]);
}
