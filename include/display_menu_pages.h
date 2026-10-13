#ifndef DISPLAY_MENU_PAGES_H
#define DISPLAY_MENU_PAGES_H
#include "display_map_fill.h"
#include "display_menu_primary.h"
#include "display_scene_setup.h"
#include "display_catalog_text.h"
#include "frame_actor_relation.h"
#include "frame.h"

extern const struct BackgroundResource g_display_menu_hint_resource;
extern unsigned char g_display_menu_page_text_variants[];
extern struct FrameObject *g_need_effect_player;
/* Unconverted tile reader: this caller observes a 16-bit return. */
unsigned short display_read_map_tile(const unsigned short *, int, int, int);
void display_load_background_dma(unsigned int, const struct BackgroundResource *,
    unsigned short, unsigned short, unsigned int, unsigned int);
struct TransitionObject;
void transition_object_set_state(struct TransitionObject *, unsigned char);
void frame_set_variant_state(struct FrameObject *, unsigned char);
void display_menu_draw_scrolling_text(const char *);
/* Partial role view of the observed actor-selection byte. */
struct DisplayMenuActorSelection {
    unsigned char unknown_00[0x740], actor;
};
/* This unconverted consumer narrows the requested delta to a signed byte. */
void display_menu_apply_delta(signed char);
void display_menu_prepare_state_42(void);
/* Observed twelve-byte view; surrounding storage and complete bounds are unknown. */
struct DisplayMenuSelectionState {
    unsigned char enabled, definition, text_kind, unknown_03;
    short major;
    signed char minor, part;
    signed char second, tick;
    unsigned short reserved;
};
extern struct DisplayMenuSelectionState g_display_menu_selection_state;
extern unsigned char g_frame_actor_social_probe[];
int frame_read_signed_parameter(const void *, unsigned int);
/* Caller observes a byte return; output points into shared game-state storage. */
unsigned char display_menu_prepare_choice(void *, unsigned char, void *);
void display_menu_prepare_choice_text(void);
#endif
