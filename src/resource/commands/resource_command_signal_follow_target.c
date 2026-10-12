#include "resource_commands.h"
void resource_command_signal_follow_target(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(4),COMMAND_BYTE(5));
    if(object) {
        struct FrameObject *target=OBJECT_POINTER(object,0x64);
        if(target)OBJECT_BYTE(target,0x63)=1;
    }
}
asm(".align 2, 0");
