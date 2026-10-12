#include "resource_commands.h"
void resource_command_set_object_timer(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(4),COMMAND_BYTE(5));
    if(object) {
        OBJECT_WORD(object,0x14)=resource_scale_value(COMMAND_SIGNED_HALF(6));
        SCRIPT(object)->pending|=8;
    }
}
asm(".align 2, 0");
