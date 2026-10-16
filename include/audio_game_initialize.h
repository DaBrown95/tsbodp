#ifndef AUDIO_GAME_INITIALIZE_H
#define AUDIO_GAME_INITIALIZE_H
#include "audio_game.h"
#include "audio_frame.h"
/* Observed game setup and shared pacing; names remain provisional. */
void audio_initialize(int);
void audio_set_master_volume(unsigned int);
void audio_game_select_activity_callback(unsigned int);
void audio_game_initialize(void);
void audio_game_initialize_default(void);
void audio_game_shutdown_hardware(void);
void audio_game_set_pacing(unsigned int);
#endif
