#include "resource_commands.h"
#include "resource_conditions.h"
void condition_complete_if_active(unsigned int row,unsigned int column,unsigned int entry)
{
    unsigned char *state=(unsigned char *)&g_resource_game_state;
    unsigned int offset=entry*4;
    offset+=column*24;
    offset+=row*144;
    offset+=(unsigned int)state;
    if(*(unsigned char *)(offset+0x448)) resource_set_triple(row,column,entry);
}
