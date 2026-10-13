#include "resource_commands.h"
void resource_command_select_actor(struct ResourceProgramRecord *command)  {
    unsigned char index;
    for(index=0;index<4;index++)g_resource_view_modes[index]=COMMAND_BYTE(5);
    g_resource_game_state.actor.selected_actor=resource_select_actor((unsigned int)g_resource_actor_context,COMMAND_BYTE(4));
    resource_submit_scene(1,0,COMMAND_BYTE(4));
    g_game_flags|=0x800;
}
asm(".align 2, 0");
