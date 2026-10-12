#ifndef AUDIO_VBLANK_H
#define AUDIO_VBLANK_H
/* Partial control layout shared by VBlank and scene/audio coordination. */
struct AudioVBlankControl {
 unsigned char unknown[4];
 unsigned char pacing;
 unsigned char sequence_id;
 volatile unsigned char flags : 8;
};
extern struct AudioVBlankControl g_audio_control;
#endif
