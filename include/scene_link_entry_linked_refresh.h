#ifndef SCENE_LINK_ENTRY_LINKED_REFRESH_H
#define SCENE_LINK_ENTRY_LINKED_REFRESH_H
#include "link_entry_receive.h"
#include "frame_command.h"
#include "display_catalog_text.h"
#include "display_time_hud.h"
#include "save_world_display.h"

/* Character representation of a four-byte-aligned catalog number column.
 * Each used address is array base +20 +scene*24, backed by the canonical array. */
typedef unsigned char SceneLinkCatalogColumnByteBase;
typedef SceneLinkCatalogColumnByteBase SceneLinkCatalogColumnByte
    __attribute__((aligned(4)));

/* Exact existing canonical pointer-slot declaration. Keeping it narrow avoids
 * importing the scene lifecycle umbrella's unguarded frame views again. */
extern struct FrameObject *g_display_scene_frame_objects[];
extern const unsigned int g_scene_link_entry_text_control;
extern const struct DisplayTimeRecord g_scene_link_offer_countdown;
void scene_link_entry_refresh_linked_offers(void);
#endif
