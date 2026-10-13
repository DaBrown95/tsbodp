#ifndef FRAME_ACTOR_PALETTE_MENU_H
#define FRAME_ACTOR_PALETTE_MENU_H

#include "frame_actor_palette_scene.h"

/* Access view of the existing game-state prefix; no complete record size. */
struct FrameActorPaletteMenuState {
    unsigned char unknown_00[16], text[16], selectors[8];
};
extern struct FrameActorPaletteMenuState g_frame_actor_palette_menu_state;
extern unsigned int g_frame_actor_palette_menu_choices[];
extern struct FrameObject *g_frame_actor_palette_menu_objects[];
extern const struct FrameActorPaletteScenePoint g_frame_actor_palette_menu_position;
extern const unsigned short g_frame_actor_palette_menu_extra_palette[];
extern const unsigned int g_frame_actor_palette_menu_background;

struct FrameObject *frame_create_scene_object(unsigned int, unsigned int,
                                             unsigned int, unsigned int);
void display_text_copy_field_zero(const char *);
void display_text_select_font(unsigned int, int, int);
const char *display_scene_lookup_text(unsigned int);
struct FrameObject *display_scene_create_label(unsigned int, const char **);
void display_text_set_background_control(unsigned int);
void display_text_update(struct FrameObject *, const char **);
void display_text_set_object_string(struct FrameObject *, const char *);

void frame_create_palette_menu_actors(void);
void frame_update_palette_menu_actor(void);

#endif
