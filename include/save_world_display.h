#ifndef SAVE_WORLD_DISPLAY_H
#define SAVE_WORLD_DISPLAY_H
#include "save_world_initialization.h"

struct BackgroundResource;
struct PaletteRangeConfig;
struct FrameVariantResource;
struct DisplayStoredMap;
/* ROM coordinates have a two-byte stride. The incoming byte index is unchecked. */
struct SaveWorldIndicatorCoordinate {
    unsigned char x, y;
} __attribute__((packed));
extern const struct BackgroundResource g_save_world_row_palette_a;
extern const struct BackgroundResource g_save_world_row_palette_b;
extern const struct PaletteRangeConfig g_save_world_row_palette_ranges;
extern const struct SaveWorldIndicatorCoordinate g_save_world_indicator_coordinates[];
extern struct FrameVariantResource g_save_world_indicator_animation;

extern const struct DisplayStoredMap *g_save_world_gauge_map;
extern const unsigned short *g_save_world_transition_map;
extern unsigned char g_frame_actor_local_need_state[];

void save_world_refresh_row_palette(unsigned int);
void save_world_update_row_gauges(void);
void save_world_finish_transition(unsigned int, unsigned char);
/* Allocation and slot validity are caller preconditions in the observed body. */
void save_world_create_row_indicator(struct SaveWorldTransitionRow *, unsigned char);
int save_world_scale_gauge(short, unsigned short, unsigned char);
/* Products retain all 32 bits before the signed original division call. */
int save_world_scale_percent(int, int);
int save_world_ratio_percent(int, int);

unsigned int display_load_resource_palette(const struct BackgroundResource *, unsigned short);
void display_load_palette_ranges(const struct PaletteRangeConfig *);
unsigned char frame_actor_need_value(struct FrameActorNeedState *, unsigned int);
void display_copy_background_rectangle(unsigned int, const struct DisplayStoredMap *,
    int, int, int, int, int, int, unsigned short);
/* Explicit original division provider; no new runtime edge-case claim. */
int display_bios_div(int, int);
#endif
