#include "resource_commands.h"
void resource_command_select_sequence(struct ResourceProgramRecord *command)  {
    g_audio_control.flags|=8;
    audio_select_sequence(COMMAND_BYTE(4));
}
asm(".align 2, 0");
