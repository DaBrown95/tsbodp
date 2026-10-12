#include "resource_commands.h"
void resource_command_set_group_flag(struct ResourceProgramRecord *command)  {
    unsigned char group=COMMAND_BYTE(4),index;
    unsigned short count;
    if(resource_group_is_enabled(group)) {
        count=resource_group_object_count(group);
        for(index=0;index<count;index++) {
            struct FrameObject *object=resource_get_object(group,index);
            if(object)object->flags|=1<<COMMAND_BYTE(5);
        }
    }
}
asm(".align 2, 0");
