#include "resource_commands.h"
void resource_command_wake_group(struct ResourceProgramRecord *command)  {
    unsigned char group=COMMAND_BYTE(4),index;
    unsigned short count;
    if(resource_group_is_enabled(group)) {
        count=resource_group_object_count(group);
        for(index=0;index<count;index++) {
            struct FrameObject *object=resource_get_object(group,index);
            if(object) {
                transition_object_set_state((struct TransitionObject *)object,1);
                object->flags|=8;
            }
        }
    }
}
asm(".align 2, 0");
