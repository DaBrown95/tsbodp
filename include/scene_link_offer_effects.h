#ifndef SCENE_LINK_OFFER_EFFECTS_PRIVATE_H
#define SCENE_LINK_OFFER_EFFECTS_PRIVATE_H
#include "audio_game.h"
#include "display_time.h"
#include "frame_random.h"
#include "scene_link_offer_state.h"
extern const struct DisplayTimeRecord g_resource_selector_clock;
extern const struct DisplayTimeRecord g_scene_link_effect_clock;
extern struct DisplayTimeRecord g_display_countdown;
/* The observed dispatcher passes a byte slot and a sign-extended byte as a
 * full word. Consuming callbacks explicitly retain that word's low byte.
 * Seven ROM targets are observed; complete table capacity remains unknown. */
typedef void (*SceneLinkOfferEffectCallback)(unsigned char, int);
extern SceneLinkOfferEffectCallback const g_link_offer_adjustments[];
void scene_link_offer_effect_0(unsigned char, int);
void scene_link_offer_effect_1(unsigned char, int);
void scene_link_offer_effect_2(unsigned char, int);
void scene_link_offer_effect_3(unsigned char, int);
void scene_link_offer_effect_4(unsigned char, int);
void scene_link_offer_effect_5(unsigned char, int);
void scene_link_offer_effect_6(unsigned char, int);
#endif
