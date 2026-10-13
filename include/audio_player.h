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

/* Partial 96-byte track view; sequencer and envelope names are inferred. */
struct AudioPlayerTrack {
    unsigned int handle;
    signed char volume, cvolume, panning;
    unsigned char pos, effect, unknown09;
    short note, period, periodc;
    const struct AudioSample *sample;
    const struct AudioInstrument *instrument;
    unsigned char leffect, effectop;
    short portainc, portadest, glissnote;
    unsigned char vibrpos, vibrspeed, vibrdepth, vibrretrig;
    const short *vibrtable;
    unsigned char trempos, tremspeed, tremdepth, tremretrig;
    const short *tremtable;
    unsigned char panbpos, panbspeed, panbdepth, panbretrig;
    /* +34 is a waveform pointer in player tracks and a handle in six SFX tracks. */
    union { const short *panbtable; unsigned int instrument_id; };
    unsigned char glissando, trmcnt, trmon, trmtot;
    unsigned char volslide, volslide_fine, cvolslide, volslidefine;
    unsigned char panslide, panslidefine, arpeggio, arpeggiocnt;
    unsigned char porta, porta_fine, porta_efine, retrig;
    unsigned char resetnote, playnote, touched, envelope_enabled;
    unsigned char i_vol_status;
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
    unsigned short tempo;
    unsigned char speed, tick;
    unsigned char row, order, unknown12[2];
    const unsigned char *stream;
    signed char pending_order, pending_row, loop_order, loop_count, loop_active;
    signed char volume;
    unsigned char volume_slide, vibrato_offset;
    unsigned char instrument_based;
    unsigned char fast_volume_slides, unknown22[2];
    unsigned short (*calc_period)(unsigned int, const void *);
    unsigned int (*calc_final_frequency)(unsigned int);
    int restart_order;
    const struct AudioPattern *pattern;
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
