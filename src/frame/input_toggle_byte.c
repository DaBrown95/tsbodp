#include "input.h"

/* Provisional unrooted interface; incoming callers and unused formals unknown. */
void input_toggle_byte(InputU8 *value)
{
    *value = !*value;
}
