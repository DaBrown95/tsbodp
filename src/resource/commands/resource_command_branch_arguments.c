#include "resource_commands.h"
void resource_command_branch_arguments(struct ResourceProgramRecord *command)  {
    struct DisplayTimeRecord first=g_resource_branch_default,second=g_resource_branch_default;
    first.hour=COMMAND_BYTE(4);
    first.minute=COMMAND_BYTE(5);
    second.hour=COMMAND_BYTE(6);
    second.minute=COMMAND_BYTE(7);
    if((unsigned char)display_time_in_range(&first,&second,(const struct DisplayTimeRecord *)g_resource_branch_context,6))resource_activate_groups(COMMAND_BYTE(8),COMMAND_BYTE(9));
    else resource_activate_groups(COMMAND_BYTE(10),COMMAND_BYTE(11));
}
asm(".align 2, 0");
