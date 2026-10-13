#ifndef FRAME_OPTIONAL_CHOICE_LIST_H
#define FRAME_OPTIONAL_CHOICE_LIST_H

#include "frame_need_effect_optional_choice.h"
#include "display_menu_relation_events.h"
#include "resource_conditions.h"

/* One-byte compiler view for the observed read/OR-255/store initialization.
 * The writer visits 24 entries; the allocation and wider capacity are unknown. */
struct FrameOptionalChoiceValue {
    unsigned char value:8;
} __attribute__((packed));
extern struct FrameOptionalChoiceValue g_optional_choice_values[];

/* Partial global overlay. Clock +8, stage +0x440 and selected actor +0x740
 * coincide with existing scene views; this helper establishes no ownership. */
struct FrameOptionalChoiceWorldState {
    unsigned char unknown_00[8];
    struct DisplayTimeRecord clock;
    unsigned char unknown_10[0x440 - 16];
    unsigned int stage;
    unsigned char unknown_444[0x740 - 0x444];
    unsigned char actor;
};
extern struct FrameOptionalChoiceWorldState g_optional_choice_world;
extern const unsigned char g_optional_choice_stage_values[];
extern const unsigned char *g_frame_scene_actor_world_tables[];

unsigned char frame_optional_choice_classify(unsigned int, unsigned int *,
                                             unsigned char *, unsigned char *);
unsigned char frame_optional_choice_build_available(void);

/* Connected page builder; arbitrary page values and wider capacity are unknown. */
unsigned char frame_optional_choice_build_page(void);

#endif
