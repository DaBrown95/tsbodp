#include "resource_commands.h"
void resource_command_resume_audio(struct ResourceProgramRecord *command)  {
    audio_game_resume();
}
asm(".align 2, 0");
