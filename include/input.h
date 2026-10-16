#ifndef TSBODP_INPUT_H
#define TSBODP_INPUT_H

/* Reconstructed state for local and linked input. Original names are unknown. */
typedef unsigned char InputU8;
typedef unsigned short InputU16;
typedef unsigned int InputU32;
struct InputConfig {
    InputU8 unknown_00[48];
    InputU8 player_count, local_player;
};
extern struct InputConfig g_input_config;
extern InputU16 g_input_current[4], g_input_previous[4];
extern InputU16 g_input_pressed[4], g_input_released[4];
extern InputU16 g_input_local_current[4], g_input_local_previous[4];
extern InputU16 g_input_local_pressed[4], g_input_local_released[4];
extern InputU16 g_input_disabled[4], g_input_link_received[4];
extern InputU16 g_input_idle_frames;
extern InputU8 g_input_direction_table[16];
void input_clear(void);
void input_poll(void);
void input_enable(void);

#endif /* TSBODP_INPUT_H */
