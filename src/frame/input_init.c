#include "input.h"
void input_init(void)
{
    input_enable();
    input_clear();
}

/* Own the zero alignment bytes following this pool-free function. */
asm(".align 2, 0");
