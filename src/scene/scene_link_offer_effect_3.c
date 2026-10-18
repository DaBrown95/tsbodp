#include "scene_link_offer_effects.h"

void scene_link_offer_effect_3(unsigned char slot, int difference_word)
{
    unsigned char difference = (unsigned char)difference_word;
    /* Keep the one-use byte offset separate from the preserved record pointer. */
    register unsigned int record_offset asm("r0") =
        (unsigned int)slot * sizeof(struct SceneLinkEffectOffer);
    register struct SceneLinkEffectOffer *offer asm("r4") =
        (struct SceneLinkEffectOffer *)((unsigned char *)&g_link_entry_effect_state
                                      + record_offset);
    switch (offer->phase) {
    case 0:
        offer->phase = 1;
        offer->countdown = frame_random_range(5, 15);
    case 1: {
        /* The two bounds share this observation; the increment reads again. */
        int count_at_check = offer->count;
        register int limit_at_check asm("r2");
        if (count_at_check * g_link_entry_effect_state.multiplier < (limit_at_check = offer->limit) &&
            (g_link_entry_effect_state.selected != slot || (signed char)difference <= 4)) {
            if ((count_at_check + 1) * g_link_entry_effect_state.multiplier <= limit_at_check) {
                ++offer->count;
                audio_play_animation_cue(15);
            }
        } else {
            offer->countdown = frame_random_range(5, 15);
            offer->phase = 3;
            break;
        }
        {
            unsigned short previous = offer->countdown--;
            if (previous == 0) {
                offer->countdown = frame_random_range(5, 15);
                offer->phase = 2;
            }
        }
        break;
    }
    case 3: {
        /* The product and decrement share one count observation. */
        int count_at_decrement = offer->count;
        if (count_at_decrement * g_link_entry_effect_state.multiplier > 0)
            offer->count = count_at_decrement - 1;
        {
            unsigned short previous = offer->countdown--;
            if (previous == 0 || offer->count == 0) {
                offer->countdown = frame_random_range(5, 15);
                offer->phase = 1;
            }
        }
        break;
    }
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
