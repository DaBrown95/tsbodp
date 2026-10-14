#include "scene_palette_menu_entry.h"
#include "input.h"
#include "scene_palette_menu_selector.h"

void scene_palette_menu_phase_5(void)
{
    register const unsigned short *input asm("r1") = g_input_pressed;
    unsigned int pressed = input[g_input_config.local_player];
    register unsigned int confirm_mask asm("r2") = 9;
    register unsigned int masked asm("r0");
    if ((masked = confirm_mask, masked &= pressed)) {
        g_scene_request.unknown_10 = 12;
        g_scene_request.unknown_14 = 15;
        g_scene_request.parameter = 14;
        audio_play_animation_cue(12);
    } else if ((masked = 2, masked &= pressed)) {
        g_scene_request.unknown_10 = 12;
        g_scene_request.unknown_14 = 15;
        g_scene_request.parameter = confirm_mask;
        audio_play_animation_cue(12);
    }
}
asm(".align 2,0");
