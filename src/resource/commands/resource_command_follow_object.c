#include "resource_commands.h"
void resource_command_follow_object(struct ResourceProgramRecord *command)  {
    register struct FrameObject *object asm("r4")=resource_get_object(COMMAND_BYTE(4),COMMAND_BYTE(5));
    if(object) {
        struct FrameObject *target=resource_get_object(COMMAND_BYTE(6),COMMAND_BYTE(7));
        if(!target)target=(struct FrameObject *)g_transition_view_context.views[0].object;
        SCRIPT(object)->field64.target=target;
        transition_object_set_state((struct TransitionObject *)object,29);
        frame_set_variant_state(object,0);
        object->flags|=8;
    }
}
asm(".align 2, 0");
