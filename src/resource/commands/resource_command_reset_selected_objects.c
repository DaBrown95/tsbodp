#include "resource_commands.h"
void resource_command_reset_selected_objects(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=0;
    if(frame_find_objects(5,141,&object,1)==1&&object) {
        transition_object_set_state((struct TransitionObject *)object,4);
        frame_set_variant_state(object,0);
    }
}
asm(".align 2, 0");
