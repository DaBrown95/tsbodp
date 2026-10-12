#include "resource_commands.h"
void resource_command_start_view_timer(struct ResourceProgramRecord *command)  {
    unsigned char index;
    for(index=0;index<g_transition_view_context.count;index++) {
        transition_set_view_mode(5,index);
        g_resource_view_effects[index].parameter=(int)COMMAND_SIGNED_HALF(6)<<16;
        g_resource_view_effects[index].duration=COMMAND_HALF(4)*30;
        g_resource_view_effects[index].mode=3;
        g_resource_view_effects[index].phase=0;
        g_resource_view_effects[index].group_a=COMMAND_BYTE(8);
        g_resource_view_effects[index].group_b=COMMAND_BYTE(9);
        if(!g_resource_view_effects[index].duration)g_resource_view_effects[index].ready=1;
        else g_resource_view_effects[index].ready=0;
    }
}
asm(".align 2, 0");
