#include "resource_commands.h"
void resource_command_reset_object(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(4),COMMAND_BYTE(5));
    if(object) {
        transition_object_set_state((struct TransitionObject *)object,4);
        frame_set_variant_state(object,0);
        if(object->id==2&&resource_group_is_enabled(g_resource_current_program))OBJECT_BYTE(object,0x67)=1;
    }
}
asm(".align 2, 0");
