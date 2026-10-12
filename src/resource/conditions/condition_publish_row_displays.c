#include "resource_commands.h"
#include "resource_conditions.h"
void condition_publish_row_displays(unsigned int row)
{
    int index;
    for (index = 0; index < 5; index++) {
        unsigned char kind = g_condition_definitions[row].display_kinds[index];
        if (kind != 0xff)
            resource_set_display_kind(kind);
    }
}
