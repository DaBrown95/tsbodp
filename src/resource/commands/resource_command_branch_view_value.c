#include "resource_commands.h"
void resource_command_branch_view_value(struct ResourceProgramRecord *command)  {
    struct ResourceViewCell cell=g_resource_game_state.conditions.cells[COMMAND_BYTE(4)][COMMAND_BYTE(5)];
    if((unsigned char)(cell.values[COMMAND_BYTE(6)]>>8)==1)resource_activate_groups(COMMAND_BYTE(7),COMMAND_BYTE(8));
    else resource_activate_groups(COMMAND_BYTE(9),COMMAND_BYTE(10));
}
asm(".align 2, 0");
