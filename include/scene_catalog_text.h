#ifndef SCENE_CATALOG_TEXT_H
#define SCENE_CATALOG_TEXT_H
#include "scene_catalog.h"
#include "display_text_fields.h"
#include "display_map_fill.h"
#include "save_world_view_resources.h"
#include "scene_view_frame.h"

/* Overlapping word read at world +4; complete world storage is unknown. */
struct SceneCatalogHeadingWorld {unsigned int unknown00;int value;};
extern struct SceneCatalogHeadingWorld g_scene_catalog_heading_world;
#endif
