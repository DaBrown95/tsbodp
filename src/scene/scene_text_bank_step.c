#include "scene_text_bank.h"
void scene_text_bank_step(void)
{
    unsigned int pressed = g_input_local_pressed[g_input_config.local_player];
    unsigned int confirm = 1;
    if (confirm & pressed) {
        scene_text_bank_apply_selection();
        audio_play_animation_cue(1);
    } else {
        unsigned int cancel = 2;
        cancel &= pressed;
        if (cancel)
            scene_text_bank_return_previous();
        else {
            unsigned int alternate = 4;
            alternate &= pressed;
            if (alternate)
                scene_text_bank_return_previous();
            else {
                unsigned int cursor = 0xc0;
                cursor &= pressed;
                if (cursor) {
                    scene_text_bank_change_selection();
                    audio_play_animation_cue(0);
                }
            }
        }
    }
}
asm(".align 2,0");
