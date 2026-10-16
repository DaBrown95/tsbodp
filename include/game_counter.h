#ifndef GAME_COUNTER_H
#define GAME_COUNTER_H
/* Partial sixteen-byte counter-slot layout supported by original accesses. */
struct GameCounterSlot {
    unsigned int index;
    unsigned int mode;
    unsigned char paused : 1;
    unsigned char : 7;
    unsigned char unknown09[3];
    unsigned int counter;
};
extern struct GameCounterSlot g_game_counter_slots[4];
void game_initialize_counter_slots(void);
void game_reset_counter_slot(unsigned int);
unsigned char game_step_counter_slot(unsigned int);
void game_start_countdown_slot(unsigned int, unsigned int);
void game_start_incrementing_slot(unsigned int);
void game_pause_counter_slot(unsigned int);
void game_resume_counter_slot(unsigned int);
unsigned int game_get_counter_slot(unsigned int);
#endif
