#include "resource_commands.h"
extern void transition_set_game_flags(unsigned int);
void resource_command_start_window_transition(struct ResourceProgramRecord *command)  {
    struct FrameObject *object;
    transition_set_game_flags(0x2000000);
    object=resource_create_transition(0);
    SCRIPT(object)->field68.positions.x=COMMAND_HALF(4);
    SCRIPT(object)->field6c.positions.y=COMMAND_HALF(6);
    SCRIPT(object)->field6c.positions.first=COMMAND_BYTE(9);
    SCRIPT(object)->field6c.positions.second=COMMAND_BYTE(10);
    SCRIPT(object)->countdown=COMMAND_BYTE(8);
    transition_object_set_state((struct TransitionObject *)object,4);
    SCRIPT(object)->group_a=COMMAND_BYTE(11);
    SCRIPT(object)->group_b=COMMAND_BYTE(12);
}
asm(".align 2, 0");
