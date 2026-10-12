#include "resource_commands.h"
void resource_command_branch_arguments(struct ResourceProgramRecord *command)  {
    struct ResourceBranchArgument first=g_resource_branch_default,second=g_resource_branch_default;
    first.row=COMMAND_BYTE(4);
    first.column=COMMAND_BYTE(5);
    second.row=COMMAND_BYTE(6);
    second.column=COMMAND_BYTE(7);
    if(resource_compare_arguments(&first,&second,g_resource_branch_context,6))resource_activate_groups(COMMAND_BYTE(8),COMMAND_BYTE(9));
    else resource_activate_groups(COMMAND_BYTE(10),COMMAND_BYTE(11));
}
asm(".align 2, 0");
