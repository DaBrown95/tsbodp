#ifndef AUDIO_GAME_ACTIVITY_H
#define AUDIO_GAME_ACTIVITY_H
/* Compatible with the accepted SDK callback/volume interfaces. */
void audio_player_set_callback(void (*)(int,int));
void audio_player_set_channel_volume(unsigned int,unsigned int);
unsigned int audio_player_get_channel_volume(unsigned int);
/* Aligned access view at the same storage as the VBlank control.
 * Only the parameter word and existing bytes4..6 are interpreted here. */
struct AudioGameActivityNotice {unsigned int parameter;unsigned char pacing,sequence;volatile unsigned char flags:8;};
extern struct AudioGameActivityNotice g_audio_game_activity_notice;
extern void (*const g_audio_game_activity_callbacks[])(int,int);
#endif
