#include "resource_commands.h"
void resource_command_attach_object(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(4),COMMAND_BYTE(5));
    if(object) {
        struct FrameObject *target=resource_get_object(COMMAND_BYTE(6),COMMAND_BYTE(7));
        if(!target)target=(struct FrameObject *)g_transition_view_context.views[0].object;
        OBJECT_POINTER(object,0x68)=target;
        transition_object_set_state((struct TransitionObject *)object,8);
        frame_set_variant_state(object,7);
        SCRIPT(object)->argument_a=COMMAND_BYTE(9);
        SCRIPT(object)->argument_b=COMMAND_BYTE(10);
        object->flags|=8;
    }
}
asm(".align 2, 0");
