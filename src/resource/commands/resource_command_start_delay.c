#include "resource_commands.h"
void resource_command_start_delay(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_create_transition(1);
    SCRIPT(object)->countdown=COMMAND_HALF(4);
    SCRIPT(object)->group_a=COMMAND_BYTE(6);
    SCRIPT(object)->group_b=COMMAND_BYTE(7);
}
asm(".align 2, 0");
