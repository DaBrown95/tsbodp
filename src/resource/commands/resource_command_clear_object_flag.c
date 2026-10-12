#include "resource_commands.h"
void resource_command_clear_object_flag(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(4),COMMAND_BYTE(5));
    if(object)object->flags&=~(1<<COMMAND_BYTE(6));
}
asm(".align 2, 0");
