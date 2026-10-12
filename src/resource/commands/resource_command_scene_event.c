#include "resource_commands.h"
void resource_command_scene_event(struct ResourceProgramRecord *command)  {
    resource_scene_event(5);
    g_game_flags|=0x800;
}
asm(".align 2, 0");
