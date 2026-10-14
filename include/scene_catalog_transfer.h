#ifndef SCENE_CATALOG_TRANSFER_H
#define SCENE_CATALOG_TRANSFER_H
#include "scene_catalog_content.h"
#include "resource_condition_entries.h"
#include "display_menu_relation.h"
/* Overlapping partial world view. Observed list prefix 0..13 and byte +43E;
 * complete allocation and pointer validity remain unknown. */
struct SceneCatalogTransferWorld {unsigned char unknown00[0xf0];struct ConditionActorEntries *record;unsigned int unknownf4;struct ConditionActorEntries lists[14];unsigned char unknown168[0x43e - 0x168],available;};
extern struct SceneCatalogTransferWorld g_scene_catalog_transfer_world;
unsigned int actor_entry_add(struct ConditionActorEntries *,unsigned int,unsigned char,unsigned char);
void scene_catalog_option(void),scene_catalog_notice(unsigned int);
#endif
