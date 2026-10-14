#ifndef DISPLAY_NEED_EFFECT_CHOICES_H
#define DISPLAY_NEED_EFFECT_CHOICES_H
#include "display_need_effect_progress.h"
#include "display_text_fields.h"

/* The callback receives the embedded choice buffer; its return value is unused here. */
struct DisplayNeedEffectChoiceCallback {
    unsigned char unknown_00[0xe8];
    unsigned int (*actions)(struct FrameNeedEffectState *, unsigned char *);
};
struct DisplayNeedEffectActionText {
    unsigned short unknown_00, text;
};
/* This five-byte access view overlaps the existing scene request storage. */
struct DisplayNeedEffectChoiceCounters {
    unsigned char unknown_00, value_1, value_2, unknown_03, value_4;
};
extern struct DisplayNeedEffectActionText g_need_effect_action_text[];
extern struct DisplayNeedEffectChoiceCounters g_need_effect_choice_counters;
extern unsigned short g_need_effect_choice_text[];
void display_scene_stage_08027dc0(unsigned int);
unsigned char frame_need_effect_build_choices(struct FrameObject *);
#endif
