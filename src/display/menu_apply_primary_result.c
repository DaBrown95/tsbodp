#include "display_menu_results.h"

static inline void *relation_values(void *pointer)
{
    unsigned char *base = pointer;
    return base + 0x20;
}

void display_menu_apply_primary_result(void)
{
    signed char probability = (signed char)display_menu_read_relation(
        relation_values(&g_display_menu_relation_state), g_display_menu_state.definition);
    struct DisplaySceneRequestState *selection = &g_display_scene_request_state;
    const unsigned char *codes = g_display_menu_state.codes;
    /* Preserve the two observed reads through a local byte access view. */
    const volatile unsigned char *code = codes + selection->scene;
    if (*code != 22) {
        const unsigned char *base = g_display_menu_primary_chance_offsets;
        int code_index = *code - 2;
        const unsigned char *offset = (const unsigned char *)(code_index + (unsigned int)base);
        int value = probability;
        probability = value + *offset;
    }
    else if (g_display_menu_state.definition <= 14)
        probability = -1;
    else {
        int value = (signed char)probability;
        probability = -1;
        if (value > 49) {
            probability = 75;
            if (value <= 74)
                probability = 50;
        }
    }
    if (frame_random_bounded(100) <= (signed char)probability) {
        const struct DisplayMenuResult *result;
        const struct DisplayMenuPrimaryResultRow *row;
        unsigned int code = g_display_menu_state.codes[g_display_scene_request_state.scene];
        struct DisplayMenuState *menu = &g_display_menu_state;
        struct DisplaySceneRequestState *request = &g_display_scene_request_state;
        if (code != 22) {
            struct DisplayMenuResultObserver *game = &g_display_menu_result_observer;
            if (game->variant != g_frame_actor_greetings[menu->definition].cue_variant)
                display_menu_try_relation_flag((unsigned char *)game + 0x30, menu->definition);
            row = &g_display_menu_primary_result_rows[menu->definition];
            result = (const struct DisplayMenuResult *)((unsigned int)row + menu->codes[request->scene] * sizeof(*result));
        } else
            result = (const struct DisplayMenuResult *)&g_display_menu_primary_special_rows[menu->definition];
        {
            /* This short request pointer constraint ends before result-consumer calls. */
            register struct DisplaySceneRequestState *current asm("r2") = request;
            int selected_code;
            {
                const unsigned char *source = menu->codes;
                unsigned int row = current->scene;
                const unsigned char *address = (const unsigned char *)(row + (unsigned int)source);
                selected_code = *address;
            }
            switch (selected_code) {
            case 3:
            case 4:
            {
                current->unknown_10 = 2;
                current->unknown_14 = 45;
                break;
            }
            case 5:
                request->unknown_10 = 2;
                request->unknown_14 = 90;
                break;
            }
        }
        display_menu_apply_delta(result->delta);
        display_menu_draw_primary_result(result->text, 1);
    } else if (g_display_menu_state.codes[g_display_scene_request_state.scene] != 22) {
        display_menu_apply_delta(-5);
        display_menu_draw_primary_result(0, 0);
    } else {
        display_menu_apply_delta(0);
        display_menu_draw_primary_result(2, 0);
    }
}

asm(".align 2, 0");
