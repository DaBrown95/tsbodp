#include "resource_commands.h"
void resource_command_select_resource(struct ResourceProgramRecord *command)  {
    if(!COMMAND_BYTE(5)||(g_game_flags&0x20))g_resource_selected=COMMAND_BYTE(4);
}
asm(".align 2, 0");
