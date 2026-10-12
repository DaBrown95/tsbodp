#include "resource_commands.h"
void resource_command_stop_view_effects(struct ResourceProgramRecord *command)  {
    unsigned char index;
    for(index=0;index<g_transition_view_context.count;index++)g_resource_view_effects[index].mode=0;
    audio_game_stop(g_resource_audio_handle);
}
asm(".align 2, 0");
