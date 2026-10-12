#ifndef AUDIO_GAME_H
#define AUDIO_GAME_H
#include "audio_vblank.h"
/* Partial options and descriptor views inferred from game audio callers. */
struct AudioGameOptions { unsigned char unknown[8], samples_enabled, sequences_enabled; };
extern struct AudioGameOptions g_audio_game_options;
struct AudioSequenceDescriptor {
 const void *sequence;
 union { volatile unsigned int word; unsigned char bytes[4]; } parameters;
};
extern struct AudioSequenceDescriptor g_audio_sequence_descriptors[];
extern volatile unsigned int g_audio_scene_word;
extern void audio_start_sequence(const void *, int, int);
extern void audio_sync_game_state(void);
void audio_select_sequence(unsigned char);
struct AudioCueDescriptor { unsigned short kind, sample_id; };
struct AudioSampleParameters { unsigned short sample_id, pitch; };
extern struct AudioCueDescriptor g_audio_cue_descriptors[];
extern struct AudioSampleParameters g_audio_sample_parameters[];
extern struct AudioSampleParameters g_audio_sample_variants[][8];
extern const void *g_audio_samples[];
extern unsigned int game_random_inclusive(unsigned short);
extern unsigned int audio_play_sample(const void *, int, int);
extern void audio_set_sample_pitch(unsigned int, int);
unsigned int audio_play_animation_cue(unsigned int);
#endif
