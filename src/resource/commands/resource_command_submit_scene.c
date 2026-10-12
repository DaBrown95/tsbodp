#include "resource_commands.h"
void resource_command_submit_scene(struct ResourceProgramRecord *command)  {
    resource_submit_scene(13,0,g_resource_scene_arg);
    g_game_flags=(g_game_flags|0x800)&~0x20;
}
asm(".align 2, 0");
