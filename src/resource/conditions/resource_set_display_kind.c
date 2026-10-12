#include "resource_commands.h"
#include "resource_conditions.h"
void resource_set_display_kind(unsigned int kind)
{
    g_condition_display_bits[kind>>3] |= 1<<(kind&7);
}
