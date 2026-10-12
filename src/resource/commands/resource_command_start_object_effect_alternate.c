#include "resource_commands.h"
void resource_command_start_object_effect_alternate(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(4),COMMAND_BYTE(5));
    if(object) {
        transition_object_set_state((struct TransitionObject *)object,26);
        frame_set_variant_state(object,0);
        SCRIPT(object)->mode=26;
        if(!object->id)resource_prepare_object(object);
        else object->flags|=8;
        SCRIPT(object)->field64.bytes.parameter=COMMAND_BYTE(7);
        SCRIPT(object)->field64.bytes.low=COMMAND_BYTE(6);
    }
}
asm(".align 2, 0");
