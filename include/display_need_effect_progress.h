#ifndef DISPLAY_NEED_EFFECT_PROGRESS_H
#define DISPLAY_NEED_EFFECT_PROGRESS_H
#include "display_need_effect_update.h"
#include "view_math.h"
#include "frame_random.h"

/* The final word of each 28-byte program row is consumed here as four bytes. */
struct DisplayNeedEffectProgramView {
    unsigned char *commands[6];
    unsigned char effect_1, effect_2, effect_3, effect_4;
};
struct DisplayNeedEffectTickCallbacks {
    unsigned char unknown_00[0xf8];
    void (*tick)(struct FrameNeedEffectState *);
};
struct DisplayNeedEffectProgressObject {
    unsigned char unknown_00[0x58];
    unsigned int count;
};
struct FrameMapRegistration;
extern unsigned char *g_need_effect_action_sets[];
unsigned char frame_need_effect_action_available(struct FrameNeedEffectState *,
                                               unsigned int);
extern unsigned char g_frame_actor_social_probe[];
/* Only this storage's first word is interpreted as an object pointer here. */
extern struct FrameObject *g_need_effect_player;
struct FrameObject *frame_create_actor_effect(struct FrameObject *, unsigned char,
                                            unsigned int, unsigned char);
unsigned char frame_find_objects(unsigned char, unsigned char, struct FrameObject **,
                                unsigned char);
unsigned int frame_need_effect_advance_optional(struct FrameNeedEffectState *);
int frame_read_signed_parameter(const void *, unsigned int);
void frame_need_effect_read_center(struct FrameObject *, struct FramePoint *);
unsigned char frame_configure_need_effect(struct FrameObject *, int, int, int);
void frame_remove_object(struct FrameObject *);
unsigned char frame_grid_coordinates_to_point(struct FrameMapRegistration *,
                                             const struct FramePoint *,
                                             struct FramePoint *);
#endif
