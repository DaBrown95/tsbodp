#include "resource_commands.h"
#include "resource_conditions.h"

unsigned char condition_is_active(unsigned int row, unsigned int column, unsigned int entry)
{
    unsigned char *state = (unsigned char *)&g_resource_game_state;
    unsigned int offset = entry*4;
    offset += column*24;
    offset += row*144;
    offset += (unsigned int)state;
    return *(unsigned char *)(offset + 0x448);
}
