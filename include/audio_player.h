#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H
#include "audio_frame.h"
#include "audio_sample.h"

/* Partial 32-byte prefix of the sequencer state; remaining storage is unknown. */
struct AudioPlayerState {
    unsigned int flags;
    int state;
    const unsigned char *song;
    unsigned char unknown0c[17];
    signed char volume;
    unsigned char unknown1e[2];
};
extern struct AudioPlayerState g_audio_player;
extern int g_audio_player_volume_current, g_audio_player_volume_target;
extern int g_audio_player_volume_step;
extern void (*g_audio_player_callback)(int, int);
void audio_player_tick(void);
void audio_player_pause(int);
void audio_player_resume(void);
int audio_player_is_paused(void);
void audio_player_set_volume(unsigned int, int);
void audio_player_set_callback(void (*)(int, int));
#endif
