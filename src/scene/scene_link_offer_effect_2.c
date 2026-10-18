#include "scene_link_offer_effects.h"
void scene_link_offer_effect_2(unsigned char slot, int difference)
{
    int change = 0;
    struct SceneLinkEffectOffer *offer = &g_link_entry_effect_state.records[slot];
    switch (offer->phase) {
    case 0:
        offer->phase = 1;
        offer->countdown = frame_random_range(5, 15);
    case 1:
        if (offer->count * g_link_entry_effect_state.multiplier < offer->limit)
            change = 1;
        else if (g_link_entry_effect_state.selected == slot) {
            offer->countdown = frame_random_range(5, 30);
            offer->phase = 3;
            break;
        }
        if ((offer->count + change) * g_link_entry_effect_state.multiplier <= offer->limit && change) {
            offer->count += change;
            audio_play_animation_cue(15);
        }
        {
            unsigned short previous = offer->countdown--;
            if (previous == 0) {
                offer->countdown = frame_random_range(5, 15);
                offer->phase = 2;
            }
        }
        break;
    case 3:
        {
            unsigned short previous = offer->countdown--;
            if (previous == 0 || offer->count == 0) {
                offer->countdown = frame_random_range(5, 15);
                offer->phase = 1;
            } else if (offer->count * g_link_entry_effect_state.multiplier > 0)
                --offer->count;
        }
        break;
    case 2:
        {
            unsigned short previous = offer->countdown--;
            if (previous == 0) {
                offer->countdown = frame_random_range(5, 15);
                offer->phase = 1;
            }
        }
        break;
    }
}
asm(".align 2,0");
