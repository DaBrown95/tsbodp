#ifndef SAVE_WORLD_VIEW_INITIALIZATION_H
#define SAVE_WORLD_VIEW_INITIALIZATION_H
#include "save_world_display.h"
#include "scene_primary.h"
#include "display_text_raster.h"

/* Descriptor letters identify their load order, not recovered asset names. */
extern const struct BackgroundResource g_save_world_view_background_a;
extern const struct BackgroundResource g_save_world_view_background_c;
extern const struct BackgroundResource g_save_world_view_background_d;
extern const struct BackgroundResource g_save_world_view_background_e;
extern const unsigned short *g_save_world_summary_map;
extern const unsigned int g_scene_background_control0;

/* The existing word API is retained; the body consumes mode's low byte. */
void scene_initialize_view(unsigned int, unsigned int);
void display_fill_background(unsigned int, unsigned short);
void display_fill_background_rectangle(unsigned int, int, int, int, int,
    unsigned short);
void display_fill_background_constant_rectangle(unsigned int, int, int, int, int,
    unsigned short);
const unsigned short *display_load_background_resource_dma(unsigned int,
    const struct BackgroundResource *, unsigned short);
const unsigned short *display_load_background_dma(unsigned int,
    const struct BackgroundResource *, unsigned short, unsigned short,
    unsigned int, unsigned int);

/* Original providers remain unconverted. These argument widths follow only
 * this caller; the child at world +20 has no complete contract here. */
void scene_view_original_3aff0(unsigned int, unsigned int, unsigned int,
    unsigned int, unsigned int, void *);
void scene_view_original_34630(unsigned int, unsigned int, unsigned int);
#endif
