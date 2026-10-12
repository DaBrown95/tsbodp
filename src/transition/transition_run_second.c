typedef void (*TransitionHandler)(unsigned short);
extern unsigned int g_game_flags;
extern TransitionHandler g_transition_second_handlers[];

void transition_run_second(unsigned short targets, unsigned int kind) {
 g_game_flags |= 0x4000;
 g_transition_second_handlers[kind](targets);
 g_game_flags &= ~0x4000;
}
