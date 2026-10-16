#ifndef FRAME_NEED_EFFECT_DEPARTURE_H
#define FRAME_NEED_EFFECT_DEPARTURE_H
#include "frame_actor_runtime.h"
#include "audio_game.h"
#include "scene_request.h"
#include "display.h"
#include "input.h"
#include "scene_request_queue.h"

/* Partial object view for the kind-27 scene reached from the special effect. */
struct FrameNeedEffectDepartureObject {
    struct FrameObject *next, *previous;
    FrameU16 id, subtype;
    FrameU32 flags;
    FrameU8 unknown_10[8];
    struct FramePoint position, next_position, velocity, acceleration, destination;
    FrameU8 unknown_40[13], state, unknown_4e[10];
    int countdown;
    FrameU8 unknown_5c[44];
    void (*on_step)(struct FrameObject *);
    FrameU8 unknown_8c[12];
    void (*before_step)(struct FrameObject *);
    FrameU8 unknown_9c[52];
    struct FrameOam oam;
};
struct FrameNeedEffectDepartureGame {
    FrameU8 unknown_00[0x20], appearance;
};
union ResourceGameState;
extern union ResourceGameState g_resource_game_state;
extern unsigned int g_need_effect_departure_cue;
extern struct FrameVariantResource g_need_effect_departure_animation_first;
extern struct FrameVariantResource g_need_effect_departure_animation_second;
extern struct FrameVariantResource g_need_effect_departure_animation_third;
unsigned char frame_object_has_flags(struct FrameObject *, unsigned int);
struct FrameObject *frame_create_need_effect_departure(void);
void frame_need_effect_departure_tick(struct FrameObject *);
extern const unsigned int g_need_effect_departure_control3;
extern const unsigned int g_need_effect_departure_control2;
extern const struct BackgroundResource g_need_effect_departure_background3;
extern const struct BackgroundResource g_need_effect_departure_background2;
extern const struct PaletteRangeConfig g_need_effect_departure_palette_ranges;
extern const void *const g_need_effect_departure_palette_slot[];
void display_set_mode(unsigned short);
void display_configure_tile_allocation(unsigned char);
void display_show_background(unsigned int, unsigned int);
const unsigned short *display_load_background(unsigned int,
    const struct BackgroundResource *, unsigned short, unsigned short,
    unsigned int, unsigned int);
void frame_define_palette_slot(unsigned int, const void *const *);
void transition_run_first(unsigned short, unsigned int);
void scene_need_effect_departure_initialize(void);
void scene_need_effect_departure_step(void);
void scene_need_effect_departure_end(void);
void display_release_object_list(struct FrameObjectList *);
void transition_run_second(unsigned short, unsigned int);
void display_reset(void);
#endif
