#include "resource_commands.h"
void resource_command_stop_object_effect(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(4),COMMAND_BYTE(5));
    if(object) {
        transition_object_set_state((struct TransitionObject *)object,0);
        frame_set_variant_state(object,0);
        OBJECT_BYTE(object,0x51)=0;
    }
}
asm(".align 2, 0");
