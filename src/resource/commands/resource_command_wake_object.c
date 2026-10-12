#include "resource_commands.h"
void resource_command_wake_object(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(4),COMMAND_BYTE(5));
    if(object) {
        transition_object_set_state((struct TransitionObject *)object,1);
        object->flags|=8;
    }
}
asm(".align 2, 0");
