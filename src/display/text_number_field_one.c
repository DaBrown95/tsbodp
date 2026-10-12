#include "display_text_fields.h"

void display_text_number_field_one(int value)
{
    char *destination = (void *)g_display_text_fields;
    destination += 64;
    display_text_format_number(value, destination);
}
