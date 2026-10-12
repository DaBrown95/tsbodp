#include "display_text_measure_inline.h"

int display_text_measure_width(const char *text)
{
    return display_text_width_inline(text);
}

__asm__(".align 2, 0");
