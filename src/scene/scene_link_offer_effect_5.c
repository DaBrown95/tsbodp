#include "scene_link_offer_effects.h"

void scene_link_offer_effect_5(unsigned char slot, int difference)
{
    /* Keep the one-use byte offset separate from the preserved record pointer. */
    register unsigned int record_offset asm("r1") =
        (unsigned int)slot * sizeof(struct SceneLinkEffectOffer);
    register struct SceneLinkEffectOffer *offer asm("r4") =
        (struct SceneLinkEffectOffer *)((unsigned char *)&g_link_entry_effect_state
                                      + record_offset);
    switch (offer->phase) {
    case 0:
        offer->phase = 1;
    case 1:
        if (offer->count * g_link_entry_effect_state.multiplier < offer->limit &&
            frame_random_range(1, 100) <= 84) {
            if ((offer->count + 2) * g_link_entry_effect_state.multiplier <= offer->limit) {
                offer->count += 2;
                audio_play_animation_cue(15);
            }
        } else {
            offer->countdown = frame_random_range(5, 15);
            offer->phase = 3;
        }
        break;
    case 3:
        {
            unsigned short previous = offer->countdown--;
            if (previous == 0 || offer->count == 0) {
                offer->countdown = frame_random_range(5, 15);
                offer->phase = 1;
            } else {
                /* The product and decrement share one count observation. */
                int count_at_decrement = offer->count;
                if (count_at_decrement * g_link_entry_effect_state.multiplier > 0)
                    offer->count = count_at_decrement - 1;
            }
        }
        break;
    }
}
asm(".align 2,0");
