#include "resource_commands.h"
void resource_command_set_triple(struct ResourceProgramRecord *command)  {
    resource_set_triple(COMMAND_BYTE(4),COMMAND_BYTE(5),COMMAND_BYTE(6));
}
asm(".align 2, 0");
