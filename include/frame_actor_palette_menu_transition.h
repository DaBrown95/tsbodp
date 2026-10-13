#ifndef FRAME_ACTOR_PALETTE_MENU_TRANSITION_H
#define FRAME_ACTOR_PALETTE_MENU_TRANSITION_H

#include "frame_actor_palette_menu.h"
#include "scene_request.h"
#include "display_window_motion.h"

/* Separate access views of pointer slots and adjacent count/control bytes. */
extern unsigned char g_frame_actor_palette_menu_exit_count;
extern unsigned char g_frame_actor_palette_menu_text_flag;
extern struct FrameObject *g_frame_actor_palette_menu_exit_objects[];
extern const struct BackgroundResource g_frame_actor_palette_menu_background2;
extern const struct BackgroundResource g_frame_actor_palette_menu_background1;
extern const unsigned short g_frame_actor_palette_menu_entry_palette[];

void frame_scene_object_tick(struct FrameObject *);
void frame_begin_position_move(struct FrameObject *, int, int, unsigned short);
unsigned char frame_step_position_move(struct FrameObject *);
/* Unconverted menu/scene wrapper at the observed ROM entry. */
void display_scene_stage_08027dc0(unsigned int);
void frame_step_palette_menu_transition(void);

#endif
