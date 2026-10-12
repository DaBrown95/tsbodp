#include "resource_commands.h"
void resource_command_play_cue(struct ResourceProgramRecord *command)  {
    audio_play_animation_cue(COMMAND_BYTE(4));
}
asm(".align 2, 0");
