#include "scene_link_offer_effects.h"
void scene_link_offer_effect_4(unsigned char slot, int difference_word)
{
    unsigned char difference = (unsigned char)difference_word;
    int change = 0;
    struct SceneLinkEffectOffer *offer = &g_link_entry_effect_state.records[slot];
    switch (offer->phase) {
    case 0:
        offer->phase = 1;
    case 1:
        if (offer->count * g_link_entry_effect_state.multiplier < offer->limit &&
            (g_link_entry_effect_state.selected != slot || (signed char)difference <= 4))
            change = 1;
        else if (g_link_entry_effect_state.selected != slot) {
            offer->countdown = frame_random_range(5, 15);
            offer->phase = 3;
            break;
        }
        if ((offer->count + change) * g_link_entry_effect_state.multiplier <= offer->limit && change) {
            offer->count += change;
            audio_play_animation_cue(15);
        }
        break;
    case 3:
        {
            unsigned short previous = offer->countdown--;
            if (previous == 0 || g_link_entry_effect_state.selected == slot || offer->count == 0) {
                offer->countdown = frame_random_range(5, 15);
                offer->phase = 1;
            } else if (offer->count * g_link_entry_effect_state.multiplier > 0)
                --offer->count;
        }
        break;
    }
}
asm(".align 2,0");
