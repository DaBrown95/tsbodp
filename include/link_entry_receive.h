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

/* Four observed 24-byte offer records precede the multiplier at +0x60 and
 * signed selection at +0x64. The selected index is not range-checked here. */
struct LinkEntryOfferRecord {
    unsigned char unknown00[12];
    int cost;
    unsigned char unknown10[4], count, unknown15[3];
};
struct LinkEntryOfferState {
    struct LinkEntryOfferRecord records[4];
    int multiplier;
    signed char selected;
};
/* Alternate access view of the existing game state, not a complete allocation. */
struct LinkEntryGameState {
    unsigned int unknown00;
    int amount;
    unsigned char unknown08[0xe8];
    struct ConditionActorEntries *entries;
};
extern struct LinkEntryOfferState g_link_entry_offers;
extern struct LinkEntryGameState g_link_entry_game_state;
unsigned int actor_entry_add(struct ConditionActorEntries *, unsigned int,
                            unsigned char, unsigned char);
#endif
