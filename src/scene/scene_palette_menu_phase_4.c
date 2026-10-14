#include "scene_palette_menu_entry.h"
#include "input.h"
#include "scene_palette_menu_selector.h"

void scene_palette_menu_phase_4(void)
{
    register unsigned int directions asm("r0");
    unsigned int pressed = g_input_pressed[g_input_config.local_player];
    if (pressed & 9) {
        if (g_scene_palette_menu_owner->initial_word)
            return;
        g_scene_request.unknown_10 = 10;
        g_scene_request.unknown_14 = 30;
        g_scene_request.parameter = 5;
        audio_play_animation_cue(12);
    } else if (pressed & 2) {
        g_scene_request.unknown_10 = 10;
        g_scene_request.unknown_14 = 30;
        g_scene_request.parameter = 6;
        audio_play_animation_cue(12);
    } else if ((directions = pressed & 240)) {
        unsigned int previous = g_scene_request.scene;
        scene_palette_menu_adjust_selection();
        if (previous != g_scene_request.scene) {
            scene_palette_menu_refresh_selector(previous);
            scene_palette_menu_refresh_selector(g_scene_request.scene);
            if (g_scene_request.scene - 13 > 1) {
                struct FrameObject **objects = g_frame_actor_palette_menu_objects;
                objects[6]->id = g_scene_request.scene + 3;
                frame_set_variant_state(objects[6], 58);
                objects[6]->flags |= 1;
                objects[4]->flags |= 1;
                objects[3]->flags |= 1;
                objects[5]->flags &= ~1U;
                objects[4]->id = g_scene_request.scene + 15;
                frame_set_variant_state(objects[4], 58);
                objects[3]->id = g_scene_request.scene + 8;
                frame_set_variant_state(objects[3], 58);
            } else {
                struct FrameObject **objects = g_frame_actor_palette_menu_objects;
                objects[4]->flags &= ~1U;
                objects[3]->flags &= ~1U;
                objects[6]->flags &= ~1U;
                objects[5]->flags |= 1;
            }
        }
        if (g_scene_request.scene != 13) {
            const unsigned char *entries = g_scene_palette_menu_owner->parameters;
            unsigned int value = (entries += g_scene_request.scene, entries[-6]);
            unsigned int first_offset = (11 - value) * 2;
            const unsigned short *colors = g_palette_menu_selector_colors;
            display_load_palette_alternate((const unsigned char *)colors + first_offset, 65, 1);
            ++value;
            display_load_palette_alternate(colors + value, 81, 1);
        }
    }
}
asm(".align 2,0");
