#ifndef DISPLAY_NEED_EFFECT_UPDATE_H
#define DISPLAY_NEED_EFFECT_UPDATE_H
#include "display_need_effect_lifecycle.h"

struct FrameTickObject;
struct FrameCommandObject;
struct ConditionActorEntries;
/* Role-specific access views; wider storage and choice-index bounds are unknown. */
struct DisplayNeedEffectChoiceState {
    unsigned char unknown_00[12];
    int index;
};
struct DisplayNeedEffectActorView {
    unsigned char unknown_00[0x4e], variant, unknown_4f[9];
    int timer;
    unsigned char unknown_5c[8];
    struct FrameNeedEffectState *owner;
    struct FrameObject *actor;
};
struct DisplayNeedEffectActionState {
    unsigned char unknown_00[0xf0];
    unsigned int (*begin)(struct FrameNeedEffectState *, struct FrameObject *,
                          unsigned char);
};
struct DisplayNeedEffectSavedObject {
    unsigned int unknown_00, flags;
    unsigned char unknown_08[48];
};
struct DisplayNeedEffectAppearance {
    unsigned char *resource;
    unsigned char mode, frame, unknown_06[2];
};
extern struct DisplayNeedEffectAppearance g_need_effect_appearances[];
extern unsigned char *g_need_effect_programs[][7];
void frame_set_animation_program(struct FrameObject *, struct FrameSpriteResource *,
                                 FrameU8 *, FrameU8);
extern const unsigned char *g_need_effect_resources[];
extern unsigned int g_need_effect_palettes[][6];
extern const void *g_need_effect_palette_39, *g_need_effect_palette_132;
extern const void *g_need_effect_palette_138;
extern unsigned char g_need_effect_game_state[], g_need_effect_save_state[];
extern struct DisplayNeedEffectChoiceState g_need_effect_choice_state;
extern struct DisplayNeedEffectSavedObject g_need_effect_saved_objects[];

/* Commit consumes a complete word, including sign-extended requests. */
void frame_commit_need_effect(struct FrameObject *, unsigned int);
unsigned char frame_need_effect_world_test(unsigned int, int);
void frame_set_animation_frame(struct FrameTickObject *, FrameU8);
void frame_acquire_palette_slot(struct FrameObject *, int);
void frame_set_object_palette(struct FrameObject *, const void *);
void frame_need_effect_interact(struct FrameObject *, struct FrameObject *);
void frame_need_effect_stop_at_position(struct FrameObject *);
void frame_disable_object_flags(struct FrameObject *, unsigned int);
void frame_set_variant_state(struct FrameObject *, unsigned char);
void frame_need_effect_choose_action(struct FrameObject *);
void frame_need_effect_finish_action(struct FrameObject *);
void frame_step_need_effect_attachments(struct FrameNeedEffectState *);
void frame_stop_motion(struct FrameObject *);
void frame_need_effect_restore_audio(struct FrameObject *);
int actor_entry_has_space(struct ConditionActorEntries *);
unsigned int actor_entry_add(struct ConditionActorEntries *, unsigned int,
                             unsigned char, unsigned char);
void frame_request_animation(struct FrameCommandObject *, unsigned char);
unsigned int audio_play_animation_cue(unsigned int);
#endif
