#ifndef LINK_ENTRY_RECEIVE_H
#define LINK_ENTRY_RECEIVE_H
#include "link_event_receive.h"
#include "display_text_fields.h"
#include "display_text_draw.h"
#include "display_text_raster.h"
#include "display_catalog_presentation.h"
#include "audio_game.h"
#include "resource_condition_entries.h"
#include "display_scene_entry_cleanup.h"

#include "scene_link_offer_state.h"

/* Alternate access view of the existing game state, not a complete allocation. */
struct LinkEntryGameState {
    unsigned int unknown00;
    int amount;
    unsigned char unknown08[0xe8];
    struct ConditionActorEntries *entries;
};
extern struct LinkEntryGameState g_link_entry_game_state;
unsigned int actor_entry_add(struct ConditionActorEntries *, unsigned int,
                            unsigned char, unsigned char);
#endif
