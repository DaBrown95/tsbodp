#include "scene_link_offer_effects.h"
void scene_link_offer_effect_0(unsigned char slot, unsigned char difference)
{
    int change = 0;
    struct SceneLinkEffectOffer *offer = &g_link_entry_effect_state.records[slot];
    switch (offer->phase) {
    case 0:
        offer->phase = 1;
    case 1:
        if (offer->count * g_link_entry_effect_state.multiplier < offer->limit &&
            (g_link_entry_effect_state.selected != slot || (signed char)difference <= 4))
            change = 1;
        if ((offer->count + change) * g_link_entry_effect_state.multiplier <= offer->limit && change) {
            offer->count += change;
            audio_play_animation_cue(15);
        }
        break;
    case 2:
        offer->phase = 1;
        break;
    }
}
asm(".align 2,0");
