#ifndef DISPLAY_SCENE_SELECTOR_H
#define DISPLAY_SCENE_SELECTOR_H
#include "display_scene_setup.h"
#include "input.h"
struct FrameObject;
extern void frame_set_variant_state(struct FrameObject *, unsigned char);
extern unsigned int audio_play_animation_cue(unsigned int);
extern void transition_run_first(unsigned short, unsigned int);
extern unsigned int g_resource_scene_arg;
extern void display_scene_stage_08027dc0(unsigned int);
extern unsigned char display_scene_previous_group(void), display_scene_next_group(void);
extern void display_scene_stage_0800f29c(unsigned int);
extern void display_update_scrolling_scene(void);
#endif
