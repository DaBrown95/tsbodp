#ifndef DISPLAY_MENU_PRIMARY_H
#define DISPLAY_MENU_PRIMARY_H
#include "display_menu_scene.h"

struct FrameObject;
struct FrameActorNeedState;
struct DisplayStoredMap;
/* Partial scene object slots from the observed flag accesses. */
struct DisplayMenuObjects {
    unsigned int unknown_00[2];
    struct FrameObject *hint;
    unsigned int unknown_0c;
    struct FrameObject *scroll;
    struct FrameObject *first, *second;
};
extern struct DisplayMenuObjects g_display_menu_objects;
extern void *g_display_menu_notice_owner;
extern const unsigned char g_display_menu_indicator_choices[];
extern const unsigned char g_display_menu_need_parameters[];
extern unsigned char g_frame_actor_local_need_state[];
void display_menu_populate_primary_rows(void);
void display_copy_background_rectangle(unsigned int, const struct DisplayStoredMap *,
    int, int, int, int, int, int, unsigned short);
/* Unconverted dependencies; widths and pointer roles follow these callers. */
void display_menu_restore_choice(void);
void display_menu_show_hint(unsigned char);
void display_menu_request_notice(unsigned int, unsigned int, void *);
unsigned int frame_actor_indicator_kind(unsigned char);
unsigned int display_menu_fallback_indicator(unsigned char);
unsigned char display_menu_primary_row_code(unsigned int);
unsigned int display_menu_primary_row_parameter(unsigned int);
unsigned int frame_low_need_mask(struct FrameActorNeedState *, unsigned int);

#endif
