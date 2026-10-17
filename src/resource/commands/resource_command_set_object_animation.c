#include "resource_commands.h"
void resource_command_set_object_animation(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(4),COMMAND_BYTE(5));
    if(object) {
        unsigned char animation,special;
        OBJECT_BYTE(object,0x12)=COMMAND_BYTE(7);
        special=COMMAND_BYTE(7);
        animation=COMMAND_BYTE(6);
        if(special>4)object->render_special=-1;
        else object->render_special=0;
        transition_object_set_state((struct TransitionObject *)object,6);
        frame_request_animation((struct FrameCommandObject *)object,animation+0x60);
        frame_stop_motion(object);
    }
}
asm(".align 2, 0");
