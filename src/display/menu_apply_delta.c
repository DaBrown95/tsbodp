#include "scene_relation_grid.h"
#include "display_menu_secondary.h"
#include "display_menu_primary.h"
#include "frame_actor_relation.h"
#include "display_menu_effects.h"
#include "display_text_fields.h"
#include "resource_commands.h"
#include "save_world_display.h"
#include "frame_random.h"

/* Two observed word entries per criterion group; group bounds are provisional. */
struct MenuRelationCriterion { unsigned int encoded; };
extern const struct MenuRelationCriterion g_menu_relation_criteria[][2];

/* Actual three-byte history accessed after criterion processing. */
struct DeltaHistoryOwner {
    unsigned char codes[5], unknown05[16];
    signed char history[3];
};
extern struct DeltaHistoryOwner g_menu_delta_history_owner;
struct DeltaCaptionPoint { signed int x:16; signed int y:16; };
/* These low-level byte views follow the pinned 32-bit layouts. */
typedef char delta_criterion_row_size[sizeof(g_menu_relation_criteria[0]) == 8 ? 1 : -1];
typedef char delta_record_stride[sizeof(struct DisplayMenuRelationRecord) == 4 ? 1 : -1];
typedef char delta_flags_offset[
    (unsigned int)&((struct DisplayMenuSecondaryWorld *)0)->relation.values.records[0].flags == 56 ? 1 : -1];
typedef char delta_history_offset[
    (unsigned int)&((struct DeltaHistoryOwner *)0)->history == 21 ? 1 : -1];
typedef char delta_caption_size[sizeof(struct DeltaCaptionPoint) == 4 ? 1 : -1];
static inline void delta_caption(int relation, struct DeltaCaptionPoint point)
{
    const char *caption;
    display_text_select_font(0,0,-1);
    display_text_number_field_zero(relation);
    caption=display_scene_lookup_text(6222);
    display_text_draw_line(442,point.x,point.y,caption,2);
    display_text_copy_field_zero((const char *)&g_resource_game_state+16);
}

void display_menu_apply_delta(signed char requested)
{
    struct DeltaCaptionPoint point;
    register struct DisplayMenuRelationState *state asm("r8");
    register struct DisplayMenuRelationValues *values asm("r4");
    register const struct MenuRelationCriterion *criterion asm("r1");
    register unsigned char *parameters asm("r3");
    signed char delta;
    unsigned char code;
    register int index asm("r4");
    register int next_index asm("r0");
    int relative, relation;
    register unsigned int definition asm("r3");
    register unsigned int nonnegative asm("r10");
    register unsigned int shifted_input asm("r0");
    register int original_delta asm("r2");
    struct FrameTickObject *indicator;

    shifted_input = (unsigned int)(unsigned char)requested << 24;
    state = &g_menu_secondary_relation_owner.state;
    point.x = 238;
    point.y = 96;
    delta = shifted_input >> 24;
    original_delta = (int)shifted_input >> 24;
    nonnegative = original_delta >= 0;
    code = g_display_menu_state.codes[g_display_scene_request_state.scene];
    if (code != 0 && code != 28) {
        register struct DisplayMenuSecondaryWorld *world asm("r6") =
            (struct DisplayMenuSecondaryWorld *)((unsigned int)state-16);
        definition = g_display_menu_state.definition;
        /* Byte observations retain the native 32-bit address-add order. */
        if (*(const unsigned char *)((definition << 2) + (unsigned int)world + 56u) & 8) {
            register int adjusted asm("r0") = original_delta + 2;
            delta = adjusted;
        }
        {
            register const struct MenuRelationCriterion (*criterion_base)[2] asm("r2") =
                g_menu_relation_criteria;
            register unsigned int criterion_offset asm("r0") =
                (unsigned int)g_frame_actor_greetings[definition].unknown_24 << 3;
            criterion = (const struct MenuRelationCriterion *)(
                criterion_offset + (unsigned int)criterion_base);
        }
        parameters = (unsigned char *)world + 0x2a;
        index = 1;
        do {
            unsigned int encoded = criterion->encoded;
            unsigned char threshold = *(const unsigned char *)criterion;

            if (threshold <= 4) {
                if (*(const unsigned char *)((unsigned int)(unsigned char)(encoded >> 8) + (unsigned int)parameters) > threshold)
                    goto next_criterion;
                goto increment_delta;
            } else if (*(const unsigned char *)((unsigned int)(unsigned char)(encoded >> 8) + (unsigned int)parameters) >= threshold) {
increment_delta:
                ++delta;
            }
next_criterion:
            ++criterion;
            --index;
        } while (index >= 0);

        index = 2;
        do {
            signed char *history = g_menu_delta_history_owner.history;
            struct DisplaySceneRequestState *request = &g_display_scene_request_state;
            unsigned char *codes = g_menu_delta_history_owner.codes;
            register signed char *current asm("r6") = &history[index];
            if (*current ==
                *(const unsigned char *)((unsigned int)request->scene + (unsigned int)codes))
                delta = (signed char)delta + frame_random_range(-1, -2);
            if (index != 0) {
                next_index = index - 1;
                *current = history[next_index];
            } else {
                history[0] =
                    *(const unsigned char *)((unsigned int)request->scene + (unsigned int)codes);
                next_index = index - 1;
            }
            index = next_index;
        } while (index >= 0);
    }
    if (nonnegative) {
        if ((signed char)delta < 0)
            goto clear_delta;
    } else if ((signed char)delta > 0) {
clear_delta:
        delta = 0;
    }

    display_menu_adjust_relation(state, g_display_menu_state.definition,
                                 (signed char)delta);
    values = &state->values;
    {
        int current_relation = display_menu_read_relation(
            values, g_display_menu_state.definition);
        relative = current_relation - values->baseline;
    }
    if ((signed char)delta < -8 || relative < -15)
        display_menu_set_relation_delay(values, g_display_menu_state.definition, 1);
    if ((signed char)delta < -12 || relative < -30)
        display_menu_set_relation_delay(values, g_display_menu_state.definition, 2);

    if ((signed char)delta > 0) {
        audio_play_animation_cue(81);
        display_menu_show_change(6);
    } else if ((signed char)delta < 0) {
        audio_play_animation_cue(82);
        display_menu_show_change(7);
    }
    display_copy_background_rectangle(1,
        (const struct DisplayStoredMap *)g_display_menu_state.unknown_0c[1],
        27, 12, 27, 12, 3, 2, 0xd116);
    display_text_set_background_control(g_display_menu_control1);
    indicator = (struct FrameTickObject *)g_display_menu_objects.unknown_00[0];
    {
        unsigned int selected_definition = g_display_menu_state.definition;
        relation = display_menu_read_relation(&g_display_menu_relation_values,
                                             selected_definition);
    }
    {
        int percent, frame;
        if (relation > 0) {
            percent=save_world_ratio_percent(relation,100);
            frame=save_world_scale_percent(10,(unsigned short)percent);
            frame_set_animation_frame(indicator,(unsigned char)(frame+10));
        } else {
            register int numerator asm("r0")=relation;
            int denominator=-100;
            percent=save_world_ratio_percent(numerator,denominator);
            frame=save_world_scale_percent(10,(unsigned short)percent);
            frame_set_animation_frame(indicator,(unsigned char)(10-frame));
        }
    }
    delta_caption(relation,point);
    display_text_set_background_control(g_display_menu_control0);
}

asm(".align 2, 0");
