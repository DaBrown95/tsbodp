#ifndef SAVE_WORLD_VIEW_UPDATE_H
#define SAVE_WORLD_VIEW_UPDATE_H

#include "save_world_display.h"
#include "frame_actor_scene.h"
#include "save_world_pending_notices.h"
#include "scene_primary.h"
#include "display_map_fill.h"
#include "display_text_fields.h"
#include "display_text_raster.h"
#include "display_time_format.h"
#include "audio_game.h"

/* The gauge selects an original descriptor pointer; its full table bound is unknown. */
struct BackgroundResource;
extern const struct BackgroundResource *g_save_world_need_resources[];
extern const unsigned short *g_save_world_summary_map;
const unsigned short *display_load_background_resource_dma(unsigned int,
    const struct BackgroundResource *, unsigned short);

void save_world_show_row_notice(unsigned int);
void save_world_show_row_flag_notice(unsigned int);
void save_world_show_notice(unsigned int);
unsigned char frame_actor_need_average(struct FrameActorNeedState *);

/* The existing incoming word index remains unchecked in this coordinator. */
void scene_update_view(unsigned int);

#endif
