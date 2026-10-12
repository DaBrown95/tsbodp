#include "resource_commands.h"
void resource_command_start_object_interval(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(8),COMMAND_BYTE(9));
    if(object) {
        SCRIPT(object)->field64.word=COMMAND_SIGNED_HALF(4);
        SCRIPT(object)->field68.word=COMMAND_SIGNED_HALF(6);
        SCRIPT(object)->group_a=COMMAND_BYTE(12);
        SCRIPT(object)->group_b=COMMAND_BYTE(10);
        SCRIPT(object)->group_c=COMMAND_BYTE(11);
        SCRIPT(object)->field6c.word=object->flags;
        transition_object_set_state((struct TransitionObject *)object,13);
        frame_set_variant_state(object,0);
        object->flags=(object->flags|8)&0xfffefdbb;
    }
}
asm(".align 2, 0");
