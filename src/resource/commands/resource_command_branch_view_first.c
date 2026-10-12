#include "resource_commands.h"
void resource_command_branch_view_first(struct ResourceProgramRecord *command)  {
    if(g_resource_game_state.conditions.cells[COMMAND_BYTE(4)][COMMAND_BYTE(5)].first)resource_activate_groups(COMMAND_BYTE(6),COMMAND_BYTE(7));
    else resource_activate_groups(COMMAND_BYTE(8),COMMAND_BYTE(9));
}
asm(".align 2, 0");
