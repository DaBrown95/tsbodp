#include "resource_commands.h"
void resource_command_start_special_object_effect(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(4),COMMAND_BYTE(5));
    if(object&&object->id==7&&object->unknown_0a>31) {
        object->flags|=8;
        transition_object_set_state((struct TransitionObject *)object,24);
        frame_set_variant_state(object,2);
        OBJECT_BYTE(object,0x51)=24;
    }
}
asm(".align 2, 0");
