#ifndef DISPLAY_SCENE_NAVIGATION_H
#define DISPLAY_SCENE_NAVIGATION_H
#include "display_scene_setup.h"
extern struct DisplaySceneOwner *g_display_scene_objects[];
extern unsigned int audio_play_animation_cue(unsigned int);
extern void display_scene_update_page_controls(void);
extern unsigned char display_scene_previous_group(void), display_scene_next_group(void);
#endif
