#include "resource_commands.h"
void resource_command_prepare_display(struct ResourceProgramRecord *command)  {
    frame_set_scene_actor_eligibility(COMMAND_BYTE(4));
    resource_activate_groups(COMMAND_BYTE(5),COMMAND_BYTE(6));
}
asm(".align 2, 0");
