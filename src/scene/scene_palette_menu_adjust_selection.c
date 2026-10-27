#include "scene_palette_menu_entry.h"
#include "display_text_draw.h"
#include "display_time_hud.h"
#include "input.h"
#include "scene_palette_menu_selector.h"

static inline unsigned char *palette_row_value(struct ScenePaletteMenuOwner *owner,
    unsigned int row, unsigned int field_offset)
{
    unsigned char *entries = (unsigned char *)*(const void **)((unsigned int)owner + field_offset);
    entries += 2;
    entries += row;
    return entries;
}

void scene_palette_menu_adjust_selection(void)
{
    /* Reuse the request/collection address only across their actual phases. */
    void *owner = &g_scene_request;
    unsigned int retained = g_scene_request.scene;
    unsigned int row, chosen;
    unsigned int *selection = &((struct SceneRequest *)owner)->scene;
    unsigned short remove;
    struct ScenePaletteMenuOwner **owner_root;

    input_step_local_vertical_pressed(selection, 8, 14, 1, 0);
    if (!g_frame_actor_palette_menu_enabled[((struct SceneRequest *)owner)->scene]) {
        unsigned int *skip_row = selection;
        const unsigned char *enabled = g_frame_actor_palette_menu_enabled;
        do {
            input_step_local_vertical_pressed(skip_row, 8, 14, 1, 0);
        } while (!*(const unsigned char *)(((struct SceneRequest *)owner)->scene +
                                         (unsigned int)enabled));
    }
    if (retained != g_scene_request.scene)
        audio_play_animation_cue(0);
    switch (g_scene_request.scene) {
    case 8: case 9: case 10: case 11: case 12:
        break;
    case 13:
        goto horizontal;
    case 14:
        /* Row fourteen has no local adjustment. */
        return;
    default:
        return;
    }
    row = g_scene_request.scene - 8;
    remove = g_input_local_pressed[0] & 32;
    if (remove) {
        unsigned char *value;
        struct ScenePaletteMenuOwner *gate;
        /* These short-lived values are consumed before the next call. */
        register struct FrameObject *cleared asm("r2");
        owner_root = &g_scene_palette_menu_owner;
        gate = *owner_root;
        {
            register unsigned char *entries asm("r0") = (unsigned char *)gate->parameters;
            entries += 2;
            value = entries + row;
        }
        if (!*value)
            goto rejected;
        {
            unsigned int updated = *value - 1;
            cleared = 0;
            *value = updated;
        }
        owner = *owner_root;
        chosen = *palette_row_value(owner, row, 304);
        retained = (unsigned int)((struct ScenePaletteMenuOwner *)owner)->groups[row][chosen];
        ((struct ScenePaletteMenuOwner *)owner)->groups[row][chosen] = cleared;
        chosen = ((struct ScenePaletteMenuOwner *)owner)->initial_word;
        ++((struct ScenePaletteMenuOwner *)owner)->initial_word;
        g_frame_actor_palette_menu_objects[8]->flags &= ~1U;
        display_clear_background_rectangle(0, 24, 17, 3, 3);
        {
            struct ScenePaletteMenuOwner *destination = *owner_root;
            destination->available[chosen] = (struct FrameObject *)retained;
        }
        frame_set_position((struct FrameObject *)retained,
            (chosen * 3 + 83) << 16, 28 << 16);
        audio_play_animation_cue(13);
    } else if (g_input_local_pressed[0] & 16) {
        unsigned int parameters_offset;
        struct ScenePaletteMenuOwner *owner;
        unsigned char *value;
        owner_root = &g_scene_palette_menu_owner;
        owner = *owner_root;
        parameters_offset =
            (unsigned int)&owner->parameters - (unsigned int)owner;
        if (*palette_row_value(owner, row, parameters_offset) > 9 || !owner->initial_word)
            goto rejected;
        chosen = --owner->initial_word;
        if (!chosen) {
            const char *text;
            g_frame_actor_palette_menu_objects[8]->flags |= 1;
            text = display_scene_lookup_text(31);
            display_text_draw_line(241, 205, 143, text, 1);
        }
        {
            struct ScenePaletteMenuOwner *source = *owner_root;
            retained = (unsigned int)source->available[chosen];
            source->available[chosen] = (struct FrameObject *)(unsigned int)remove;
            value = palette_row_value(source, row, parameters_offset);
            chosen = *value;
            ++*value;
        }
        {
            struct ScenePaletteMenuOwner *destination = *owner_root;
            destination->groups[row][chosen] = (struct FrameObject *)retained;
        }
        frame_set_position((struct FrameObject *)retained,
            (chosen * 3 + 106) << 16, (row * 20 + 46) << 16);
        audio_play_animation_cue(13);
    }
    return;
rejected:
    audio_play_animation_cue(3);
    return;
horizontal: {
        unsigned int value = *(const unsigned char *)g_scene_palette_menu_owner->parameters;
        input_step_local_horizontal_pressed(&value, 0, 11, 1, 0);
        if (*(const unsigned char *)g_scene_palette_menu_owner->parameters != value) {
            *(unsigned char *)g_scene_palette_menu_owner->parameters = value;
            scene_palette_menu_refresh_selector(13);
            audio_play_animation_cue(0);
        }
    }
}
asm(".align 2,0");
