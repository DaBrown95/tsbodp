#include "display_text_fields.h"

void display_text_number_field_two(int value)
{
    char *destination = (void *)g_display_text_fields;
    destination += 128;
    display_text_format_number(value, destination);
}
