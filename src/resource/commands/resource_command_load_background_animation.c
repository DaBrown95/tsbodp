#include "resource_commands.h"
void resource_command_load_background_animation(struct ResourceProgramRecord *command)  {
    background_animation_load(COMMAND_BYTE(4));
    if(resource_group_is_enabled(g_resource_current_program))background_animation_configure_alpha();
}
asm(".align 2, 0");
