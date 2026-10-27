#ifndef DISPLAY_MENU_SECONDARY_H
#define DISPLAY_MENU_SECONDARY_H
#include "display_menu_results.h"
#include "display_menu_choice.h"
#include "display_menu_relation_resource.h"
#include "display_menu_effects.h"
#include "save_world_display.h"
#include "display_text_fields.h"
#include "display_condition_panel_details.h"
#include "scene_link_menu.h"

/* Observed role prefixes of shared linker storage, not complete object or
 * table bounds. World and relation-owner views overlap at world+16; external
 * provider calls delimit their use. Their historical C ownership is provisional. */
struct DisplayMenuSecondaryDescriptor {
    const unsigned short *text_ids;
    const struct BackgroundResource *resources[7];
    const unsigned int *cues;
    unsigned char multiplier, cue_variant, unknown26, allowed_count;
    const unsigned int *allowed;
};
struct DisplayMenuSecondaryWorld {
    unsigned char unknown00[8];
    struct DisplayTimeRecord clock;
    struct DisplayMenuRelationState relation;
    unsigned char unknown98[0xdc - 0x98];
    unsigned int once_mask;
    unsigned char unknowne0[16];
    struct ConditionActorEntries *secondary_entries;
    unsigned char unknownf4[0x418 - 0xf4];
    struct DisplayMenuSelectionState selection;
    unsigned char unknown424[0x440 - 0x424];
    unsigned int reward;
};
extern struct DisplayMenuSecondaryDescriptor g_menu_secondary_descriptors[];
extern struct DisplayMenuSecondaryWorld g_menu_secondary_world;
/* The native later phases retain this owner at world+16. Its selected
 * definition aliases selection.definition at world+0x419. */
struct DisplayMenuSecondaryRelationOwner {
    struct DisplayMenuRelationState state;
    unsigned char unknown88[0x409 - 0x88];
    unsigned char selected_definition;
    unsigned char unknown40a[0x430 - 0x40a];
    unsigned int reward;
};
extern struct DisplayMenuSecondaryRelationOwner g_menu_secondary_relation_owner;
extern const unsigned char g_menu_secondary_reward_multipliers[];
#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char greeting_stride[sizeof(struct DisplayMenuSecondaryDescriptor)==44?1:-1];
typedef char world_relation[OFF(struct DisplayMenuSecondaryWorld,relation)==16?1:-1];
typedef char world_once[OFF(struct DisplayMenuSecondaryWorld,once_mask)==0xdc?1:-1];
typedef char world_entries[OFF(struct DisplayMenuSecondaryWorld,secondary_entries)==0xf0?1:-1];
typedef char world_selection[OFF(struct DisplayMenuSecondaryWorld,selection)==0x418?1:-1];
typedef char world_reward[OFF(struct DisplayMenuSecondaryWorld,reward)==0x440?1:-1];
typedef char secondary_descriptor_fields[(OFF(struct DisplayMenuSecondaryDescriptor,multiplier)==36&&OFF(struct DisplayMenuSecondaryDescriptor,allowed_count)==39&&OFF(struct DisplayMenuSecondaryDescriptor,allowed)==40)?1:-1];
typedef char secondary_relation_fields[(OFF(struct DisplayMenuSecondaryRelationOwner,selected_definition)==0x409&&OFF(struct DisplayMenuSecondaryRelationOwner,reward)==0x430)?1:-1];
#undef OFF
#endif
