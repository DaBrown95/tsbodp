#include "input.h"
void input_disable(void)
{
    InputU16 *base = g_input_disabled;
    InputU16 value = 1;
    InputU16 *p = base + 3;
    do {
        *p-- = value;
    } while ((int)p >= (int)base);
}
