#include "resource_commands.h"
void resource_command_pause_audio(struct ResourceProgramRecord *command)  {
    audio_game_pause();
}
asm(".align 2, 0");
