#ifndef DISPLAY_MENU_RESULTS_H
#define DISPLAY_MENU_RESULTS_H
#include "display_menu_pages.h"
#include "display_menu_relation_events.h"
#include "frame_random.h"
#include "audio_game.h"

/* Partial access views. Strides and field offsets do not establish table bounds.
 * Row byte arrays express an address stride; slot offsets can exceed that stride. */
struct DisplayMenuResultObserver { unsigned char unknown_00[0x20], variant; };
struct DisplayMenuResult { signed char delta, text; } __attribute__((packed));
struct DisplayMenuSecondaryResultRow { unsigned char bytes[30]; } __attribute__((packed));
struct DisplayMenuPrimaryResultRow { unsigned char bytes[10]; } __attribute__((packed));
struct DisplayMenuResultDescriptor {
    const unsigned short *text_ids;
    const struct BackgroundResource *resources[7];
    const unsigned int *cues;
    unsigned char unknown_24[8];
};
struct DisplayMenuChoiceResultRecord {
    unsigned short unknown_00, text;
    unsigned char unknown_04[16];
    unsigned int flags;
};
struct DisplayMenuResultGame {
    unsigned char unknown_00[0x440];
    unsigned int text_variant;
};
extern struct DisplayMenuResultObserver g_display_menu_result_observer;
extern struct DisplayMenuRelationState g_display_menu_relation_state;
extern const struct DisplayMenuSecondaryResultRow g_display_menu_secondary_result_rows[];
extern const struct DisplayMenuPrimaryResultRow g_display_menu_primary_result_rows[];
extern const struct DisplayMenuPrimaryResultRow g_display_menu_primary_special_rows[];
extern const unsigned char g_display_menu_primary_chance_offsets[];
extern const struct DisplayMenuResultDescriptor g_display_menu_result_descriptors[];
extern struct DisplayMenuActorSelection g_display_menu_result_actor_selection;
extern struct FrameActorNeedState g_display_menu_result_local_needs;
extern const struct DisplayTimeRecord g_display_menu_result_time_delta;
extern struct DisplayMenuResultGame g_display_menu_result_game;

void display_menu_apply_primary_result(void), display_menu_apply_secondary_result(void);
/* Callee entry consumes the complete selector and narrows only the success byte. */
void display_menu_draw_primary_result(int, unsigned char);
void display_menu_draw_secondary_result(int), display_menu_draw_choice_result(void);
void display_menu_stage_result_text(const char *), display_menu_reset_result_text(void);
void display_menu_execute_row(void);
void display_menu_step_result_effects(void);
/* Accepted needs updater; the local storage is a partial role view. */
void frame_adjust_actor_needs(struct FrameActorNeedState *, unsigned int, unsigned char);
void display_text_set_line_height(int);
/* This caller observes a narrowed halfword from the unconverted bounded RNG. */
unsigned short frame_random_bounded(unsigned short);

static inline const struct BackgroundResource *display_menu_result_resource(
    const struct DisplayMenuResultDescriptor *definitions, unsigned int index,
    int offset)
{
    unsigned int bytes = offset + index * sizeof(*definitions);
    const unsigned char *column = (const unsigned char *)definitions + 4;
    return *(const struct BackgroundResource *const *)(bytes + (unsigned int)column);
}
static inline const struct BackgroundResource *display_menu_result_resource_column(
    const struct DisplayMenuResultDescriptor *definitions, unsigned int index,
    int offset)
{
    unsigned int bytes = index * sizeof(*definitions);
    const unsigned char *column = (const unsigned char *)definitions + offset;
    return *(const struct BackgroundResource *const *)(bytes + (unsigned int)column);
}
static inline const unsigned int *display_menu_result_cues(
    const struct DisplayMenuResultDescriptor *definitions, unsigned int index)
{
    unsigned int bytes = index * sizeof(*definitions);
    const unsigned char *column = (const unsigned char *)definitions + 0x20;
    return *(const unsigned int *const *)((unsigned int)column + bytes);
}
#endif
