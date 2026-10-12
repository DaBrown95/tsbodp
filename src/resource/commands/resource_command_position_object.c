#include "resource_commands.h"
void resource_command_position_object(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(8),COMMAND_BYTE(9));
    if(object) {
        object->position.x=(int)COMMAND_SIGNED_HALF(4)<<16;
        object->position.y=(int)COMMAND_SIGNED_HALF(6)<<16;
        OBJECT_BYTE(object,0x12)=COMMAND_BYTE(10)>>1;
        SCRIPT(object)->pending|=0x10;
    }
}
asm(".align 2, 0");
