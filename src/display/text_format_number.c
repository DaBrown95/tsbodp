#include "display_text_fields.h"

#define WRITE_DECIMAL_PLACE(place, grouped) do { \
    if (value > (place) - 1 || digit != -1) { \
        digit = value / (place); \
        value %= (place); \
        *cursor++ = digit + '0'; \
        if (grouped) *cursor++ = g_display_text_number_separator; \
    } \
} while (0)

char *display_text_format_number(int input_value, char *destination)
{
    char *cursor = destination;
    int value = input_value;
    int digit = -1;
    if (value < 0) {
        value = (int)(0U - (unsigned int)value);
        *cursor++ = '-';
    }
    WRITE_DECIMAL_PLACE(1000000000, 1);
    WRITE_DECIMAL_PLACE(100000000, 0);
    WRITE_DECIMAL_PLACE(10000000, 0);
    WRITE_DECIMAL_PLACE(1000000, 1);
    WRITE_DECIMAL_PLACE(100000, 0);
    WRITE_DECIMAL_PLACE(10000, 0);
    WRITE_DECIMAL_PLACE(1000, 1);
    WRITE_DECIMAL_PLACE(100, 0);
    WRITE_DECIMAL_PLACE(10, 0);
    *cursor = value + '0';
    cursor[1] = 0;
    return destination;
}
