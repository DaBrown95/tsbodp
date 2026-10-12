#include "resource_commands.h"
void resource_command_set_view_flag(struct ResourceProgramRecord *command)  {
    if(COMMAND_BYTE(4))g_transition_view_context.views[g_transition_view_context.current_view].flags&=~4;
    else g_transition_view_context.views[g_transition_view_context.current_view].flags|=4;
}
asm(".align 2, 0");
