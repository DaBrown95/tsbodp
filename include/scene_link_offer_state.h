#ifndef SCENE_LINK_OFFER_STATE_H
#define SCENE_LINK_OFFER_STATE_H
/* Access view of four observed 24-byte records. Incoming index bounds and all
 * writer populations remain separate from these callback reconstructions. */
struct SceneLinkEffectOffer {
    unsigned int kind;
    int limit;
    unsigned char unknown08[4];
    int cost;
    unsigned short countdown, phase;
    unsigned char count, unknown15[3];
};
struct SceneLinkEffectState {
    struct SceneLinkEffectOffer records[4];
    int multiplier;
    signed char selected;
};
extern struct SceneLinkEffectState g_link_entry_effect_state;
#endif
