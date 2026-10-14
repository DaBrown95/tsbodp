#include "display_text_helpers.h"
char *display_format_hex_text(int value, int digits, char *buffer)
{
    char *start = buffer;
    register char *cursor asm("r2") = buffer;
    int i;
    for (i = digits - 1; i >= 0; i--) {
        int nibble = (value >> (i * 4)) & 15;
        if (nibble <= 9)
            *cursor = nibble + '0';
        else
            *cursor = nibble + ('A' - 10);
        cursor++;
        value = (unsigned int)value - ((unsigned int)nibble << (i * 4));
    }
    *cursor = 0;
    return start;
}
asm(".align 2,0");
