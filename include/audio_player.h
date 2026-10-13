/*
 * Layout names adapted from Krawall lib/player.c and lib/mtypes.h.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: observed partial game layouts and direct mixer handoff declarations.
 * LGPL-2.1-or-later; see licenses/Krawall-LGPL-2.1.txt for the licence.
 */
#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H
#include "audio_frame.h"

/* Partial 96-byte track view: handle and envelope flag are observed fields. */
struct AudioPlayerTrack {
    unsigned int handle;
    signed char volume, cvolume, panning;
    unsigned char unknown07, effect, unknown09[5];
    unsigned short periodc;
    unsigned char unknown10[4];
    const struct AudioInstrument *instrument;
    unsigned char unknown18[12];
    const short *vibrtable;
    unsigned char unknown28[35];
    unsigned char envelope_enabled, i_vol_status;
    signed char i_vol;
    unsigned short i_vol_pos;
    unsigned char i_vol_node, i_vol_tick, i_vol_ticktarget, i_vol_fadeactive;
    short i_vol_fade;
    unsigned char i_pan_status;
    signed char i_pan;
    unsigned short i_pan_pos;
    unsigned char i_pan_node, i_pan_tick, i_pan_ticktarget, volume_effect;
    unsigned char i_vibrpos, unknown5f;
};
/* Observed 52-byte prefix followed by tracks; allocation bounds remain provisional. */
struct AudioPlayerState {
    unsigned int flags;
    int state;
    const unsigned char *song;
    unsigned char unknown0c[2];
    unsigned char speed, tick;
    unsigned char unknown10[13];
    signed char volume;
    unsigned char unknown1e[2];
    unsigned char instrument_based;
    unsigned char unknown21[3];
    unsigned int unknown24;
    unsigned int (*calc_final_frequency)(unsigned int);
    unsigned char unknown2c[8];
    struct AudioPlayerTrack tracks[];
};
struct AudioVolumeEffect {
    void (*apply)(struct AudioPlayerTrack *, int);
    unsigned char update_enabled, unknown05[3];
};
struct AudioTrackEffect {
    void (*apply)(struct AudioPlayerTrack *, int);
    void (*tick)(struct AudioPlayerTrack *, int);
    unsigned char update_enabled, unknown09[3];
};
extern const struct AudioVolumeEffect g_audio_volume_effects[];
extern const struct AudioTrackEffect g_audio_track_effects[];
extern struct AudioPlayerState g_audio_player;
extern int g_audio_player_volume_current, g_audio_player_volume_target;
extern int g_audio_player_volume_step;
extern void (*g_audio_player_callback)(int, int);
void audio_player_tick(void);
void audio_player_process_row(void);
void audio_player_process_between_row(void);
void audio_player_process_instruments(struct AudioPlayerTrack *, int);
void audio_player_pause(int);
void audio_player_resume(void);
int audio_player_is_paused(void);
void audio_player_set_volume(unsigned int, int);
void audio_player_set_callback(void (*)(int, int));
#endif
