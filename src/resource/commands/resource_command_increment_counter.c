#include "resource_commands.h"
void resource_command_increment_counter(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(4),COMMAND_BYTE(5));
    if(object&&object->id==2)OBJECT_BYTE(object,0x71)++;
}
asm(".align 2, 0");
