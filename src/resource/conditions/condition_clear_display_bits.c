#include "resource_conditions.h"
void condition_clear_display_bits(void)
{
    unsigned int index;
    for(index=0;index<15;index++)g_condition_display_bits[index]=0;
}
