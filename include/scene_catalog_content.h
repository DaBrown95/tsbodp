#ifndef SCENE_CATALOG_CONTENT_H
#define SCENE_CATALOG_CONTENT_H
#include "scene_catalog.h"
#include "display_catalog_text.h"
/* Overlapping access views; observed prefixes do not establish complete capacity. */
struct __attribute__((packed,aligned(1))) SceneCatalogSlot {unsigned char kind,unknown01[3];};
struct SceneCatalogRecord {unsigned char count,unknown01[3];struct SceneCatalogSlot *slots;};
struct SceneCatalogPage {unsigned char value,unknown01[3];struct SceneCatalogSlot *slots;};
struct SceneCatalogContext {struct SceneCatalogRecord *record;unsigned int unknown04;struct SceneCatalogPage pages[14];};
struct SceneCatalogContentWorld {unsigned char unknown00[0xe0];unsigned char quantities[9],values[7];struct SceneCatalogRecord *catalog;unsigned int unknownf4;struct SceneCatalogPage pages[14];};
struct __attribute__((packed,aligned(1))) SceneCatalogCaptionPosition {unsigned char x,y,unknown02[2];};
struct SceneCatalogValueRate {unsigned int basic,page;};
extern struct SceneCatalogContentWorld g_scene_catalog_content;
extern const struct SceneCatalogCaptionPosition g_scene_catalog_caption_positions[5];
extern const char g_scene_catalog_caption_suffix[];
extern unsigned char g_scene_catalog_quantities[9];
/* Word products wrap before the logical shift by sixteen. */
extern const struct SceneCatalogValueRate g_scene_catalog_value_rates[14];
unsigned int scene_catalog_basic_value(unsigned int);
unsigned int scene_catalog_page_value(unsigned int);
unsigned char scene_catalog_has_next(unsigned char,unsigned char);
void scene_catalog_fill(unsigned int,unsigned int);
#endif
