#include "resource_commands.h"
void resource_command_set_sample_volume(struct ResourceProgramRecord *command)  {
    audio_game_set_sample_volume(COMMAND_BYTE(4));
}
asm(".align 2, 0");
