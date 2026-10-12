#include "resource_commands.h"
void resource_command_set_display_kind(struct ResourceProgramRecord *command)  {
    resource_set_display_kind(g_resource_display_kinds[COMMAND_BYTE(4)]);
}
asm(".align 2, 0");
